#pragma once
#ifndef cnf
#define cnf
/*ͷ�ļ�*/
#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include <stdlib.h>
#include<string.h>
/*�궨��*/
#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define MAX 1000
#define OVERFLOW -1
/*״̬����ֵ����*/
typedef int status;
/*CNF�Ĵ洢�ṹ*/
typedef struct ClauseNode {//CNF��ʽ�ṹ
	struct LiteralNode* head;//ָ���Ӿ���׸����ֽ��
	struct ClauseNode* next;//ָ����һ���Ӿ�
	int info;//��ǰ���ָ���
}*ClauseNodeList,ClauseNode;
typedef struct LiteralNode {
	struct LiteralNode* next;//ָ����һ������
	int x;//��Ԫ���
}*LiteralNodeList,LiteralNode;
typedef struct varinfo {//�洢��Ԫ�����Ϣ
	int val;//counter[i].val��������ʾ��Ԫȡ����,0��ʾδ��ֵ
	int cnt;//��Ԫ���ִ���
	int positive, negative;//�����ֺ͸����ֱַ���ִ���
	int flag;//�Ƿ�ֵ
}Counter;
/*��������*/
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