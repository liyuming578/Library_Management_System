#include"Library.h"


void InitLibrary(BTree &L) {
	L = NULL;
}

void InsertBook(BTree &L, BookType B, result res) {
	//���L�Ѵ��ڣ�res����B�������L�е�λ�û�Ӧ�ò����λ��
	//���������Ѵ���B�飬��ֻ��B��Ŀ�������ӣ��������B�鵽���L��

	if (res.tag == 0) InsertBTree(L, B->booknum, res.pt, res.i, B);
	//����в����ڸ��飬�����
	else {
		BookType b = res.pt->recptr[res.i];
		b->current = b->current + B->total;//�ִ�������
		b->total = b->total + B->total;//�ܿ������
	}
}

int DeleteBook(BTree &L, BookType B) {
	//�������д���B�飬��������ɾ��B�����Ϣ��������OK�����򷵻�ERROR
	if (DeleteBTree(L, B->booknum)) return OK;//ɾ���ɹ�
	else return ERROR;//ɾ��ʧ��
}

int CanBorrow(BTree L, BookType B, ReaderType R) {
	//�������д���B�飬��B���ִ�������0����ɳ��践��OK�����򷵻�ERROR
	if(B->current>0) return TRUE;//�ִ���������
	else return FALSE;//������������������
}

void	BorrowBook(BTree L, BookType B, ReaderType R)
// ���L���ڣ�B��������е��鲢�ҿɱ�����R���ģ���ͨ��CanBorrow()�жϣ�
// ���һ��B�飬�Ǽǽ�����R����Ϣ���ı��ִ�������¼�������ڣ����Ӧ�����ڵ���Ϣ��
{
	ReaderType	r;
	if (!B->reader) B->reader = R;				// �����������ߣ���ֱ�ӵǼ�
	else {
		for (r = B->reader; r->rnext; r = r->rnext);
		r->rnext = R;							// ���򵽽���������β���Ǽ�
	}
	B->current--;								// �ִ�����1

}

int ReturnBook(BTree L, int booknum, int IDnum, BookType &B, ReaderType &R) {
	//booknumΪ������ţ�IDnum�ǽ����ߵ�ID��
	//������в��������Ϊbooknum���飬��������������-1
	//���н��ļ�¼����ע���ü�¼������B��R����ͼ����Ϣ�ͽ�������Ϣ������1
	//��û��r���ĵļ�¼������B����ͼ����Ϣ��������0
	result res = SearchBTree(L, booknum); //��B���ϰ��������
	if (res.tag == 0) return -1;
	B = res.pt->recptr[res.i];
	ReaderType p = res.pt->recptr[res.i]->reader, pre = p;
	while (p) {
		if (pre == p&&p->IDnum == IDnum) {
			R = p;
			B->current++;//�ִ�����һ
			return 1;
		}
		if (p->IDnum == IDnum) {//���������
			R = p;
			pre->rnext = p->rnext;
			B->current++;//�ִ���+1
			return 1;
		}
		pre = p;
		p = p->rnext;
	}
	return 0;
}

void PrintH() {//���ͷ����ʽ
	printf("\n");
	printf("|*********************************ͼ�������Ϣ**********************************|\n"); 
	printf("|  ���  |       ����         |      ����     | �ִ� | �ܿ�� | ������� | ���� |\n");
}

void PrintB(BookType B) { //��ʾB�������Ϣ
	printf("|--------|--------------------|---------------|------|--------|----------|------|\n");
	printf("|  %-4d  |%-20s|%-15s|", B->booknum,B->bookname,B->writer);
	printf(" %-5d|   %-4d | %-6d   |%-6.1f|\n",  B->current, B->total, B->published_year, B->price);
}

void PrintT() {//���ײ���ʽ
	printf("|--------|--------------------|---------------|------|--------|----------|------|\n");
}

void PrintAll(BTree p) {//��ʾB��ÿ�����ļ�¼��Ϣ
	int i;
	for (i = 1; i <= p->keynum; ++i) {
		PrintB(p->recptr[i]);
	}
}

void PrintBook(BookType B) {//�Ա����ʽ��ʾһ����Ļ�����Ϣ
	PrintH();
	PrintB(B);
	PrintT();
	printf("\n");
}

void PrintBorrower(ReaderType R) {//�Ա����ʽ��ʾһ����Ľ�������Ϣ
	ReaderType p = R;
	printf("|------------------------|\n");
	while (p) {
		printf("|  %-5d  |  %-10s  |\n", p->IDnum, p->reader_name);
		p = p->rnext;
	}
	printf("|------------------------|\n");
}

void PrintAllbooks(BTree L) {//��ʾ���L����ͼ����Ϣ
	PrintH();
	BTreeTraverse(L, PrintAll);
	PrintT();
}

