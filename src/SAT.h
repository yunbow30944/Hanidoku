#pragma once
#ifndef cnf
#define cnf
/*头文件*/
#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include <stdlib.h>
#include<string.h>
/*宏定义*/
#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define MAX 1000
#define OVERFLOW -1
/*状态返回值定义*/
typedef int status;
/*CNF的存储结构*/
typedef struct ClauseNode {//CNF公式结构
	struct LiteralNode* head;//指向子句的首个文字结点
	struct ClauseNode* next;//指向下一个子句
	int info;//当前文字个数
}*ClauseNodeList,ClauseNode;
typedef struct LiteralNode {
	struct LiteralNode* next;//指向下一个文字
	int x;//变元编号
}*LiteralNodeList,LiteralNode;
typedef struct varinfo {//存储变元相关信息
	int val;//counter[i].val的正负表示变元取真或假,0表示未赋值
	int cnt;//变元出现次数
	int positive, negative;//正文字和负文字分别出现次数
	int flag;//是否赋值
}Counter;
/*函数声明*/
status ReadFile(ClauseNodeList* root, const char Filename[]);
status ListTraverse(ClauseNodeList root);
ClauseNodeList FindUnitClause(ClauseNodeList root);
status isEmptyClause(ClauseNodeList root);
status Unit_Strategy(int unit, ClauseNodeList* root);
status RemoveClause(int unit, ClauseNodeList* root);
status FreeClause(ClauseNodeList* r);
status RemoveLiteral(int unit, ClauseNodeList* root);
status DPLL(ClauseNodeList* root);
ClauseNodeList CopyClauses(ClauseNodeList* root);
status AddUnitClause(int var, ClauseNodeList* root);
status SaveSATFile(int result, double total_t, char Filename[]);
status SAT();
#endif