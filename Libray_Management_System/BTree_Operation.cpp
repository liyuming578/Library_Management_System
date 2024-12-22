#include "Library.h"

/********************************B���ӿ�ʵ��****************************/

int Search(BTree p, int k) {
	//��B��p�в��ҹؼ���k��λ��i��ʹ��p->node[i].key<=K<p->node[i+1].key
	int i;
	for (i = 0; i < p->keynum&&p->key[i + 1] <= k; i++);
	return i;
}

result	SearchBTree(BTree T, KeyType k)
// ��m��B���ϲ��ҹؼ���k�����ؽ����pt��i��tag���������ҳɹ���������ֵtag=1��ָ��pt
// ��ָ����е�i���ؼ��ֵ���k�����򷵻�����ֵtag=0������k�Ĺؼ���Ӧ������pt��ָ���
// �е�i�͵�i+1���ؼ���֮�䡣
{
	int		i = 1;
	BTree	p = T, q = NULL;						// ��ʼ����pָ������㣬qָ��p��˫��
	int		found = FALSE;
	while (p && !found)
	{
		i = Search(p, k);							// ����k��λ��ʹp->key[i]<=k<p->key[i+1]
		if (i> 0 && k == p->key[i])	found = TRUE;
		else {										// δ�ҵ����������һ��
			q = p;
			p = p->ptr[i];
		}
	}
	if (found) { result	r = { p, i, 1 };	return r; }	// ���ҳɹ�
	else { result	r = { q, i, 0 };	return r; }	// ���Ҳ��ɹ�������k�Ĳ���λ����Ϣ
}

void split(BTree &q, int s, BTree &ap) {
	//��q�����ѳ�������㣬ǰһ�뱣������һ�������½��ap
	int i, n = q->keynum;
	ap = (BTNode*)malloc(sizeof(BTNode));//�����½��ap
	ap->ptr[0] = q->ptr[s];
	for (i = s + 1; i <= M; i++) {//��һ������ap���
		ap->key[i - s] = q->key[i];
		ap->ptr[i - s] = q->ptr[i];
		ap->recptr[i - s] = q->recptr[i];
	}
	ap->keynum = n - s;//����ap�Ĺؼ��ָ���
	ap->parent = q->parent;
	for (i = 0; i <= M - s; i++) {
		if (ap->ptr[i])
			ap->ptr[i]->parent = ap;//��ap���к��ӽ��ָ��ap
	}
	q->keynum = s - 1;//q����ǰһ�뱣�����޸�keynum
}

void newroot(BTree &T, BTree p, int k, BTree ap, Record *recptr) {//�����µĸ����
	T = (BTNode*)malloc(sizeof(BTNode));
	T->keynum = 1;
	T->ptr[0] = p;
	T->ptr[1] = ap;
	T->key[1] = k;
	T->recptr[1] = recptr;  //T������ap�ĸ���ָ��
	if (p != NULL) p->parent = T;
	if (ap != NULL) ap->parent = T;
	T->parent = NULL;//�¸���˫���ǿ�ָ��
}

void Insert(BTree &q, int i, int k, BTree ap, Record *recptr) {//k��ap�ֱ�嵽q->key[i+1]��q->ptr[i+1]
															   //������ؼ���Ϊk�ļ�¼recprt
	int j, n = q->keynum;
	for (j = n; j > i; j--) {
		q->key[j + 1] = q->key[j];//�ؼ���ָ�������һλ
		q->ptr[j + 1] = q->ptr[j];//���ӽ��ָ�������һλ
		q->recptr[j + 1] = q->recptr[j];
	}
	q->key[i + 1] = k;//��ֵ
	q->ptr[i + 1] = ap;
	q->recptr[i + 1] = recptr;
	if (ap != NULL) ap->parent = q;
	q->keynum++;//�ؼ�����+1
}

