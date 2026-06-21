#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// 定义数独游戏类
class SudokuGame {
private:
    int board[9][9];      // 9x9 的数独棋盘
    int original[9][9];   // 记录初始状态，用于判断哪些数字是玩家不能修改的

    // 检查在 (row, col) 位置填入 num 是否合法
    bool isValid(int row, int col, int num) {
        for (int i = 0; i < 9; ++i) {
            // 检查当前行和当前列
            if (board[row][i] == num || board[i][col] == num) return false;

            // 检查 3x3 的小九宫格
            int boxRow = 3 * (row / 3) + i / 3;
            int boxCol = 3 * (col / 3) + i % 3;
            if (board[boxRow][boxCol] == num) return false;
        }
        return true;
    }

    // 使用回溯法生成一个完整的数独解（用于初始化）
    bool solve() {
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] == 0) { // 找到空格
                    for (int num = 1; num <= 9; ++num) {
                        if (isValid(row, col, num)) {
                            board[row][col] = num;
                            if (solve()) return true; // 递归尝试下一步
                            board[row][col] = 0;      // 回溯：如果走不通，恢复为0
                        }
                    }
                    return false; // 1-9都试过了都不行，返回false
                }
            }
        }
        return true; // 所有格子都填满了，成功
    }

public:
    // 构造函数：生成一局新游戏
    SudokuGame() {
        srand(time(0));
        // 1. 先清空棋盘
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                board[i][j] = 0;

        // 2. 随机生成一个完整的合法数独
        solve();

        // 3. 保存完整解，然后随机挖空（这里简单挖掉40个格子）
        int blanks = 40;
        while (blanks > 0) {
            int r = rand() % 9;
            int c = rand() % 9;
            if (board[r][c] != 0) {
                board[r][c] = 0;
                blanks--;
            }
        }

        // 4. 记录初始状态
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                original[i][j] = board[i][j];
    }

    // 打印当前棋盘
    void printBoard() {
        system("cls"); // Windows清屏，如果是Mac/Linux请改成 system("clear");
        cout << "====== 简易数独 ======\n";
        cout << "   ";
        for (int c = 0; c < 9; ++c) cout << c << " ";
        cout << "\n";

        for (int r = 0; r < 9; ++r) {
            if (r % 3 == 0 && r != 0) cout << "   -----------------\n";
            cout << r << " | ";
            for (int c = 0; c < 9; ++c) {
                if (c % 3 == 0 && c != 0) cout << "| ";
                if (board[r][c] == 0) cout << ". ";
                else cout << board[r][c] << " ";
            }
            cout << "\n";
        }
        cout << "======================\n";
    }

    // 玩家填入数字
    bool makeMove(int row, int col, int num) {
        if (original[row][col] != 0) {
            cout << ">> 错误：不能修改题目自带的数字！\n";
            return false;
        }
        if (num < 1 || num > 9) {
            cout << ">> 错误：数字必须在 1-9 之间！\n";
            return false;
        }
        board[row][col] = num;
        return true;
    }

    // 检查是否通关（棋盘没有0了）
    bool isWin() {
        for (int r = 0; r < 9; ++r)
            for (int c = 0; c < 9; ++c)
                if (board[r][c] == 0) return false;
        return true;
    }
};

int main() {
    SudokuGame game;
    int r, c, num;

    while (true) {
        game.printBoard();
        cout << "请输入 行(0-8) 列(0-8) 数字(1-9) (输入 -1 -1 -1 退出): ";
        cin >> r >> c >> num;

        if (r == -1) break;

        game.makeMove(r, c, num);

        if (game.isWin()) {
            game.printBoard();
            cout << " 恭喜你，成功通关！\n";
            break;
        }
    }
    return 0;
}