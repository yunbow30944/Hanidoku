#include"SAT.h"
/*外部变量*/
extern int cnt;
extern int vnum;
extern int opt;
extern Counter counter[1000][MAX];
/*函数声明*/
int ChooseVar_Strategy1(ClauseNodeList root);
int ChooseVar_Strategy2(ClauseNodeList root);
int ChooseVar_Strategy3(ClauseNodeList root);
int (*ChooseVar[4])(ClauseNodeList root) = { NULL,ChooseVar_Strategy1 ,ChooseVar_Strategy2,ChooseVar_Strategy3 };//函数指针，便于选择策略
/*函数定义*/
//读入cnf文件
//函数ReadFile:解析CNF文件，存储公式为邻接链表的形式。
status ReadFile(ClauseNodeList* root, const char Filename[])
{
	FILE* fp = NULL;
	char ch, str[10];
	int varnum, clnum;//variable num,clause num;
	int elem;
	int cnt_1;
	int num = 0;
	ClauseNodeList r = NULL, q = NULL;//根指针root，q记录当前子句结点；
	LiteralNodeList p = NULL, t = NULL;
	cnt++;
	fp = fopen(Filename, "r");
	if (fp == NULL) {
		printf("文件打开失败!请重新输入！\n");
		return ERROR;
	}
	else {
		do {
			fread(&ch, sizeof(char), 1, fp);//注释部分读取
		} while (ch != 'p');
		fread(str, sizeof(char), 5, fp);//cnf范式
		fscanf(fp, "%d", &varnum); vnum = varnum;
		fscanf(fp, "%d", &clnum); cnt_1 = clnum;

		r = (ClauseNodeList)malloc(sizeof(ClauseNode));
		r->next = NULL; r->head = NULL;
		q = r;
		(*root) = r;//根指针root指向首结点
		while (fscanf(fp, "%d", &elem) != EOF && cnt_1) {
			if (elem) {
				counter[cnt][abs(elem)].flag = 1;

				p = (LiteralNodeList)malloc(sizeof(LiteralNode));
				p->x = elem; p->next = NULL;
				num++;
				if (q->head == NULL) {//刚开始创建当前子句
					q->head = p;
					t = p;//t记录当前文字结点
				}
				else {
					t->next = p;
					t = p;
				}
			}//end of if
			else {//读到0
				q->info = num;  num = 0;
				if (cnt_1 != 1) {
					r = (ClauseNodeList)malloc(sizeof(ClauseNode));
					r->next = NULL; r->head = NULL;
					q->next = r; q = r;
				}
				cnt_1--;
			}//end of else
		}//end of while
	}
	fclose(fp);
	return OK;
}
//函数ListTraverse：遍历cnf文件
status ListTraverse(ClauseNodeList root)
{
	ClauseNodeList p;
	LiteralNodeList q;
	p = root;
	while (p) {
		q = p->head;
		while (q) {
			printf("%d ", q->x);
			q = q->next;
		}
		printf("\n");
		p = p->next;
	}
	return OK;
}
//DPLL
//函数FindUnitClause：在给定的子句链表中查找并返回第一个单子句的指针。
ClauseNodeList FindUnitClause(ClauseNodeList root)
{
	ClauseNodeList temp;
	temp = root;
	while (temp) {
		if (temp->info == 1) return temp;
		temp = temp->next;
	}
	return NULL;//无单子句
}
//函数isEmptyClause：判断是否有空子句
status isEmptyClause(ClauseNodeList root)
{
	ClauseNodeList temp;
	temp = root;
	while (temp) {
		if (temp->info == 0) return TRUE;//有空子句
		temp = temp->next;
	}
	return FALSE;//无空子句
}
//函数Unit_Strategy：单子句传播
status Unit_Strategy(int unit, ClauseNodeList* root)//unit为单子句编号
{
	RemoveClause(unit, root);//删除含单子句unit的子句
	RemoveLiteral(unit, root);//删除含-unit的子句中的文字
	return OK;
}
//删除含单子句unit的子句
status RemoveClause(int unit, ClauseNodeList* root)
{
	ClauseNodeList temp, pre_temp;
	LiteralNodeList p;
	int flag = 0;//判断子句是否需要删除

	temp = *root;
	while (temp) {//循环，直至首个子句不需要删除
		p = temp->head;
		while (p) {
			if (p->x == unit) {
				flag = 1;
				break;
			}
			p = p->next;
		}
		if (flag) {
			(*root) = (*root)->next;
			FreeClause(&temp); free(temp);
			temp = (*root);
			flag = 0;
		}
		else break;
	}
	if (*root == NULL) return OK;//已经删完

	pre_temp = temp;
	temp = temp->next;
	while (temp) {//一般情况
		p = temp->head;
		while (p) {
			if (p->x == unit) {
				flag = 1;
				pre_temp->next = temp->next;
				FreeClause(&temp); free(temp); temp = NULL;
				break;
			}
			p = p->next;
		}
		if (flag) {
			temp = pre_temp->next;
			flag = 0;
		}
		else {
			pre_temp = pre_temp->next;
			temp = temp->next;
		}
	}
	return OK;
}
//释放空间
status FreeClause(ClauseNodeList* r)
{
	ClauseNodeList p;
	LiteralNodeList q, s;
	p = *r; q = p->head; s = NULL;
	while (q) {
		s = q;
		q = q->next;
		free(s);
	}
	return OK;
}
//删除含-unit的子句中的文字
status RemoveLiteral(int unit, ClauseNodeList* root)
{
	int target = -unit;
	ClauseNodeList p;
	LiteralNodeList q, pre_q = NULL;
	p = *root;
	while (p) {
		q = p->head;
		if (q == NULL) return FALSE;
		if (q->x == target) {//删除首个文字
			p->head = q->next;
			free(q);
			p->info--;
		}
		else {//一般情况
			while (q) {
				pre_q = q;
				q = q->next;
				if (q == NULL) break;
				if (q->x == target) {
					pre_q->next = q->next;
					free(q);
					p->info--;
					break;
				}
			}
		}
		p = p->next;
	}
	return OK;
}
int ChooseVar_Strategy1(ClauseNodeList root)
{
	return root->head->x;//选第一个
}
int ChooseVar_Strategy2(ClauseNodeList root)
{
	//(VNDS)
	ClauseNodeList p;
	LiteralNodeList q;
	int max = 0;
	int choice = 0;
	p = root;

	while (p) {
		q = p->head;
		while (q) {
			if (counter[cnt][abs(q->x)].positive == 0 && counter[cnt][abs(q->x)].negative != 0) return -q->x;
			else if (counter[cnt][abs(q->x)].positive != 0 && counter[cnt][abs(q->x)].negative == 0) return q->x;

			if (counter[cnt][abs(q->x)].cnt > max) {
				max = counter[cnt][abs(q->x)].cnt;
				choice = abs(q->x);
			}
			q = q->next;
		}
		p = p->next;
	}
	if (choice) {
		return counter[cnt][choice].positive > counter[cnt][choice].negative ? choice : -choice;
	}
	else return root->head->x;//选第一个
}
int ChooseVar_Strategy3(ClauseNodeList root)
{//flag
	//最短正子句优先/负的？
	ClauseNodeList p, pchoice;
	int min;
	int choice = 0;
	p = root; min = p->info; pchoice = p;
	while (p) {
		if (p->info == 2 || p->info == 3) return p->head->x;
		if (p->info < min) {
			min = p->info;
			pchoice = p;
		}
		p = p->next;
	}
	return pchoice->head->x;
}
int choosevar_strategy(ClauseNodeList root)//加权
{
	ClauseNodeList p;
	LiteralNodeList q;
	double max = 0;
	double s;
	int choice = 0;
	p = root;
	while (p) {
		q = p->head;
		while (q) {
			if (q->x > 0) s = (double)counter[cnt][abs(q->x)].positive / (1 << (p->info - 1));
			else s = (double)counter[cnt][abs(q->x)].negative / (1 << (p->info - 1));
			if (s > max) {
				max = s;
				choice = q->x;
			}
			q = q->next;
		}
		p = p->next;
	}
	return choice;
}
//复制当前链表
ClauseNodeList CopyClauses(ClauseNodeList* root)
{
	ClauseNodeList p, t, r, copy_root;
	LiteralNodeList q, node, s = NULL;
	p = *root;

	r = (ClauseNodeList)malloc(sizeof(ClauseNode));
	if (!r) exit(OVERFLOW);
	r->next = NULL; r->head = NULL;
	r->info = p->info;
	t = r;//t记录当前子句结点
	copy_root = r;
	while (p) {
		q = p->head;
		while (q) {
			node = (LiteralNodeList)malloc(sizeof(LiteralNode));
			//if (!node) exit(OVERFLOW);
			node->x = q->x; node->next = NULL;
			if (t->head == NULL) {//刚开始创建当前子句
				t->head = node;
				s = node;//s记录当前文字结点
			}
			else {
				s->next = node;
				s = node;
			}
			q = q->next;
		}//end of while
		p = p->next;
		if (p == NULL) break;//已经到结尾
		r = (ClauseNodeList)malloc(sizeof(ClauseNode));
		//if (!r) exit(OVERFLOW);
		r->next = NULL; r->head = NULL;
		r->info = p->info;
		t->next = r; t = r;
	}//end of while
	return copy_root;
}
//头插法插入单子句
status AddUnitClause(int var, ClauseNodeList* root)
{
	ClauseNodeList p;
	LiteralNodeList q;
	p = (ClauseNodeList)malloc(sizeof(ClauseNode));
	p->info = 1; p->head = NULL;
	p->next = *root; *root = p;
	q = (LiteralNodeList)malloc(sizeof(LiteralNode));
	q->x = var; q->next = NULL;
	p->head = q;
	//DPLL变元选取策略优化（VNDS策略）
	counter[cnt][abs(var)].cnt++;
	var > 0 ? counter[cnt][var].positive++ : counter[cnt][-var].negative++;
	return OK;
}
status RemoveUnitClause(ClauseNodeList* root)
{
	ClauseNodeList temp;
	LiteralNodeList p;
	temp = *root;
	if (temp) {
		p = temp->head;
		(*root) = (*root)->next;
		FreeClause(&temp); free(temp);
	}
	return OK;
}
status DPLL(ClauseNodeList* root)
{
	ClauseNodeList p;

	int unit;
	int v;
	while ((p = FindUnitClause(*root)) != NULL) {
		unit = p->head->x;
		(unit > 0) ? (counter[cnt][unit].val = 1) : (counter[cnt][-unit].val = -1);
		Unit_Strategy(unit, root);
		if (*root == NULL) return TRUE;
		else if (isEmptyClause(*root)) return FALSE;
	}

	v = ChooseVar[opt](*root);//变元选择策略
	(v > 0) ? (counter[cnt][v].val = 1) : (counter[cnt][-v].val = -1);
	ClauseNodeList copy = CopyClauses(root);
	//开始分裂策略
	AddUnitClause(v, &copy);
	if (DPLL(&copy)) return TRUE;
	else {
		FreeClause(&copy);//释放空间
		(-v > 0) ? (counter[cnt][-v].val = 1) : (counter[cnt][v].val = -1);
		AddUnitClause(-v, root);
		return DPLL(root);
	}
}
status SaveSATFile(int result, double total_t, char Filename[])
{
	FILE* fp;
	int len;
	len = strlen(Filename);
	Filename[len - 1] = 's', Filename[len - 2] = 'e', Filename[len - 3] = 'r';
	Filename[len] = '\0';
	printf("求解结果已保存到：%s\n", Filename);
	fp = fopen(Filename, "w");
	if (result) {
		fprintf(fp, "s 1\n");
		fprintf(fp, "v ");
		for (int i = 1; i <= vnum; i++) {
			if (counter[cnt][i].val == 1) {
				fprintf(fp, "%d ", i);
			}
			else {//-1
				fprintf(fp, "%d ", -i);
			}
		}
		fprintf(fp, "\n");
	}
	else fprintf(fp, "s 0\n");
	fprintf(fp, "t %d", (int)total_t);
	fclose(fp);
	return OK;
}
status SAT()
{
	ClauseNodeList H, copy_H;
	int result;
	clock_t start_t, end_t;
	double total_t;
	char Filename[100];
	int op1 = 0;

	printf("请输入cnf文件名！\n");
	do {
		scanf("%s", Filename);
	} while (ReadFile(&H, Filename) != OK);
	printf("读取成功，请选择是否遍历：1.是 0.否\n");
	scanf("%d", &op1);
	if (op1) ListTraverse(H);
	system("pause");
	opt = 2;
	while (opt) {
		printf("------------------------------------------------------\n");
		printf("            1.未优化的             2.优化的           \n");
		printf("            0.exit                                    \n");
		printf("------------------------------------------------------\n");
		scanf("%d", &opt);
		if (opt == 0) break;

		copy_H = CopyClauses(&H);
		start_t = clock();
		result = DPLL(&copy_H);
		end_t = clock();

		total_t = ((double)end_t - (double)start_t) / CLOCKS_PER_SEC * 1000;
		printf("用时%.0fms\n", total_t);
		SaveSATFile(result, total_t, Filename);
		system("pause");
	}
	return OK;
}