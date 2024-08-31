/* SnakeGame
Change made by David Wu
Date last changed: 1/23/2023
Class: CS1337.012
Purpose: This is a video game which the player is a snake trying to eat as much fruit as possible without biting its own tail.
Change Log: Add some comment in PlayerInput which originally is called input also added comment in logic class.

            Break down the original class "Logic" now name "gameAdvancement"
            into multiple different class such as directionReceiver, pointSystem, GameOver, and outOfBorder thus each class have its own purpose.
            Also added some output when the game is over such as the death cause bottom of score.

            Added fruitGenerator class.
            Added topBoundary and bottom Boundary class.
            Made the snake tails into "l" instead of "o" to make the head significantly larger for fun.



*/

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int CoordX, CoordY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int snakeTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

void Setup();
void fruitGenerator();
void Screendraw();
void playerInput();
void gameAdvancement();
void directionReceiver();
void pointSystem();
void GameOver();
void outOfBorder();
void topBoundary();
void bottomBoundary();


void Setup()
{
    gameOver = false;
    dir = STOP;
    CoordX = width / 2; //size of coordinate x   for EX( # #) is between coordX distant
    CoordY = height / 2; //size of coordinate y

    fruitGenerator();
    score = 0; //default score to 0
}

void fruitGenerator()
{
    fruitX = rand() % width;
    fruitY = rand() % height;
}
void screenDraw() //So this help set up the whole entire area where snake can function  also the drawing of snake
{
    system("cls"); //system("clear");
    topBoundary();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == CoordY && j == CoordX)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < snakeTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "l";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    bottomBoundary();
    cout << "Score:" << score << endl;
}
void topBoundary()
{
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
}
void bottomBoundary()
{
    for (int i = 0; i < width+2; i++)
            cout << "#";
        cout << endl;
}
void playerInput()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':  //so the player can input 'a' that tell Logic class to move the snake to left
            dir = LEFT;
            break;
        case 'd':      //so the player can input 'd' that tell Logic class t to  move to the right
            dir = RIGHT;
            break;
        case 'w':       //In order to make the snake can input 'w' that tell Logic class t to move forward
            dir = UP;
            break;
        case 's':       //In order to make the snake can input 's' that tell Logic class t to  move backward(aka South)
            dir = DOWN;
            break;
        case 'x':       //So the player can leave the game voluntarily
            gameOver = true;
            cout << "due to player exiting itself by pressing x" << endl;
            break;
        }
    }
}
void gameAdvancement()
{
    //Save the coordinate of the first tail
    int prevX = tailX[0];
    int prevY = tailY[0];

    //Thus the tail follow the head
    int prev2X, prev2Y;
    tailX[0] = CoordX;
    tailY[0] = CoordY;
    for (int i = 1; i < snakeTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    directionReceiver();
    outOfBorder();
    pointSystem();
    GameOver();
}
void directionReceiver()
{
    switch (dir) //so this function receive from Input class in order to move the snake itself
    {
    case LEFT:  //by receiving LEFT from the input it move the snake coord to Left
        CoordX--;
        break;
    case RIGHT: //by receiving RIGHT from the input it move the snake coord to the right
        CoordX++;
        break;
    case UP: //by receiving UP from the input it move the snake coord to the north
        CoordY--;
        break;
    case DOWN: //by receiving DOWN from the input it move the snake coord to the south
        CoordY++;
        break;
    default:
        break;
    }
}
void outOfBorder() //this make sure the snake to come from opposite of map when enter the border
{
    if (CoordX >= width) CoordX = 0; else if (CoordX < 0) CoordX = width - 1;
    if (CoordY >= height) CoordY = 0; else if (CoordY < 0) CoordY = height - 1;
}
void pointSystem()
{
    if (CoordX == fruitX && CoordY == fruitY)   //If the snake bite the fruit it will increase the score by 10
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        snakeTail++;
    }
}
void GameOver(){

    for (int i = 0; i < snakeTail; i++)       //So the game would be over if snake bites it own tail
        if (tailX[i] == CoordX && tailY[i] == CoordY)
          {
            gameOver = true;
            cout << "Gameover due to snake biting itself" << endl;
          }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        screenDraw();
        playerInput();
        gameAdvancement();
        Sleep(10); //sleep(10);
    }
    return 0;
}
