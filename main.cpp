#include <iostream>
#include <conio.h>
#include <windows.h> 

using namespace std;
void Input_number();

const int width = 9;
const int height = 9;

char map[height][width] = {'3', '4', ' ', ' ', ' ', '7', ' ', '2', '6',
						   ' ', '2', ' ', ' ', ' ', '4', '8', ' ', '1',
						   ' ', ' ', '1', '2', ' ', '5', ' ', ' ', ' ',
						   '2', '5', ' ', '6', ' ', ' ', ' ', ' ', ' ',
						   '6', '8', ' ', '9', ' ', ' ', '3', '4', ' ',
						   ' ', '1', ' ', '4', ' ', '2', ' ', ' ', '8',
						   '1', '6', ' ', ' ', '8', '9', ' ', '3', ' ',
						   '4', ' ', '9', ' ', '2', ' ', '6', ' ', ' ',
						   ' ', ' ', '8', '7', '4', '6', '2', ' ', ' '
						   };
						   
char map_win[height][width] = {'3', '4', '5', '8', '1', '7', '9', '2', '6',
						   '7', '2', '6', '3', '9', '4', '8', '5', '1',
						   '8', '9', '1', '2', '6', '5', '4', '7', '3',
						   '2', '5', '4', '6', '3', '8', '1', '9', '7',
						   '6', '8', '7', '9', '5', '1', '3', '4', '2',
						   '9', '1', '3', '4', '7', '2', '5', '6', '8',
						   '1', '6', '2', '5', '8', '9', '7', '3', '4',
						   '4', '7', '9', '1', '2', '3', '6', '8', '5',
						   '5', '3', '8', '7', '4', '6', '2', '1', '9'
						   };

char map_game[height][width];
int symb;
enum eDirection  {STOP = 0, LEFT, RIGHT, UP, DOWN, SPACE, NUMBER};
eDirection dir;
int x_cord, y_cord, x_map, y_map, temp;
bool gameOver;

HANDLE col_txt = GetStdHandle(STD_OUTPUT_HANDLE);

						   
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Start()
{
	gameOver = false;
	dir = STOP;
	temp = 0;
	x_cord = 34;
	y_cord = 14;
	x_map = 0;
	y_map = 0;
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			map_game[i][j] = map[i][j];
}

void Draw()
{	
	cout << "\t\t ___________________________________\n";
	for(int i = 0; i < height; i++)
	{
		cout << "\t\t|   |   |   |   |   |   |   |   |   |\n";
		cout << "\t\t| ";
		for(int j = 0; j < width; j++)
		{	
			cout << map[i][j] << " | ";
		}
		cout << endl;
		cout << "\t\t|___|___|___|___|___|___|___|___|___|\n";
	}
}

void Input()
{
	if(_kbhit())
	{	
		symb = _getch();
		switch(symb)
		{
			case 'a':
				if(x_cord != 18)
				dir = LEFT;
				break;
			case 'd':
				if(x_cord != 50)
				dir = RIGHT;
				break;
			case 'w':
				if(y_cord != 2)
				dir = UP;
				break;
			case 's':
				if(y_cord != 26)
				dir = DOWN;
				break;
			case ' ':
				dir = SPACE;
				break;
			case 'x':
				gotoxy(0,30);
				cout << "End Game!\n";
				gameOver = true;
				break;
			default: Input_number(); break;
		};
	}
}

void Input_number()
{		
		dir = NUMBER;
		x_map = (x_cord - 18) / 4;
		y_map = (y_cord - 2) / 3;
		//gotoxy(x_cord,y_cord);
		//cout << "x : " << x_cord <<" y : " << y_cord << endl;
		if(map_game[y_map][x_map] == ' ')
		{
			switch(symb)
			{
				case '1': map_game[y_map][x_map] = '1'; break; 	
				case '2': map_game[y_map][x_map] = '2'; break;
				case '3': map_game[y_map][x_map] = '3'; break;
				case '4': map_game[y_map][x_map] = '4'; break;
				case '5': map_game[y_map][x_map] = '5'; break;
				case '6': map_game[y_map][x_map] = '6'; break;
				case '7': map_game[y_map][x_map] = '7'; break;
				case '8': map_game[y_map][x_map] = '8'; break;
				case '9': map_game[y_map][x_map] = '9'; break;
			}
			if(map_game[y_map][x_map] != ' ')
			{
				if(map_game[y_map][x_map] == map_win[y_map][x_map])
					SetConsoleTextAttribute(col_txt,FOREGROUND_GREEN);
				else SetConsoleTextAttribute(col_txt,FOREGROUND_RED);
				cout << map_game[y_map][x_map];
				gotoxy(x_cord,y_cord);
				temp++;
			}
		}
}

void Logic()
{
	switch(dir)
	{
		case LEFT: x_cord -= 4; break;
		case RIGHT: x_cord += 4; break;
		case UP: y_cord -= 3; break;
		case DOWN: y_cord += 3; break;
	}

	if(dir == SPACE)
	{	
		if(map_game[y_map][x_map] != ' ')
		{
			if(map[y_map][x_map] == ' ')
			{
				cout << ' ';
				gotoxy(x_cord,y_cord);
				map_game[y_map][x_map] = ' ';
				temp--;
			}
		}
	}
	else if(dir != STOP)
	{
		x_map = (x_cord - 18) / 4;
		y_map = (y_cord - 2) / 3;
		gotoxy(x_cord,y_cord);
		dir = STOP;
		if(temp == 43)
		{	
			gotoxy(0,30);
			int i = 0, j;
			while(i < height && !gameOver)
			{
				j = 0;
				while(j < width && !gameOver)
				{
					if(map_game[i][j] != map_win[i][j])
						gameOver = true;
					else{
						j++;
						if(j == width) 
							i++;
					}
				}
			}
			
				
			if(!gameOver)
			{	
				SetConsoleTextAttribute(col_txt,FOREGROUND_GREEN);
				cout << "\t\t\t!!! Game Wins !!!\n";	
			}else {
				SetConsoleTextAttribute(col_txt,FOREGROUND_RED);
				cout << "\t\t\t!!! GameOver !!!\n";
 			}
 			SetConsoleTextAttribute(col_txt,7);
 			gameOver = true;
		}
	}
	//cout << "x : " << x_cord << " y : " << y_cord << endl;
	Sleep(10);
}

int main() 
{	
	Start();
	Draw();
	gotoxy(x_cord,y_cord);
	while(!gameOver)
	{	
		Input();
		Logic();
		//gotoxy(x_cord,y_cord);
		//cout << "x : " << x_cord << " y : " << y_cord << endl;
	}
	system("Pause");
	return 0;
}
