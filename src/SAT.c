#include"SAT.h"
/*�ⲿ����*/
extern int cnt;
extern int vnum;
extern int opt;
extern Counter counter[1000][MAX];
/*��������*/
int ChooseVar_Strategy1(ClauseNodeList root);
int ChooseVar_Strategy2(ClauseNodeList root);
int ChooseVar_Strategy3(ClauseNodeList root);
int (*ChooseVar[4])(ClauseNodeList root) = { NULL,ChooseVar_Strategy1 ,ChooseVar_Strategy2,ChooseVar_Strategy3 };//����ָ�룬����ѡ�����
/*��������*/
//����cnf�ļ�
//����ReadFile:����CNF�ļ����洢��ʽΪ�ڽ��������ʽ��
status ReadFile(ClauseNodeList* root, const char Filename[])
{
	FILE* fp = NULL;
	char ch, str[10];
	int varnum, clnum;//variable num,clause num;
	int elem;
	int cnt_1;
	int num = 0;
	ClauseNodeList r = NULL, q = NULL;//��ָ��root��q��¼��ǰ�Ӿ��㣻
	LiteralNodeList p = NULL, t = NULL;
	cnt++;
	fp = fopen(Filename, "r");
	if (fp == NULL) {
		printf("�ļ���ʧ��!���������룡\n");
		return ERROR;
	}
	else {
		do {
			fread(&ch, sizeof(char), 1, fp);//ע�Ͳ��ֶ�ȡ
		} while (ch != 'p');
		fread(str, sizeof(char), 5, fp);//cnf��ʽ
		fscanf(fp, "%d", &varnum); vnum = varnum;
		fscanf(fp, "%d", &clnum); cnt_1 = clnum;

		r = (ClauseNodeList)malloc(sizeof(ClauseNode));
		r->next = NULL; r->head = NULL;
		q = r;
		(*root) = r;//��ָ��rootָ���׽��
		while (fscanf(fp, "%d", &elem) != EOF && cnt_1) {
			if (elem) {
				counter[cnt][abs(elem)].flag = 1;

				p = (LiteralNodeList)malloc(sizeof(LiteralNode));
				p->x = elem; p->next = NULL;
				num++;
				if (q->head == NULL) {//�տ�ʼ������ǰ�Ӿ�
					q->head = p;
					t = p;//t��¼��ǰ���ֽ��
				}
				else {
					t->next = p;
					t = p;
				}
			}//end of if
			else {//����0
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
//����ListTraverse������cnf�ļ�
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
//����FindUnitClause���ڸ������Ӿ������в��Ҳ����ص�һ�����Ӿ��ָ�롣
ClauseNodeList FindUnitClause(ClauseNodeList root)
{
	ClauseNodeList temp;
	temp = root;
	while (temp) {
		if (temp->info == 1) return temp;
		temp = temp->next;
	}
	return NULL;//�޵��Ӿ�
}
//����isEmptyClause���ж��Ƿ��п��Ӿ�
status isEmptyClause(ClauseNodeList root)
{
	ClauseNodeList temp;
	temp = root;
	while (temp) {
		if (temp->info == 0) return TRUE;//�п��Ӿ�
		temp = temp->next;
	}
	return FALSE;//�޿��Ӿ�
}
//����Unit_Strategy�����Ӿ䴫��
status Unit_Strategy(int unit, ClauseNodeList* root)//unitΪ���Ӿ���
{
	RemoveClause(unit, root);//ɾ�������Ӿ�unit���Ӿ�
	RemoveLiteral(unit, root);//ɾ����-unit���Ӿ��е�����
	return OK;
}
//ɾ�������Ӿ�unit���Ӿ�
status RemoveClause(int unit, ClauseNodeList* root)
{
	ClauseNodeList temp, pre_temp;
	LiteralNodeList p;
	int flag = 0;//�ж��Ӿ��Ƿ���Ҫɾ��

	temp = *root;
	while (temp) {//ѭ����ֱ���׸��Ӿ䲻��Ҫɾ��
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
	if (*root == NULL) return OK;//�Ѿ�ɾ��

	pre_temp = temp;
	temp = temp->next;
	while (temp) {//һ�����
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
//�ͷſռ�
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
//ɾ����-unit���Ӿ��е�����
status RemoveLiteral(int unit, ClauseNodeList* root)
{
	int target = -unit;
	ClauseNodeList p;
	LiteralNodeList q, pre_q = NULL;
	p = *root;
	while (p) {
		q = p->head;
		if (q == NULL) return FALSE;
		if (q->x == target) {//ɾ���׸�����
			p->head = q->next;
			free(q);
			p->info--;
		}
		else {//һ�����
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
	return root->head->x;//ѡ��һ��
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
	else return root->head->x;//ѡ��һ��
}
int ChooseVar_Strategy3(ClauseNodeList root)
{//flag
	//������Ӿ�����/���ģ�
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
int choosevar_strategy(ClauseNodeList root)//��Ȩ
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
//���Ƶ�ǰ����
ClauseNodeList CopyClauses(ClauseNodeList* root)
{
	ClauseNodeList p, t, r, copy_root;
	LiteralNodeList q, node, s = NULL;
	p = *root;

	r = (ClauseNodeList)malloc(sizeof(ClauseNode));
	if (!r) exit(OVERFLOW);
	r->next = NULL; r->head = NULL;
	r->info = p->info;
	t = r;//t��¼��ǰ�Ӿ���
	copy_root = r;
	while (p) {
		q = p->head;
		while (q) {
			node = (LiteralNodeList)malloc(sizeof(LiteralNode));
			//if (!node) exit(OVERFLOW);
			node->x = q->x; node->next = NULL;
			if (t->head == NULL) {//�տ�ʼ������ǰ�Ӿ�
				t->head = node;
				s = node;//s��¼��ǰ���ֽ��
			}
			else {
				s->next = node;
				s = node;
			}
			q = q->next;
		}//end of while
		p = p->next;
		if (p == NULL) break;//�Ѿ�����β
		r = (ClauseNodeList)malloc(sizeof(ClauseNode));
		//if (!r) exit(OVERFLOW);
		r->next = NULL; r->head = NULL;
		r->info = p->info;
		t->next = r; t = r;
	}//end of while
	return copy_root;
}
//ͷ�巨���뵥�Ӿ�
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
	//DPLL��Ԫѡȡ�����Ż���VNDS���ԣ�
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

	v = ChooseVar[opt](*root);//��Ԫѡ�����
	(v > 0) ? (counter[cnt][v].val = 1) : (counter[cnt][-v].val = -1);
	ClauseNodeList copy = CopyClauses(root);
	//��ʼ���Ѳ���
	AddUnitClause(v, &copy);
	if (DPLL(&copy)) return TRUE;
	else {
		FreeClause(&copy);//�ͷſռ�
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
	printf("������ѱ��浽��%s\n", Filename);
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

	printf("������cnf�ļ�����\n");
	do {
		scanf("%s", Filename);
	} while (ReadFile(&H, Filename) != OK);
	printf("��ȡ�ɹ�����ѡ���Ƿ������1.�� 0.��\n");
	scanf("%d", &op1);
	if (op1) ListTraverse(H);
	system("pause");
	opt = 2;
	while (opt) {
		printf("------------------------------------------------------\n");
		printf("            1.δ�Ż���             2.�Ż���           \n");
		printf("            0.exit                                    \n");
		printf("------------------------------------------------------\n");
		scanf("%d", &opt);
		if (opt == 0) break;

		copy_H = CopyClauses(&H);
		start_t = clock();
		result = DPLL(&copy_H);
		end_t = clock();

		total_t = ((double)end_t - (double)start_t) / CLOCKS_PER_SEC * 1000;
		printf("��ʱ%.0fms\n", total_t);
		SaveSATFile(result, total_t, Filename);
		system("pause");
	}
	return OK;
}