Status InsertBTree(BTree &T, KeyType k, BTree q, int i, Record *rec)
//  ��m��B��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K�ͼ�¼rec��
//  ���������������˫�������б�Ҫ�Ľ����ѵ�����ʹT����m��B����
{
	BTree ap = NULL;
	int finished = FALSE;
	if (!q)    newroot(T, NULL, k, NULL, rec);	// T�ǿ��������ɽ����ؼ���K�ĸ����*T
	else {
		while (!finished)
		{
			Insert(q, i, k, ap, rec);			// ��k��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]
			if (q->keynum < M) finished = TRUE; // �������
			else {
				split(q, (M + 1) / 2, ap);			// ���ѽ��Q
				k = q->key[(M + 1) / 2];
				rec = q->recptr[(M + 1) / 2];
				if (q->parent)
				{							// ��˫�׽��*q�в���k�Ĳ���λ��
					q = q->parent;
					i = Search(q, k);
				}
				else finished = OVERFLOW;		// ���ڵ��ѷ���Ϊ*q��*ap�������
			}
		}
		if (finished == OVERFLOW)				// ������ѷ���Ϊ���*q��*ap
			newroot(T, q, k, ap, rec);			// �������¸����*T,q��apΪ����ָ��
	}
	return OK;
} //  InsertBTree



void TakePlace(BTree &q, int &i) {
	//*q���ĵ�i���ؼ���Ϊk����q�ĺ�̹ؼ��ִ���q������qָ�������ڽ��
	BTree p = q;
	q = q->ptr[i];
	while (q->ptr[0]) q = q->ptr[0]; //����p�ĺ��
	p->key[i] = q->key[1]; //��¼����
	p->recptr[i] = q->recptr[1];
	i = 1;  //�����Ӧ��ɾ��q��ָ���ĵ�1���ؼ���
}

void Del(BTree q, int i) {
	//ɾ��q��ָ����i���ؼ��ּ����¼
	for (; i < q->keynum; i++) {//�ؼ��ֺͼ�¼ָ��ǰ��
		q->key[i] = q->key[i + 1];
		q->recptr[i] = q->recptr[i + 1];
	}
	q->keynum--;//�ؼ�����Ŀ��1
}

Status	Borrow(BTree q)
// ��q���ֵܽ��ؼ��ִ���(m-1)/2,����ֵܽ��������С������󣩵Ĺؼ��ֵ�˫�׽�㣬
// ����˫�׽����С��(����ڣ��ҽ����ùؼ��ֵĹؼ���������q��,������OK�����򷵻�EREOR��
{
	int	i;
	BTree p = q->parent, b = NULL;					// pָ��q��˫�׽��
	for (i = 0; p->ptr[i] != q; i++);			// ����q��˫��p������λ��
	if (i >= 0 && i + 1 <= p->keynum && p->ptr[i + 1]->keynum > (M - 1) / 2)
	{										// ��q�����ֵܹؼ��ָ�������(m-1)/2
		b = p->ptr[i + 1];						// bָ�����ֵܽ��
		q->ptr[1] = b->ptr[0];					// ����ָ��ҲҪͬ���ƶ�
		q->key[1] = p->key[i + 1];				// �Ӹ��ڵ���i+1���ؼ���
		q->recptr[1] = p->recptr[i + 1];
		p->key[i + 1] = b->key[1];				// b��һ���ؼ������Ƶ����ڵ�
		p->recptr[i + 1] = b->recptr[1];
		for (i = 1; i <= b->keynum; i++)			// b��һ���ؼ������ƣ����ʣ���¼ǰ��һλ
		{
			b->key[i] = b->key[i + 1];
			b->recptr[i] = b->recptr[i + 1];
			b->ptr[i - 1] = b->ptr[i];
		}
	}
	else if (i > 0 && p->ptr[i - 1]->keynum > (M - 1) / 2)
	{										// ��q�����ֵܹؼ��ָ�����Լ(m-1)/2
		b = p->ptr[i - 1];						// bָ�����ֵܽ��
		q->ptr[1] = q->ptr[0];
		q->ptr[0] = b->ptr[b->keynum];
		q->key[1] = p->key[i];					// �Ӹ��ڵ���i���ؼ���
		q->recptr[1] = p->recptr[i];
		p->key[i] = b->key[b->keynum];			// ��b���һ���ؼ������Ƶ����ڵ�
		p->recptr[i] = b->recptr[b->keynum];
	}
	else return ERROR;							// �޹ؼ��ִ���(m-1)/2���ֵ�
	q->keynum++;
	b->keynum--;
	for (i = 0; i <= q->keynum; i++)
		if (q->ptr[i]) q->ptr[i]->parent = q;	// ˢ��q���ӽ���˫��ָ��
	return OK;
}

