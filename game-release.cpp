#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<string>
#include<unistd.h>
#include<sstream>
#include<cmath>
//#ifdef _WIN32
//#include <Windows.h>
//#include "MMSystem.h"
//#endif    
//#include<cstdlib>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>

using namespace std;

void CollisionCheck();
void updateSnakeTail();
void DisplayMsg();
void increaseBody();

const int grid_size=30;
const int one_grid_size=20;
int bonusTurn = 0;

int grid[grid_size][grid_size];

int snake_head_x = 2;
int snake_head_y = 2;
int snake_tail1_x = snake_head_x+3;
int snake_tail1_y = snake_head_y;
int snake_tail2_x = snake_head_x+4;
int snake_tail2_y = snake_head_y;

int mid_x = snake_head_x+1;
int mid_y = snake_head_y;

int mid1_x = snake_head_x+2;
int mid1_y = snake_head_y;

int food1_x, food1_y;
int food2_x, food2_y;
int food3_x, food3_y;
int food4_x, food4_y;
int food5_x, food5_y;

int food_x=-10,food_y=-10;
bool valid_position;
	
int score=0;

void SetCanvasSize(int width, int height) //not changed
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
}

double startx=320,starty=400;


bool gameEnd = false;
bool gameMode = true;

void Display()
{
	{
		// set the background color using function glClearColotgr.
		// to change the background play with the red, green and blue values below.
		// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

		glClearColor(1/*Red Component*/, 1.0/*Green Component*/,
				1.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
		
		/*
		DrawSquare( 300 , 300 ,100,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
		DrawString( 50, 600, "Here are some are basic shapes", colors[MISTY_ROSE]); // this will print given string at x=50 , y=600
		DrawString( 50, 570, "You will use these to make your game", colors[MISTY_ROSE]); // this will print given string at x=50 , y=570
		DrawCircle( 200 , 200 , 50 , colors[5]); // This will draw a circle at x=200,y=200 of radius 50
																			
																			//                    v1( x,y )   v2( x,y )  , v3( x,y ) 
		DrawTriangle( 300, 50 , 500, 50 , 400 , 250, colors[MISTY_ROSE] );  // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
		
		//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
		DrawLine( 550 , 50 ,  550 , 600 , 20 , colors[MISTY_ROSE] );
		*/


		for (int i = 0; i < grid_size; i++)//this will add boundaries to the snake board
		{
			for (int j = 0;j< grid_size; j++)
			{
				if((i==0 || i==grid_size-1 || j==0 || j==grid_size-1)&& i!=5 && i!=6 && i!=7 && i!=8 && i!=9 && i!=10 && i!=11 && i!=12 && i!=13 && i!=14 && i!=15 	&& i!=16 && i!=17 && i!=18 && i!=19 && i!=20 && i!=21)
					grid[i][j] = GOLD;
			}
		}

		for (int i=0; i < grid_size; i++) 
		{
			for (int j=0; j < grid_size; j++) 
			{
				if (i == food1_x && j == food1_y)//1st element
				{
					DrawSquare( i*one_grid_size , j*one_grid_size ,one_grid_size,colors[FOREST_GREEN]);//giving parameters to square
					DrawCircle( i*one_grid_size+(one_grid_size/2) , j*one_grid_size+(one_grid_size/2) , (one_grid_size/2)-1 , colors[grid[i][j]]);
				}
				
				else if (i == food2_x && j == food2_y) //2nd  element
				{
					DrawSquare( i*one_grid_size , j*one_grid_size ,one_grid_size,colors[FOREST_GREEN]);//giving parameters to square
					DrawCircle( i*one_grid_size+(one_grid_size/2) , j*one_grid_size+(one_grid_size/2) , (one_grid_size/2)-1 , colors[grid[i][j]]);
				}
				
				else if (i == food3_x && j == food3_y) //3rd
				{
					DrawSquare( i*one_grid_size , j*one_grid_size ,one_grid_size,colors[FOREST_GREEN]);//giving parameters to square
					DrawCircle( i*one_grid_size+(one_grid_size/2) , j*one_grid_size+(one_grid_size/2) , (one_grid_size/2)-1 , colors[grid[i][j]]);
				}
				else if (i == food4_x && j == food4_y)//4th 
				{
					DrawSquare( i*one_grid_size , j*one_grid_size ,one_grid_size,colors[FOREST_GREEN]);//giving parameters to square
					DrawCircle( i*one_grid_size+(one_grid_size/2) , j*one_grid_size+(one_grid_size/2) , (one_grid_size/2)-1 , colors[grid[i][j]]);
				}
				else if (i == food5_x && j == food5_y) //5th
				{
					DrawSquare( i*one_grid_size , j*one_grid_size ,one_grid_size,colors[FOREST_GREEN]);//giving parameters to square
					DrawCircle( i*one_grid_size+(one_grid_size/2) , j*one_grid_size+(one_grid_size/2) , (one_grid_size/2)-1 , colors[grid[i][j]]);
				}
				
				else if (i == food_x && j == food_y) //bonus element
				{
					DrawSquare( i*one_grid_size , j*one_grid_size ,one_grid_size,colors[FOREST_GREEN]);//giving parameters to square
					DrawCircle( i*one_grid_size+(one_grid_size/2) , j*one_grid_size+(one_grid_size/2) , (one_grid_size/2)-1 , colors[grid[i][j]]);
				}
					
				else if (i == snake_head_x && j == snake_head_y) 
				{
					DrawSquare( i*one_grid_size , j*one_grid_size ,one_grid_size,colors[FOREST_GREEN]);
					DrawCircle( i*one_grid_size+(one_grid_size/2) , j*one_grid_size+(one_grid_size/2) , (one_grid_size/2)-1 , colors[grid[i][j]]);
				}
				
				else
					DrawSquare( i*one_grid_size , j*one_grid_size ,one_grid_size,colors[grid[i][j]]);	
			}   
		}
		
		DrawString( 24*one_grid_size , 29*one_grid_size , "Score=" + to_string(score), colors[BLACK]); 
		DrawString( 2*one_grid_size , 29*one_grid_size , "Snake", colors[BLACK]); 
		for (int i = 5; i <= 21; i++)
			{
				int j=29;
				grid[i][j] = WHITE;
			}
			
			int s=score/5;
			s=s+5;
			if( s<21 && s%21==0)
				s=5;
		for (int i =5 ; i < s; i++)
			{
				int j=29;
				grid[i][j] = DARK_RED;
			}	
				
	if (gameEnd) 
	{
		DrawSquare(0, 0, 600, colors[WHEAT]);
		DrawString( 6*one_grid_size , 17*one_grid_size , "GAME OVER!", colors[SIENNA]); 
		DrawString( 6*one_grid_size , 15*one_grid_size , "Score " + to_string(score), colors[SIENNA]); 		
		DrawString( 6*one_grid_size , 13*one_grid_size , "Press ESC to exit", colors[SIENNA]); 		
	}
			
	if (gameMode) 
	{
		DrawSquare(0, 0, 600, colors[WHEAT]);
		DrawString( 8*one_grid_size , 21*one_grid_size , "Start Game (S)", colors[SIENNA]); 	
		DrawString( 8*one_grid_size , 19*one_grid_size , "Resume Game ", colors[SIENNA]); 	
		DrawString( 8*one_grid_size , 17*one_grid_size , "Change Level", colors[SIENNA]); 	
		DrawString( 8*one_grid_size , 15*one_grid_size , "High Score", colors[SIENNA]); 	
		DrawString( 8*one_grid_size , 13*one_grid_size , "Game History", colors[SIENNA]); 	
		DrawString( 8*one_grid_size , 11*one_grid_size , "Exit ", colors[SIENNA]); 	
	}	
		
	   	glutSwapBuffers(); // do not modify this line..
	}	
}	

void updateSnakeTail() 
{

	grid[snake_tail2_x][snake_tail2_y] = FOREST_GREEN;
	
	snake_tail2_x = snake_tail1_x;
	snake_tail2_y = snake_tail1_y;

	if (grid[snake_tail1_x-1][snake_tail1_y] == MAROON) 
	{
		snake_tail1_x = snake_tail1_x-1;
	}
	else if (grid[snake_tail1_x+1][snake_tail1_y] == MAROON) 
	{
		snake_tail1_x = snake_tail1_x+1;
	}
	else if (grid[snake_tail1_x][snake_tail1_y-1] == MAROON) 
	{
		snake_tail1_y = snake_tail1_y-1;
	}
	else if (grid[snake_tail1_x][snake_tail1_y+1] == MAROON) 
	{
		snake_tail1_y = snake_tail1_y+1;
	}
	
	grid[snake_tail1_x][snake_tail1_y] = MAROON;	

	return;
}

void NonPrintableKeys(int key, int x, int y) 
{
	if (key == GLUT_KEY_LEFT)   	
	{	
		if (grid[snake_head_x-1][snake_head_y] != MAROON && grid[snake_head_x-1][snake_head_y] != GOLD) 
		{
	   		snake_head_x = snake_head_x-1;
	   		grid[snake_head_x][snake_head_y] = MAROON;
	   		
	   		updateSnakeTail();
		}
		else 
		{
			gameEnd = true;
		}
		
		CollisionCheck();
   		
	} 
	else if (key == GLUT_KEY_RIGHT) 
	{
	   	if (grid[snake_head_x+1][snake_head_y] != MAROON && grid[snake_head_x+1][snake_head_y] != GOLD) 
	   	{
	   		snake_head_x = snake_head_x+1;
	   		grid[snake_head_x][snake_head_y] = MAROON;
	   		
	   		updateSnakeTail();
	   	}
		else 
		{
			gameEnd = true; 

		}
		
	   	CollisionCheck();
	} 
	else if (key == GLUT_KEY_UP) 	
	{
   		if (grid[snake_head_x][snake_head_y+1] != MAROON && grid[snake_head_x][snake_head_y+1] != GOLD) 
   		{
   			snake_head_y = snake_head_y+1;
   			grid[snake_head_x][snake_head_y] = MAROON;
   		
   			updateSnakeTail();
		}
		else 
		{
			gameEnd = true;
		}
		
		CollisionCheck();
	}
	else if (key == GLUT_KEY_DOWN)  
	{
   		if (grid[snake_head_x][snake_head_y-1] != MAROON && grid[snake_head_x][snake_head_y-1] != GOLD) //collision with in self
   		{
   			snake_head_y = snake_head_y-1;
   			grid[snake_head_x][snake_head_y] = MAROON;
   		
   			updateSnakeTail();
   		}
		else 
		{
			gameEnd = true;
		}
		
   		CollisionCheck();
	}
	
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) 
{
	if (key == KEY_ESC/* Escape key ASCII*/) 
	{
		exit(1); // exit the program when escape key is pressed.
	}
	if (key == 'R' || key=='r'/* Escape key ASCII*/) 
	{
		//exit(1); // exit the program when escape key is pressed.
		//aswangle+=90;
	}	
	
	if (key == 'S' || key=='s'/* Escape key ASCII*/) 
	{
		gameMode = false;
	}	
	
	glutPostRedisplay();
}

void increaseBody() 
{
	int new_tail_x, new_tail_y;
	if (snake_tail1_x == snake_tail2_x) 
	{
		new_tail_x = snake_tail2_x;
		if (snake_tail1_y - snake_tail2_y == 1) 
		{
			new_tail_y = snake_tail2_y - 1;
		}
		else 
		{	// = -1
			new_tail_y = snake_tail2_y + 1;
		}
	}
	else if (snake_tail1_y == snake_tail2_y) 
	{
		new_tail_y = snake_tail2_y;
		if (snake_tail1_x - snake_tail2_x == 1) 
		{
			new_tail_x = snake_tail2_x - 1;
		}
		else 
		{	// = -1
			new_tail_x = snake_tail2_x + 1;
		}
	}
	
	grid[new_tail_x][new_tail_y] = MAROON;
	snake_tail1_x = snake_tail2_x;
	snake_tail1_y = snake_tail2_y;

	snake_tail2_x = new_tail_x;
	snake_tail2_y = new_tail_y;	
	
	return;
}

void CollisionCheck ()
{

	if(snake_head_x == food1_x && snake_head_y == food1_y)
	{
		score=score+5;
		
		grid[food1_x][food1_y] = MAROON;
		increaseBody();
		bool isNotBody = true;
		while (isNotBody) 
		{
			food1_x = rand()%(grid_size-3)+1;
			food1_y = rand()%(grid_size-3)+1;
			
			if (grid[food1_x][food1_y] != MAROON && grid[food1_x][food1_y] != GOLD)
			{
				if(food1_x==food2_x || food1_x==food3_x || food1_x==food4_x || food1_x==food5_x ||
			 	   food1_y==food2_y || food1_y==food3_y || food1_y==food4_y || food1_y==food5_y  )
				{}
				else
				isNotBody = false;
			}	
		}
		
		grid[food1_x][food1_y] = POWDER_BLUE;
	}
	
	if(snake_head_x == food2_x && snake_head_y == food2_y)
	{
		score=score+5;
		
		grid[food2_x][food2_y] = MAROON;
		increaseBody();
		bool isNotBody = true;
		while (isNotBody) 
		{
			food2_x = rand()%(grid_size-3)+1;
			food2_y = rand()%(grid_size-3)+1;
			
			if (grid[food2_x][food2_y] != MAROON && grid[food2_x][food2_y] != GOLD)
			{
				if(food1_x==food2_x || food2_x==food3_x || food2_x==food4_x || food2_x==food5_x ||
			 	   food1_y==food2_y || food2_y==food3_y || food2_y==food4_y || food2_y==food5_y )
				{}
				else
				isNotBody = false;
			}	
		}
		
		grid[food2_x][food2_y] = POWDER_BLUE;
	}
	
	if(snake_head_x == food3_x && snake_head_y == food3_y)//third
	{
		score=score+5;	
		
		grid[food3_x][food3_y] = MAROON;
		increaseBody();
		bool isNotBody = true;
		
		while (isNotBody) 
		{
			food3_x = rand()%(grid_size-3)+1;
			food3_y = rand()%(grid_size-3)+1;
			
			if (grid[food3_x][food3_y] != MAROON && grid[food3_x][food3_y] != GOLD)
			{
				if(food3_x==food2_x || food1_x==food3_x || food3_x==food4_x || food3_x==food5_x ||
				   food3_y==food2_y || food1_y==food3_y || food3_y==food4_y || food3_y==food5_y )
				{}
				else
				isNotBody = false;
			}	
		}
		
		grid[food3_x][food3_y] = POWDER_BLUE;
	}
	
	if(snake_head_x == food4_x && snake_head_y == food4_y)//4th
	{
		score=score+5;
		
		grid[food4_x][food4_y] = MAROON;
		increaseBody();		
		bool isNotBody = true;		
		while (isNotBody) 
		{
			food4_x = rand()%(grid_size-3)+1;
			food4_y = rand()%(grid_size-3)+1;
						
			if (grid[food4_x][food4_y] != MAROON && grid[food4_x][food4_y] != GOLD)
			{
				if(food4_x==food2_x || food4_x==food3_x || food1_x==food4_x || food4_x==food5_x ||
			   	   food4_y==food2_y || food4_y==food3_y || food1_y==food4_y || food4_y==food5_y  )
				{}
				else
				isNotBody = false;
			}	
		}
		
		grid[food4_x][food4_y] = POWDER_BLUE;
	}
	
	if(snake_head_x == food5_x && snake_head_y == food5_y)//fifth
	{
		score=score+5;	

		grid[food5_x][food5_y] = MAROON;	
		increaseBody();	
		bool isNotBody = true;
		while (isNotBody) 
		{
			food5_x = rand()%(grid_size-3)+1;
			food5_y = rand()%(grid_size-3)+1;
			
			if (grid[food5_x][food5_y] != MAROON && grid[food5_x][food5_y] != GOLD)
			{
				if(food5_x==food2_x || food5_x==food3_x || food5_x==food4_x || food1_x==food5_x ||
			 	   food5_y==food2_y || food5_y==food3_y || food5_y==food4_y || food1_y==food5_y  )
				{}
				else
				isNotBody = false;
			}	
		}
		
		grid[food5_x][food5_y] = POWDER_BLUE;
	}
	
	if(snake_head_x == food_x && snake_head_y == food_y)//that bonus element
	{
		score=score+20;
		increaseBody();
		//PlaySound(TEXT("song"),NULL,SND_FILENAME);
		//system("pause");	
		
		grid[food_x][food_y] = MAROON;//not recreating it because it is the bonus point which appears once in a minute
	}
	

	return;
}

void Timer(int m) 
{
	glutPostRedisplay();
	
	grid[food1_x][food1_y] = FOREST_GREEN;
	grid[food2_x][food2_y] = FOREST_GREEN;
	grid[food3_x][food3_y] = FOREST_GREEN;
	grid[food4_x][food4_y] = FOREST_GREEN;
	grid[food5_x][food5_y] = FOREST_GREEN;
	
	bool isNotBody = true;
	while (isNotBody) 
	{
		food1_x = rand()%(grid_size-3)+1 ;
		food1_y = rand()%(grid_size-3)+1;
		
		if ((grid[food1_x][food1_y]  == FOREST_GREEN))//!= MAROON) && (grid[food1_x][food1_y] != GOLD))
		{
			if(food1_x==food2_x || food1_x==food3_x || food1_x==food4_x || food1_x==food5_x ||
			   food1_y==food2_y || food1_y==food3_y || food1_y==food4_y || food1_y==food5_y  )
			{}
			else 
			isNotBody = false;
		}
	}
	
	isNotBody = true;
	while (isNotBody) 
	{
		food2_x = rand()%(grid_size-3)+1;
		food2_y = rand()%(grid_size-3)+1;
		
		if (grid[food2_x][food2_y]  == FOREST_GREEN)//!= MAROON) && (grid[food2_x][food2_y] != GOLD))
		{
			if(food1_x==food2_x || food2_x==food3_x || food2_x==food4_x || food2_x==food5_x ||
			   food1_y==food2_y || food2_y==food3_y || food2_y==food4_y || food2_y==food5_y )
			{}
			else
			isNotBody = false;
		}		
	}
	
	isNotBody = true;
	while (isNotBody) 
	{
		food3_x = rand()%(grid_size-3)+1;
		food3_y = rand()%(grid_size-3)+1;
		
		if ((grid[food3_x][food3_y]  == FOREST_GREEN))//!= MAROON) && (grid[food3_x][food3_y] != GOLD))
		{
			if(food3_x==food2_x || food1_x==food3_x || food3_x==food4_x || food3_x==food5_x ||
			   food3_y==food2_y || food1_y==food3_y || food3_y==food4_y || food3_y==food5_y )
			 {}
			 else
			 	isNotBody = false;
		}
	}
	
	isNotBody = true;
	while (isNotBody) 
	{
		food4_x = rand()%(grid_size-3)+1;
		food4_y = rand()%(grid_size-3)+1;
		
		if ((grid[food4_x][food4_y] == FOREST_GREEN))//!= MAROON) && (grid[food4_x][food4_y] != GOLD))
		{
			if(food4_x==food2_x || food4_x==food3_x || food1_x==food4_x || food4_x==food5_x ||
			   food4_y==food2_y || food4_y==food3_y || food1_y==food4_y || food4_y==food5_y  )
			 
			{} 
			else
				isNotBody = false;
		}
	}
	
	isNotBody = true;
	while (isNotBody) 
	{
		food5_x = rand()%(grid_size-3)+1;
		food5_y = rand()%(grid_size-3)+1;
		
		if ((grid[food5_x][food5_y]  == FOREST_GREEN))//!= MAROON) && (grid[food5_x][food5_y] != GOLD))
		{
			if(food5_x==food2_x || food5_x==food3_x || food5_x==food4_x || food1_x==food5_x ||
			   food5_y==food2_y || food5_y==food3_y || food5_y==food4_y || food1_y==food5_y  )
			{} 
			else
				isNotBody = false;
		}
	}
	
	grid[food1_x][food1_y] = POWDER_BLUE;
	grid[food2_x][food2_y] = POWDER_BLUE;
	grid[food3_x][food3_y] = POWDER_BLUE;
	grid[food4_x][food4_y] = POWDER_BLUE;
	grid[food5_x][food5_y] = POWDER_BLUE;	
	
	
	if (bonusTurn == 4) //calculating the bonus elemrent with reference of glutTimerFunc...as it keeps the food on screen for 15 secs...as 15 x 4 =60
	{
		grid[food_x][food_y] = FOREST_GREEN;
		isNotBody = true;
		
		while (isNotBody) 
		{
			food_x = rand()%(grid_size-3)+1;
			food_y = rand()%(grid_size-3)+1;
			
			if ((grid[food_x][food_y]  == FOREST_GREEN))//!= MAROON) && (grid[food_x][food_y] != GOLD))
				isNotBody = false;
		}		
		grid[food_x][food_y] = PURPLE;
		bonusTurn++;
		
		/*for (int i = 0; i < grid_size; i++)
		{
			for (int j = 0;j< grid_size; j++)
			{	
				if((j>=10 && j<=20 )&&(i==10 ))// removal of hurdle....in u shape
					grid[i][j] = FOREST_GREEN;	
				if((j>=10 && j<=20 )&&(i==20))
					grid[i][j] = FOREST_GREEN;	
				if((i>=10 && i<=20 )&&(j==10 ))
					grid[i][j] = FOREST_GREEN;	
			}
		}*/
					
	}
	
	else if(bonusTurn==5)
	{
		bonusTurn++;
		for (int i = 8; i < grid_size-8; i++)
		{
			for (int j = 0;j< grid_size; j++)
			{
						
				if(i==j)//hurdle in shape of z
					grid[i][j] = GOLD;
					
			}
		}
	}
	 
	else if (bonusTurn==6)
	{
		for (int i = 8; i < grid_size-8; i++)
		{
			for (int j = 0;j< grid_size; j++)
			{
				if(i==j)//removal of hurdle in shape of /
				grid[i][j] = FOREST_GREEN;	
			}
		}
						
		for (int i = 0; i < grid_size; i++)
		{
			for (int j = 0;j< grid_size; j++)
			{
				if(j>=4 && j<=12 &&(i==5))// hurdle.....five vertical lines appears
					grid[i][j] = GOLD;
				if(j>=8 && j<=16 &&(i==10))
					grid[i][j] = GOLD;
				if(j>=12 && j<=20 &&(i==15))
					grid[i][j] = GOLD;
				if(j>=16 && j<=24 &&(i==20))
					grid[i][j] = GOLD;
				if(j>=20 && j<=28 &&(i==25))
					grid[i][j] = GOLD;
			}
		}								
	bonusTurn = 0;
	}

	else 
	{
		bonusTurn++;
		if(bonusTurn==1)
		{
			for (int i = 0; i < grid_size; i++)			
			{
				for (int j = 0;j< grid_size; j++)
				{
					if((j>=10 && j<=26 )&&(i==10 ))//1st hurdle .....in l shape
						grid[i][j] = GOLD;	
					if((i>=10 && i<=17 )&&(j==10 ))
						grid[i][j] = GOLD;	
			
					if(j>=4 && j<=12 &&(i==5))// hurdle.....five vertical lines appears
						grid[i][j] = FOREST_GREEN;
					if(j>=8 && j<=16 &&(i==10))
						grid[i][j] = FOREST_GREEN;
					if(j>=12 && j<=20 &&(i==15))
						grid[i][j] = FOREST_GREEN;
					if(j>=16 && j<=24 &&(i==20))
						grid[i][j] = FOREST_GREEN;
					if(j>=20 && j<=28 &&(i==25))
						grid[i][j] = FOREST_GREEN;
				}
			}		
			
		}		
		
		if(bonusTurn==2)
		{
			for (int i = 0; i < grid_size; i++)
			{
				for (int j = 0;j< grid_size; j++)
				{
					if((j>=10 && j<=26 )&&(i==10 ))//removal of l shape
						grid[i][j] = FOREST_GREEN;	
					if((i>=10 && i<=17 )&&(j==10 ))
						grid[i][j] =FOREST_GREEN;
						
					if(i>=8 && i<=16 &&(j==10))//2nd hurdle....3 horizontal lines
						grid[i][j] = GOLD;
					if(i>=12 && i<=20 &&(j==15))
						grid[i][j] = GOLD;
					if(i>=16 && i<=24 &&(j==20))
						grid[i][j] = GOLD;		
				}
			}
		}
		
		if(bonusTurn==3)
		{
			for (int i = 0; i < grid_size; i++)
			{
				for (int j = 0;j< grid_size; j++)
				{	
					if(i>=8 && i<=16 &&(j==10))//removal of hurdle in shape of 3 horizontal lines
						grid[i][j] = FOREST_GREEN;
					if(i>=12 && i<=20 &&(j==15))
						grid[i][j] = FOREST_GREEN;
					if(i>=16 && i<=24 &&(j==20))
						grid[i][j] = FOREST_GREEN;	
						
					if((j>=10 && j<=20 )&&(i==10 ))// hurdle....in u shape
						grid[i][j] = GOLD;	
					if((j>=10 && j<=20 )&&(i==20))
						grid[i][j] = GOLD;	
					if((i>=10 && i<=20 )&&(j==10 ))
						grid[i][j] = GOLD;			
				}
			}
		}
		
		
	
	}
	
// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(75000.0 / FPS, Timer, 0);
	// 5000.0 FPS = 1 sec
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) 
{

	int width = 600, height = 600; // i have set my window size to be 800 x 600
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("PF's Snake Game"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...



	for (int i=0; i < grid_size; i++) 
	{
		for (int j=0; j < grid_size; j++) 
		{
			if (i == snake_head_x && j == snake_head_y) 
				grid[i][j] = MAROON;
			else if (i == snake_tail1_x && j == snake_tail1_y) 
				grid[i][j] = MAROON;
			else if (i == snake_tail2_x && j == snake_tail2_y)
				grid[i][j] = MAROON;
			else if (i == mid_x && j == mid_y) 
				grid[i][j] = MAROON;
			else if (i == mid1_x && j == mid1_y) 
				grid[i][j] = MAROON;
					
			else 
				grid[i][j] = FOREST_GREEN;
		}
	}
	
	for (int i = 0; i < grid_size; i++)//this will add boundaries to the snake board
	{
	    for (int j = 0;j< grid_size; j++)
		{
			if(i==0 || i==grid_size-1 || j==0 || j==grid_size-1)
				grid[i][j] = GOLD;
		}
	}
	
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(5.0 / FPS, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Snake Game */