int ShowBookinfo(BTree L, int booknum) {
	//�����L�д������Ϊbooknum���飬�����ڸ����������Ϣ������OK�����L��������
	//����ERROR
	result res = SearchBTree(L, booknum);
	if (!res.tag) return ERROR;
	BookType B = res.pt->recptr[res.i];
	PrintBook(B);
	return OK;
}

void 	gotoxy(short x, short y)
// �ƶ���굽��x��y�����꣬25>x>=0,80>y>=0	
{
	COORD point = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void 	SetColor(unsigned short TextColor)
// ��������ͱ�����ɫ
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, TextColor);
}

void	Welcome(int color)
// ��ʾ��ӭ����
{
	SetColor(color);
	gotoxy(2, 5);

	SetColor(10);
	printf("                                             �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("                                               �U Welcome to Library!!      \n");
	printf("                                               �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("                                                ��������ͼ�����ϵͳ\n");
	SetColor(color+1);
}

void	Creat(BTree &L) {
	// **********************************************************************************
	// ��������������ʾ�˵�ʱ��8���ɽ��뱾����������
	// LΪ��⡣
	// ��ָ���ļ�����ͼ����Ϣ����ͼ����⡣
	// Ȼ����ļ�������������֣����������������֤�źͽ�����ţ�����ͼ����ģ�����¼��־��
	// ���Ŷ���ԤԼ�����֣����������������֤�ź�ͼ��֤�ţ�����ͼ��ԤԼ������¼��־
	// ��ɺ󼴿ɷ������˵������л��顢ԤԼ���������ԡ�
	FILE		*fp;
	BookType	B;
	result		res;
	errno_t err;
	ReaderType	R;
	//fp = fopen_s(bookinfomationfile, "r");				// ��ͼ����Ϣ�ļ�
	if ((err = fopen_s(&fp, "bookinfo.dat", "r")) != 0)
	{
		printf("���ܴ�ͼ����Ϣ�ļ�,��ȷ��%s�ļ��ѷŵ��̸�Ŀ¼...", bookinfomationfile);
		getchar();
		return;
	}
	printf("\n���潫���ļ�%s����ͼ����Ϣ�������������...", bookinfomationfile);
	getchar();
	while (!feof(fp))								// ��δ���ļ�����
	{
		B = (BookType)malloc(sizeof(BookNode));		// ����ͼ��ռ�
		fscanf(fp, "%d %s %s %d %d %d %f", &B->booknum, B->bookname, B->writer, &B->current,
			&B->total, &B->published_year, &B->price);// ����ͼ������
		B->reader = NULL;			// ���ߺͽ�����ָ���ÿ�
		res = SearchBTree(L, B->booknum);			// ���Ҳ���λ��
		if (!res.tag)								// ����в����ڸ��飬�����
		{
			InsertBook(L, B, res);					// ����
			printf("\n\n\n ���������ͼ��");
			PrintBook(B);							// ��ʾ��ͼ��
			printf("\nB����״̬\n\n");
			ShowBTree(L);							// ��ʾ�����B����״̬
		}
	}
	fclose(fp);
	printf("\n\n���������ͼ����Ϣ");
	PrintAllbooks(L);								// ��ʾ����ͼ��
	printf("\n�ļ�ͼ����Ϣ�������!������ļ������������Ϣ�������������...\n");
	getchar();
// **********************************************************************************
	system("cls");
	int		booknum, i = 0;
	fp = fopen(borrowerfile, "r");					// �򿪽����������ļ�
	if (!fp)
	{
		printf("\n\n\n���ܴ򿪶�����Ϣ�ļ�,��ȷ��%s�ļ��ѷŵ��̸�Ŀ¼...", borrowerfile);
		_getch();
		return;
	}

	while (i++ <4000 && !feof(fp))
	{
		R = (ReaderType)malloc(sizeof(ReaderNode));
		fscanf(fp, "%6s", &R->reader_name);					// ���ļ��������������
		R->IDnum = rand() % 100;					// ���������������֤��
		R->rnext = NULL;					// ����������ԤԼ��ָ���ÿ�
		booknum = rand() % 100 + 1;					// ��������������
		res = SearchBTree(L, booknum);				// ����������
		if (res.tag)								// ����ҵ������
		{
			B = res.pt->recptr[res.i];
			if (CanBorrow(L, B, R))					// �жϸý������Ƿ���Խ��ĸ���
			{
				BorrowBook(L, B, R);				// �����������һ��
			}
		}
	}

	fclose(fp);
	PrintAllbooks(L);							// ��ʾ����ͼ�飨���Կ����ִ������٣�
	printf("\n������Ϣ������ϣ����潫���ļ�����ԤԼ����Ϣ�������������....");
	_getch();
}