void Combine(BTree &q) {
	int i, j;
	BTree p = q->parent, b = NULL;//pָ��q�ĸ���
	for (i = 0; p->ptr[i] != q; i++);//����q�ڸ���p�е�����λ��
	if (i == 0) {//��Ϊ0������ϲ�Ϊ�ֵܵĵ�һ���ؼ���
		b = p->ptr[i + 1];
		for (j = b->keynum; j >= 0; j--) {//��b�Ĺؼ��ֺͼ�¼����һλ
			b->key[j + 1] = b->key[j];
			b->recptr[j + 1] = b->recptr[j];
			b->ptr[j + 1] = b->ptr[j];
		}
		b->ptr[0] = q->ptr[0];//�ϲ�
		b->key[1] = p->key[1];
		b->recptr[1] = p->recptr[1];
	}
	else if (i > 0) {//��q�ڸ��׵�����λ�ô���0����ϲ�Ϊ�ֵ�b�����һ���ؼ���
		b = p->ptr[i - 1];
		b->key[b->keynum + 1] = p->key[i];//�ϲ�
		b->recptr[b->keynum + 1] = p->recptr[i];
		b->ptr[b->keynum + 1] = q->ptr[0];
	}
	if (i == 0 || i == 1)//��iΪ0��1���轫�����p�ؼ���ǰ��һλ
		for (; i < p->keynum; i++) {
			p->key[i] = p->key[i + 1];
			p->ptr[i] = p->ptr[i + 1];
			p->recptr[i] = p->recptr[i + 1];
		}
	p->keynum--;
	b->keynum++;
	free(q);
	q = b;   //qָ���޸ĵ��ֵܽ��
	for (i = 0; i <= b->keynum; i++)
		if (b->ptr[i]) b->ptr[i]->parent = b;//ˢ��b���ӽ���˫��ָ��
}


Status	DeleteBTree(BTree &T, KeyType k)
// ��m��B��T��ɾ���ؼ���k�����Ӧ��¼��������OK��
// ��T�ϲ����ڹؼ���k���򷵻�ERROR��
{
	KeyType	x = k;
	BTree	q, b = NULL;
	int		finished = FALSE, i = 1;
	result res = SearchBTree(T, k);				// ��T�в��ҹؼ���k
	if (res.tag == 0) return ERROR;				// δ������
	else
	{
		q = res.pt;								// qָ���ɾ���
		i = res.i;
		if (q->ptr[0]) TakePlace(q, i);			// ��q���������գ�(�ǵײ���)
												// �������̴�֮������qָ�������ڽ��
		Del(q, i);								// ɾ��q��ָ�����е�i���ؼ��ּ���¼
		if (q->keynum >= (M - 1) / 2 || !q->parent)		// ��ɾ����ؼ��ָ�����С��(m-1)/2��q�Ǹ��ڵ�
		{
			finished = TRUE;					// ɾ�����
			if (q->keynum == 0) T = NULL;		// ��q�Ĺؼ��ָ���Ϊ0 ����Ϊ����
		}
		while (!finished)
		{
			if (Borrow(q))	finished = TRUE;	// ��q�������ֵܽ��ؼ��ִ���(m-1)/2,��Ӹ�
												// �ֵܽ������һ����󣨻���С���ؼ��ֵ�
												// ���ڵ㣬�Ӹ��ڵ��һ�ؼ��ֵ�q
			else {								// ��q�����ֵܹؼ��ָ��������ک�m /2��-1
				Combine(q);	// ��q�е�ʣ�ಿ�ֺ�˫���е���عؼ��ֺϲ���q��һ���ֵ���
				q = q->parent;					// ���˫��
				if (q == T && T->keynum == 0)	// ����ɾ���ĸ��ڵ��Ǹ�T��T�Ĺؼ��ָ���Ϊ0
				{
					T = T->ptr[0];				// �¸�	
					T->parent = NULL;
					free(q);					// ɾ��ԭ˫�׽��
					finished = TRUE;
				}
				else if (q->keynum >= M / 2) finished = TRUE;
			}								// �ϲ���˫�׹ؼ��ָ���������(m-1)/2�����
		}
	}
	return OK;
}


