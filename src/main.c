#include<stdio.h>
#include"SAT.h"
#include"Hanidoku.h"
/*ȫ�ֱ���*/
int vnum;
int cnt = 0;
int opt;
Counter counter[1000][MAX];
/*������*/
int main(void)
{
	int op = 1, op_1 = 1, op_H = 1;
	int flag = 0;
	char digit[65];
	while (op) {
		system("cls");
		printf("\n            Menu for SAT or Hanidoku            \n");
		printf("------------------------------------------------------\n");
		printf("            1.SAT                  2.Hanidoku         \n");
		printf("            0.Exit                                    \n");
		printf("------------------------------------------------------\n");
		printf("          Please choose your choices: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			SAT();
			system("pause");
			break;
		case 2:
			op_H = 1;
			while (op_H)
			{
				system("cls");
				printf("\n            Menu for Hanidoku             \n");
				printf("-------------------------------------------\n");
				printf("     1.Initialize        2.Try to solve  \n");
				printf("     3.Answer            0.exit   \n");
				printf("-------------------------------------------\n");
				printf("          Please choose your choices: ");
				scanf("%d", &op_H);
				switch (op_H) {
				case 1:
					printf("-------------------------------------------\n");
					printf("     1.Input digit string        2.Random  \n");
					printf("     0.Exit                                \n");
					printf("-------------------------------------------\n");
					printf("          Please choose your choices: ");
					scanf("%d", &op_1);
					switch (op_1) {
					case 1:
						//�������ִ����ɷ�������
						printf("���������ִ���\n");
						scanf("%s", digit);
						InitHanidoku(digit);
						flag = 1;
						break;
					case 2:
						//�������
						RandomInit();
						flag = 1;
						break;
					case 0:
						break;
					default:
						printf("�������\n");
						system("pause");
						break;
					}
					system("pause");
					break;
				case 2:
					if (flag) {
						TryHanidoku();
						flag = 0;
					}
					else printf("����������δ��ʼ����\n");
					system("pause");
					break;
				case 3:
					if (flag) {
						SolveHanidoku();
						flag = 0;
					}
					else
						printf("���������ļ���δ��ʼ����\n");
					system("pause");
					break;
				case 0:
					break;
				default:
					printf("����������������룡\n");
					system("pause");
					break;
				}
			}//end of case 2
		case 0:
			break;
		default:
			printf("����������������룡\n");
			system("pause");
			break;
		}
	}
	return 0;
}