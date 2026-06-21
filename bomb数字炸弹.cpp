#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    // 设置随机种子
    srand((unsigned int)time(NULL));
    int bomb = rand() % 51; // 生成0~50炸弹数字
    int minNum = 0, maxNum = 50;
    int input;

    cout << "数字炸弹小游戏\n";
    cout << "规则：炸弹藏在0~50之间，输入数字缩小范围，踩到炸弹游戏结束\n\n";

    while (true)
    {
        cout << "当前安全区间：" << minNum << " ~ " << maxNum << endl;
        cout << "请输入一个区间内数字：";
        cin >> input;

        // 校验输入是否在合法区间
        if (input <= minNum || input >= maxNum)
        {
            cout << "输入超出当前区间，重新输入！\n\n";
            continue;
        }

        // 踩到炸弹，游戏结束
        if (input == bomb)
        {
            cout << "轰！你踩到数字炸弹" << bomb << "了，游戏结束！";
            break;
        }
        // 缩小区间
        else if (input < bomb)
        {
            cout << "安全！炸弹在更大的数字区间\n\n";
            minNum = input;
        }
        else
        {
            cout << "安全！炸弹在更小的数字区间\n\n";
            maxNum = input;
        }
    }
    return 0;
}