void BTreeTraverse(BTree T, void(*visit)(BTree)) {
	//����B��T����ÿ��������visit����
	if (!T) return;
	visit(T);
	for (int i = 0; i <= T->keynum; ++i) {
		if (T->ptr[i]) BTreeTraverse(T->ptr[i], visit);
	}
}

void	ShowBTree(BTree T, short  x)
// �ݹ��԰������ʽ��ʾB��T,ÿ���������Ϊx����ʼ������Ϊ8
{
	if (!T)	return;
	int		i;
	printf("\n");
	for (i = 0; i <= x; i++) putchar(' ');			// ����x
	for (i = 1; i <= T->keynum; i++)
	{
		printf("%d,", T->key[i]);
	}
	for (i = 0; i <= T->keynum; i++)				// �ݹ���ʾ�������ؼ���
		ShowBTree(T->ptr[i], x + 7);
}

int menu() {//�˵�
	int choice;
	printf("\n\n\t\t\t|##############################################|\n");
	printf("\t\t\t|##############################################|\n");
	printf("\t\t\t ______________________________________________|\n");
	printf("\t\t\t|                 ͼ��ݹ���ϵͳ               |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   1.�洢ͼ��           2.���ͼ��            |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   3.����ͼ��           4.�黹ͼ��            |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   5.�鿴ͼ���ȫ��ͼ�� 6.�鿴ĳͼ����Ϣ      |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   7.�鿴ĳ���������Ϣ 8.��ȡͼ����Ϣ        |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   0.�˳�                                     |\n");
	printf("\t\t\t|______________________________________________|\n");
	printf("\t\t\t|##############################################|\n");
	printf("\t\t\t|##############################################|\n");
	printf("\t\t\t|              ��Ϣ��ȫ��1����                 |\n");
	printf("\t\t\t|                 3119005419                   |\n");
	printf("\t\t\t|                   ������                     |\n");
	printf("\t\t\t|##############################################|\n");
	do {
		printf("\t\t\t��ѡ���ܣ�����0-8����һ�����֣�:");
		scanf_s("%d", &choice);
	} while (choice < 0 || choice > 8);//����Ƿ�����
	return choice;
}


void gotoxy(HANDLE hOut, int x, int y) {//��λ���
	COORD pos;
	pos.X = x;             //������
	pos.Y = y;            //������
	SetConsoleCursorPosition(hOut, pos);
}


int login() {//��½����
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//������ʾ���������
	int secret_code, i;
	printf("\n\n\t\t\t ______________________________________\n");
	printf("\t\t\t|                                      |\n");
	printf("\t\t\t|                                      |\n");
	printf("\t\t\t|            ���������룡       |\n");
	printf("\t\t\t|            ���룺____                |\n");//����Ϊ5419
	printf("\t\t\t|______________________________________|\n");
	gotoxy(hOut, 43, 6);
	scanf_s("%d", &secret_code);
	fflush(stdin);


	printf("\n\t\t\tLoding��");//���붯��
	for (i = 0; i<11; i++) {
		Sleep(50);
		printf(". ");
	}
	printf("\n\t\t\t������ɣ�������һ��ϵͳ");
	Sleep(1000);
	system("cls");//����

	if (secret_code == Super_Manager_Code)//�ж��ǲ��ǹ���Ա
		return 1;
	else
		return 0;
}