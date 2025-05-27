#pragma once
#ifndef Hanidoku
#define Hanidoku
#include"SAT.h"
/*蜂窝数独转换结构*/
typedef struct back {
	int row, col;
}back;
struct transfer_up {
	int row, col;
}a[10][10];
struct transfer_down {
	int row, col;
}b[10][10];
/*函数声明*/
void fun();
status func(int from, int to, int col, int row);
status func2(int row, int col);
status func3(int row, int col, int num1, int num2);
status func_1(int from, int to, int col, int row);
status func2_1(int row, int col);
status func3_1(int row, int col, int num1, int num2);
status func_2(int from, int to, int col, int row);
status func2_2(int row, int col);
status func3_2(int row, int col, int num1, int num2);
void print(int Board[10][10]);
status InitHanidoku(char digit[65]);
status RandomInit();
status find(int num);
status TryHanidoku();
status SolveHanidoku();
status checkifFULL();
status check();
#endif