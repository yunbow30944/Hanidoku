#include"Hanidoku.h"
#include "SAT.h"
/*��������*/
FILE* fp1;
ClauseNodeList H_S;
extern int cnt;
extern int opt;
extern Counter counter[1000][MAX];
const int col_num[10] = { 0,5,6,7,8,9,8,7,6,5 };//ÿһ�е�����
int Board[10][10];//���Ͷ�ά����洢����������
/*��������*/
//��ȡ������cnf�ļ�������cnf���ɽṹ
status InitHanidoku(char digit[65])
{
	//ֱ������cnf����Լ��
	char Filename[50];
	int k = 0;
	int num = 0;

	for (int i = 0; i <= 61 - 1; i++) {
		if (digit[i] - '0') num++;
	}

	printf("������Ҫ�����CNF�ļ�����\n");
	scanf("%s", Filename);
	fp1 = fopen(Filename, "w");
	fprintf(fp1, "p cnf 549 %d\n", 7468 + num);
	//��������
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= i + 4; j++) {
			Board[i][j] = digit[k++] - '0';
			if (Board[i][j])
				fprintf(fp1, "%d 0\n", i * 100 + j * 10 + Board[i][j]);
		}
	}
	for (int i = 6; i <= 9; i++) {
		for (int j = 1; j <= 14 - i; j++) {
			Board[i][j] = digit[k++] - '0';
			if (Board[i][j])
				fprintf(fp1, "%d 0\n", i * 100 + j * 10 + Board[i][j]);
		}
	}
	/*��Լ��*/
	//+������/Ψһ��Լ��(row,col)�������ߣ�
	for (int i = 1; i <= 9; i++) {
		func2(i, col_num[i]);
	}
	/*��Լ��*/
	//������Լ����from,to,col,row)�������У�
	for (int j = 1; j <= 9; j++) {
		func(10 - col_num[j], col_num[j], col_num[j], j);
	}
	//������Լ��(�У��У�num1��num2��
	func3(4, 8, 1, 9); func3(6, 8, 1, 9);

	func3(3, 7, 1, 8); func3(7, 7, 1, 8);
	func3(3, 7, 2, 8); func3(7, 7, 2, 8);
	func3(3, 7, 2, 9); func3(7, 7, 2, 9);

	func3(2, 6, 1, 7); func3(8, 6, 1, 7);
	func3(2, 6, 2, 7); func3(8, 6, 2, 7);
	func3(2, 6, 2, 8); func3(8, 6, 2, 8);
	func3(2, 6, 3, 7); func3(8, 6, 3, 7);
	func3(2, 6, 3, 8); func3(8, 6, 3, 8);
	func3(2, 6, 3, 9); func3(8, 6, 3, 9);

	func3(1, 5, 1, 6); func3(9, 5, 1, 6);
	func3(1, 5, 2, 6); func3(9, 5, 2, 6);
	func3(1, 5, 2, 7); func3(9, 5, 2, 7);
	func3(1, 5, 3, 6); func3(9, 5, 3, 6);
	func3(1, 5, 3, 7); func3(9, 5, 3, 7);
	func3(1, 5, 3, 8); func3(9, 5, 3, 8);
	func3(1, 5, 4, 6); func3(9, 5, 4, 6);
	func3(1, 5, 4, 7); func3(9, 5, 4, 7);
	func3(1, 5, 4, 8); func3(9, 5, 4, 8);
	func3(1, 5, 4, 9); func3(9, 5, 4, 9);
	/*�Խ���Լ��*/
	fun();
	//+
	//������/Ψһ��Լ��(row,col)�������ߣ�
	for (int i = 1; i <= 9; i++) {
		func2_1(i, col_num[i]);
	}
	/*��Լ��*/
	//������Լ����from,to,col,row)�������У�
	for (int j = 1; j <= 9; j++) {
		func_1(10 - col_num[j], col_num[j], col_num[j], j);
	}
	//������Լ��(�У��У�num1��num2��
	func3_1(4, 8, 1, 9); func3_1(6, 8, 1, 9);

	func3_1(3, 7, 1, 8); func3_1(7, 7, 1, 8);
	func3_1(3, 7, 2, 8); func3_1(7, 7, 2, 8);
	func3_1(3, 7, 2, 9); func3_1(7, 7, 2, 9);

	func3_1(2, 6, 1, 7); func3_1(8, 6, 1, 7);
	func3_1(2, 6, 2, 7); func3_1(8, 6, 2, 7);
	func3_1(2, 6, 2, 8); func3_1(8, 6, 2, 8);
	func3_1(2, 6, 3, 7); func3_1(8, 6, 3, 7);
	func3_1(2, 6, 3, 8); func3_1(8, 6, 3, 8);
	func3_1(2, 6, 3, 9); func3_1(8, 6, 3, 9);

	func3_1(1, 5, 1, 6); func3_1(9, 5, 1, 6);
	func3_1(1, 5, 2, 6); func3_1(9, 5, 2, 6);
	func3_1(1, 5, 2, 7); func3_1(9, 5, 2, 7);
	func3_1(1, 5, 3, 6); func3_1(9, 5, 3, 6);
	func3_1(1, 5, 3, 7); func3_1(9, 5, 3, 7);
	func3_1(1, 5, 3, 8); func3_1(9, 5, 3, 8);
	func3_1(1, 5, 4, 6); func3_1(9, 5, 4, 6);
	func3_1(1, 5, 4, 7); func3_1(9, 5, 4, 7);
	func3_1(1, 5, 4, 8); func3_1(9, 5, 4, 8);
	func3_1(1, 5, 4, 9); func3_1(9, 5, 4, 9);
	//-
	//������/Ψһ��Լ��(row,col)�������ߣ�
	for (int i = 1; i <= 9; i++) {
		func2_2(i, col_num[i]);
	}
	///*��Լ��*/
	//������Լ����from,to,col,row)�������У�
	for (int j = 1; j <= 9; j++) {
		func_2(10 - col_num[j], col_num[j], col_num[j], j);
	}
	//������Լ��(�У��У�num1��num2��
	func3_2(4, 8, 1, 9); func3_2(6, 8, 1, 9);

	func3_2(3, 7, 1, 8); func3_2(7, 7, 1, 8);
	func3_2(3, 7, 2, 8); func3_2(7, 7, 2, 8);
	func3_2(3, 7, 2, 9); func3_2(7, 7, 2, 9);

	func3_2(2, 6, 1, 7); func3_2(8, 6, 1, 7);
	func3_2(2, 6, 2, 7); func3_2(8, 6, 2, 7);
	func3_2(2, 6, 2, 8); func3_2(8, 6, 2, 8);
	func3_2(2, 6, 3, 7); func3_2(8, 6, 3, 7);
	func3_2(2, 6, 3, 8); func3_2(8, 6, 3, 8);
	func3_2(2, 6, 3, 9); func3_2(8, 6, 3, 9);

	func3_2(1, 5, 1, 6); func3_2(9, 5, 1, 6);
	func3_2(1, 5, 2, 6); func3_2(9, 5, 2, 6);
	func3_2(1, 5, 2, 7); func3_2(9, 5, 2, 7);
	func3_2(1, 5, 3, 6); func3_2(9, 5, 3, 6);
	func3_2(1, 5, 3, 7); func3_2(9, 5, 3, 7);
	func3_2(1, 5, 3, 8); func3_2(9, 5, 3, 8);
	func3_2(1, 5, 4, 6); func3_2(9, 5, 4, 6);
	func3_2(1, 5, 4, 7); func3_2(9, 5, 4, 7);
	func3_2(1, 5, 4, 8); func3_2(9, 5, 4, 8);
	func3_2(1, 5, 4, 9); func3_2(9, 5, 4, 9);

	fclose(fp1);
	system("cls");
	printf("CNF�ļ��Ѿ����룺%s\n", Filename);
	system("pause");
	printf("-----------------------------------------------\n");
	printf("����������ʼ����ɣ�\n");
	print(Board);
	printf("-----------------------------------------------\n");
	ReadFile(&H_S, Filename);
	return OK;

}
int stack[30], top = 0;
const char* FULLDigit[25] =
{ "5376468549785276434731825676423918548316257652874387549653674",
"5643241325665271433279856424163978535498267687245356387447536",
"2543634651262783544389276556978124375496382325417667853443765",
"5748646237585362476271385474528169338712456654398749687557364",
"5643241325665271433279856424163978535498267687245356387447536",
"5674334257675689346347182541892536723689745524783635261464523",
"5674363521428634573421786547158932654792863386794565347226534",
"3746564857372531464539678256978123437892465624875343651225346",
"3476546853767521437534928659218367486321745487625374859665487",
"2456346231553172463865972465794813274289365386275447358656473",
"4576376948538576945439287669821435776593824487623534257657648",
"5376464231532175464652983727418695353879462652378446783532546",
"5632438465747251366387241524519876357861324637241548653735246",
"5463246521325173643724815668319274534867152765823457438645673",
"7546364237538576424739825656821973437548612689734545612323456",
"2534664253743789655689742331528967426713485432516764875352346",
"2365454736267521434238957636197842552489673473615265723423546",
"6574342356776984358351267454837192676218435475236869485785674",
"5476846253772436858351724665182937476213845374695849578654637",
"5674342531665478327386925434917862573829456625783456431245763"
};
status find(int num)
{
	for (int i = 1; i <= top; i++) {
		if (stack[i] == num) return FALSE;
	}
	return OK;
}
status RandomInit()
{
	char digit[65];
	int num, holes, loc;
	int op;
	srand((unsigned int)time(NULL));

	do {
		num = rand() % 20;
		if (top == 0) break;
	} while (find(num) != OK);
	stack[++top] = num;
	strcpy(digit, FULLDigit[num]);

	system("cls");
	printf("------------------------------------------------------\n");
	printf("      1.Easy          2.Medium          3.Hard       \n");
	printf("------------------------------------------------------\n");
	printf("      Please choose your choices: ");
	scanf("%d", &op);
	//�����ڶ�����
	if (op == 1) {
		holes = rand() % 10 + 11;
	}//11-20
	else if (op == 2) {
		holes = rand() % 10 + 21;
	}//21-30
	else if (op == 3) {
		holes = rand() % 10 + 31;
	}//31-40
	//�ڶ�
	for (int i = 1; i <= holes; i++) {
		do {
			loc = rand() % 61;
		} while (digit[loc] == '0');

		digit[loc] = '0';
	}
	InitHanidoku(digit);
	return OK;
}
status func(int from, int to, int col, int row)
{
	for (int num = from; num <= to; num++) {
		for (int i = 1; i <= col; i++) {
			fprintf(fp1, "%d ", row * 100 + i * 10 + num);
		}
		fprintf(fp1, "0\n");
	}
	return OK;
}
status func2(int row, int col)
{
	/*��Լ��*/
	for (int j = 1; j <= col; j++) {
		for (int num = 1; num <= 9; num++) {
			fprintf(fp1, "%d ", row * 100 + j * 10 + num);
		}
		fprintf(fp1, "0\n");
	}

	for (int j = 1; j <= col; j++) {
		for (int num1 = 1; num1 <= 9; num1++) {
			for (int num2 = num1 + 1; num2 <= 9; num2++) {
				fprintf(fp1, "-%d -%d 0\n", row * 100 + j * 10 + num1, row * 100 + j * 10 + num2);
			}
		}
	}
	//
	for (int num = 1; num <= 9; num++) {
		for (int col_start = 1; col_start <= col; col_start++) {
			for (int col_end = col_start + 1; col_end <= col; col_end++) {
				fprintf(fp1, "-%d ", row * 100 + col_start * 10 + num);
				fprintf(fp1, "-%d ", row * 100 + col_end * 10 + num);
				fprintf(fp1, "0\n");
			}
		}
	}
	return OK;
}
status func3(int row, int col, int num1, int num2)
{
	for (int column = 1; column <= col; column++) {
		fprintf(fp1, "%d ", row * 100 + column * 10 + num1);
		fprintf(fp1, "%d ", row * 100 + column * 10 + num2);
	}
	fprintf(fp1, "0\n");
	return OK;
}
void fun()
{
	//��a�������
	for (int row_1 = 1; row_1 <= 9; row_1++) {
		for (int col_1 = row_1 > 5 ? 5 : row_1; col_1 <= col_num[row_1]; col_1++) {
			a[row_1][col_1].col = row_1;
		}
	}
	for (int row = 1; row <= 5; row++) {
		for (int row_1 = 1; row_1 <= col_num[row]; row_1++) {
			int col_1;
			if (row_1 <= 5) col_1 = row_1 + 5 - row;
			else col_1 = 10 - row;
			a[row_1][col_1].row = row;
		}
	}
	for (int row = 6; row <= 9; row++) {
		for (int col = 1, row_1 = row - 4; col <= 14 - row && row_1 <= 9; col++, row_1++) {
			int col_1;
			if (row_1 <= 5) col_1 = row_1 - row + 5;
			else col_1 = 10 - row;
			a[row_1][col_1].row = row;
			a[row_1][col_1].col = col;
		}
	}
	//��b�������
	for (int row_2 = 1; row_2 <= 5; row_2++) {
		for (int col_2 = 1; col_2 <= col_num[row_2]; col_2++) {
			b[row_2][col_2].row = col_2;
			if (col_2 <= 5) b[row_2][col_2].col = col_2 + 5 - row_2;
			else b[row_2][col_2].col = 10 - row_2;
		}
	}
	for (int row_2 = 6; row_2 <= 9; row_2++) {
		for (int col_2 = 1, row = row_2 - 4; col_2 <= col_num[row_2]; col_2++, row++) {
			b[row_2][col_2].row = row;
			if (row <= 5) b[row_2][col_2].col = row + 5 - row_2;
			else b[row_2][col_2].col = 10 - row_2;
		}
	}

}
status func_1(int from, int to, int col, int row)
{
	for (int num = from; num <= to; num++) {
		for (int i = 1; i <= col; i++) {
			fprintf(fp1, "%d ", a[row][i].row * 100 + a[row][i].col * 10 + num);
		}
		fprintf(fp1, "0\n");
	}
	return OK;
}
status func2_1(int row, int col)
{
	for (int num = 1; num <= 9; num++) {
		for (int col_start = 1; col_start <= col; col_start++) {
			for (int col_end = col_start + 1; col_end <= col; col_end++) {
				fprintf(fp1, "-%d ", a[row][col_start].row * 100 + a[row][col_start].col * 10 + num);
				fprintf(fp1, "-%d ", a[row][col_end].row * 100 + a[row][col_end].col * 10 + num);
				fprintf(fp1, "0\n");
			}
		}
	}
	return OK;
}
status func3_1(int row, int col, int num1, int num2)
{
	for (int column = 1; column <= col; column++) {
		fprintf(fp1, "%d ", a[row][column].row * 100 + a[row][column].col * 10 + num1);
		fprintf(fp1, "%d ", a[row][column].row * 100 + a[row][column].col * 10 + num2);
	}
	fprintf(fp1, "0\n");
	return OK;
}
status func_2(int from, int to, int col, int row)
{
	for (int num = from; num <= to; num++) {
		for (int i = 1; i <= col; i++) {
			fprintf(fp1, "%d ", b[row][i].row * 100 + b[row][i].col * 10 + num);
		}
		fprintf(fp1, "0\n");
	}
	return OK;
}
status func2_2(int row, int col)
{
	for (int num = 1; num <= 9; num++) {
		for (int col_start = 1; col_start <= col; col_start++) {
			for (int col_end = col_start + 1; col_end <= col; col_end++) {
				fprintf(fp1, "-%d ", b[row][col_start].row * 100 + b[row][col_start].col * 10 + num);
				fprintf(fp1, "-%d ", b[row][col_end].row * 100 + b[row][col_end].col * 10 + num);
				fprintf(fp1, "0\n");
			}
		}
	}
	return OK;
}
status func3_2(int row, int col, int num1, int num2)
{
	for (int column = 1; column <= col; column++) {
		fprintf(fp1, "%d ", b[row][column].row * 100 + b[row][column].col * 10 + num1);
		fprintf(fp1, "%d ", b[row][column].row * 100 + b[row][column].col * 10 + num2);
	}
	fprintf(fp1, "0\n");
	return OK;
}
void print(int Board[10][10])
{
	int row = 1;
	for (int i = 10; i > 0; i -= 2) {
		for (int j = 1; j <= i; j++) {
			printf(" ");
		}
		for (int l = 1; l <= 10 - i / 2; l++) {
			printf("/ \\ ");
		}
		printf("\n");

		printf("%d", row++);
		for (int j = 1; j <= i - 2; j++) {
			printf(" ");
		}
		for (int l = 1; l <= 10 - i / 2; l++) {
			printf("| ");
			if (Board[6 - i / 2][l]) printf("%d ", Board[6 - i / 2][l]);
			else printf(". ");
		}
		printf("|");
		for (int j = 1; j <= i - 1; j++) {
			printf(" ");
		}
		printf("\n");
	}

	for (int i = 2; i <= 10; i += 2) {
		for (int j = 1; j <= i; j++) {
			printf(" ");
		}
		for (int l = 1; l <= 10 - i / 2; l++) {
			printf("\\ / ");
		}
		printf("\n");

		if (i == 10) break;

		printf("%d", row++);
		for (int j = 1; j <= i; j++) {
			printf(" ");
		}
		for (int l = 1; l <= (19 - i) / 2; l++) {
			printf("| ");
			if (Board[5 + i / 2][l]) printf("%d ", Board[5 + i / 2][l]);
			else printf(". ");
		}
		printf("|");
		for (int j = 1; j <= i - 1; j++) {
			printf(" ");
		}
		printf("\n");
	}
}
status check()
{
	ClauseNodeList copy;
	copy = CopyClauses(&H_S);
	opt = 2;
	if (DPLL(&copy)) {
		return TRUE;
	}
	else {
		FreeClause(&copy);
		return FALSE;
	}
}
status checkifFULL()
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= col_num[i]; j++) {
			if (!Board[i][j]) return FALSE;
		}
	}
	return TRUE;
}
status TryHanidoku()
{
	int row, col, num;
	int op = 1;
	back stack[100];
	int top = 0;
	while (op) {
		if (op == 3) {
			return OK;
		}
		system("cls");
		printf("��ǰ����������֣�\n");
		print(Board);
		printf("-------------------------------------------\n");
		printf("     1.����        2.������һ�� \n");
		printf("     3.���        4.��� \n");
		printf("     0.Exit                                 \n");
		printf("-------------------------------------------\n");
		printf("          Please choose your choices: ");
		scanf("%d", &op);
		switch (op) {
		case 1:
			printf("\n���������֣�����ʽΪ�� �� ���֣�\n");

			do {
				scanf("%d %d %d", &row, &col, &num);
				if (Board[row][col]) printf("�˴���������,���������룡\n");
				else {
					Board[row][col] = num; AddUnitClause(row * 100 + col * 10 + num, &H_S);
					if (checkifFULL() == TRUE) {
						if (check() == TRUE) {
							printf("Success!\n");
							return OK;
						}
						else printf("Failed!\nPlease check your Hanidoku if there are some mistakes!\n");
					}
					stack[++top].row = row, stack[top].col = col;
					break;
				}
			} while (Board[row][col]);
			system("pause");
			break;
		case 2:
			if (top == 0) {
				printf("�ѵ���ʼ״̬���޷����أ�\n");
				system("pause");
				break;
			}
			Board[stack[top].row][stack[top].col] = 0;
			--top;
			RemoveUnitClause(&H_S);
			system("pause");
			break;
		case 3:
			SolveHanidoku();
			break;
		case 4:
			if (check() == TRUE) printf("Correct!\n");
			else printf("False!���������Ƿ�����\n");
			system("pause");
			break;
		case 0:
			break;
		default:
			printf("����������������룡\n");
			system("pause");
			break;
		}

	}
	return OK;
}
status SolveHanidoku()
{
	int res;
	opt = 2;
	res = DPLL(&H_S);

	if (res) {
		for (int i = 111; i <= 959; i++) {
			if (counter[cnt][i].flag) {
				if (counter[cnt][i].val == 1) {
					Board[i / 100][i / 10 % 10] = i % 10;
				}
			}
		}
		print(Board);
	}
	else printf("�˷��������޽⣡\n");

	return OK;
}