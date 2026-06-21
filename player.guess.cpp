#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand((unsigned int)time(NULL));
    int target = rand() % 100 + 1;
    int guess;
    cout << "=== 猜数字游戏 ===" << endl;
    cout << "系统生成1~100数字，你来猜：" << endl;

    while (true)
    {
        cin >> guess;
        if (guess > target)
            cout << "太大了，再小一点：";
        else if (guess < target)
            cout << "太小了，再大一点：";
        else
        {
            cout << "恭喜猜对！游戏结束" << endl;
            break;
        }
    }
    return 0;
}