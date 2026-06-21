#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
using namespace std;

// 蛇坐标
struct Point
{
    int x, y;
};

Point snake[100];
int len = 3;
Point food;
int dir = 2; // 1上 2右 3下 4左
int width = 30, height = 20;
bool gameOver = false;

void init()
{
    snake[0].x = width / 2;
    snake[0].y = height / 2;
    snake[1].x = width / 2 - 1;
    snake[1].y = height / 2;
    snake[2].x = width / 2 - 2;
    snake[2].y = height / 2;

    srand((unsigned int)time(NULL));
    food.x = rand() % width;
    food.y = rand() % height;
}

void draw()
{
    system("cls");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                cout << "#";
            else if (j == snake[0].x && i == snake[0].y)
                cout << "@";
            else if (j == food.x && i == food.y)
                cout << "F";
            else
            {
                bool isBody = false;
                for (int k = 1; k < len; k++)
                {
                    if (snake[k].x == j && snake[k].y == i)
                    {
                        cout << "o";
                        isBody = true;
                        break;
                    }
                }
                if (!isBody) cout << " ";
            }
        }
        cout << endl;
    }
    cout << "长度：" << len << "  W上 S下 A左 D右";
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w': if (dir != 3) dir = 1; break;
        case 's': if (dir != 1) dir = 3; break;
        case 'a': if (dir != 2) dir = 4; break;
        case 'd': if (dir != 4) dir = 2; break;
        case 'x': gameOver = true; break;
        }
    }
}

void logic()
{
    // 身体后移
    for (int i = len - 1; i > 0; i--)
        snake[i] = snake[i - 1];

    // 头部移动
    switch (dir)
    {
    case 1: snake[0].y--; break;
    case 2: snake[0].x++; break;
    case 3: snake[0].y++; break;
    case 4: snake[0].x--; break;
    }

    // 撞墙
    if (snake[0].x <= 0 || snake[0].x >= width - 1 ||
        snake[0].y <= 0 || snake[0].y >= height - 1)
        gameOver = true;

    // 撞到自己
    for (int i = 1; i < len; i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            gameOver = true;
    }

    // 吃到食物
    if (snake[0].x == food.x && snake[0].y == food.y)
    {
        len++;
        food.x = rand() % width;
        food.y = rand() % height;
    }
}

int main()
{
    init();
    while (!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(80);
    }
    cout << "\n游戏结束！";
    return 0;
}