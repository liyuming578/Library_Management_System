#include"Library.h"

int main() {
	BTree L = NULL;
	BookType B;
	result res;
	ReaderType R;
	int booknum, IDnum, k, book_num;
	char flag;
	int i;
	for (i = 0; i <= 10; i++) {			// ��ʾ��ӭ����
		Welcome(i % 16);
		Sleep(100);
	}
	Sleep(800);
	system("cls");//����
	if (login()) {
		for (;;) {
			switch (menu())
			{
			case 1://�洢ͼ��
				B = (BookType)malloc(sizeof(BookNode));
				B->reader = NULL;
				printf("������Ҫ������ţ�\n");
				fflush(stdin);
				scanf_s("%d", &B->booknum);
				getchar();
				res = SearchBTree(L, B->booknum);
				if (!res.tag) {
					fflush(stdin);
					printf("���������������\n");
					fflush(stdin);
					gets_s(B->bookname);
					printf("������������ߣ�\n");
					fflush(stdin);
					gets_s(B->writer);
					printf("�������������\n");
					fflush(stdin);
					scanf_s("%d", &B->current);
					printf("�����������ݣ�\n");
					fflush(stdin);
					scanf_s("%d", &B->published_year);
					printf("�������鱾�۸�\n");
					fflush(stdin);
					scanf_s("%f", &B->price);
					B->total = B->current;
					InsertBook(L, B, res);
					printf("�ð������ʽ��ʾB�����£�\n");
					ShowBTree(L, 8);
					break;
				}
				else {//ͼ���Ѵ��ڣ�ֻ���ӿ��
					printf("������и����¼�����������ӵĲ�����\n");
					fflush(stdin);
					scanf_s("%d", &B->total);
					InsertBook(L, B, res);
					B = res.pt->recptr[res.i];
					printf("�ð������ʽ��ʾB�����£�\n");
					ShowBTree(L);
					printf("������������ɣ�\n");
					system("pause");
					break;
				}


			case 2://���ͼ��
				printf("������Ҫɾ����ͼ����ţ�\n");
				fflush(stdin);
				scanf_s("%d", &booknum);
				res = SearchBTree(L, booknum);
				if (res.tag) {
					B = res.pt->recptr[res.i];
					PrintBook(B);
					printf("\n��ȷ��ɾ�������ͼ��<Yȷ�ϣ����ఴ���������˵�>?");
					fflush(stdin);
					getchar();
					flag = getchar();
					if (flag == 'Y' || flag == 'y') {
						DeleteBook(L, B);
						printf("\n�����ϣ�\tɾ�����ð������ʾB�����£�\n");
						ShowBTree(L, 8);
					}
				}
				else {
					printf("\n��ⲻ���ڴ��飬ɾ��ʧ�ܣ�\n");
				}
				printf("\t");
				system("pause");
				break;
			case 3://����ͼ��
				R = (ReaderType)malloc(sizeof(ReaderNode));
				R->rnext = NULL;
				printf("���������ͼ����ţ�\n");
				fflush(stdin);
				scanf_s("%d", &booknum);
				getchar();
				res = SearchBTree(L, booknum);
				if (res.tag) {
					B = res.pt->recptr[res.i];
					printf("����������������\n");
					fflush(stdin);
					gets_s(R->reader_name);
					printf("����������ID�ţ�\n");
					fflush(stdin);
					scanf_s("%d", &R->IDnum);
					if (CanBorrow(L, B, R)) {
						BorrowBook(L, B, R);
						printf("\n������ɣ�");
					}
					else {
						printf("\n��治�㣬����ʧ�ܣ�");
						free(R);
					}
				}
				else {
					printf("\n����޴��飬����ʧ�ܣ�");
					free(R);
				}
				printf("\t");
				system("pause");
				break;
			case 4://�黹ͼ��
				printf("\n������ͼ��ţ�\n");
				scanf_s("%d", &booknum);
				printf("����������ID�ţ�\n");
				scanf_s("%d", &IDnum);
				k = ReturnBook(L, booknum, IDnum, B, R);
				if (k == 1) {
					printf("\n������ɣ�");
					R = NULL;
				}
				else if (k == 0) {
					printf("\n����ʧ�ܣ�ϵͳû����������¼��");
				}
				else {
					printf("\n����в����ڴ���!");
				}
				printf("\t");
				system("pause");
				break;
			case 5://����ܿ��
				printf("ͼ����ܿ����Ϣ���£�\n");
				PrintAllbooks(L);
				break;
			case 6://����ĳ��ͼ��
				printf("������Ҫ���ҵ�ͼ��ı�ţ�\n");
				scanf_s("%d", &book_num);
				ShowBookinfo(L, book_num);
				break;
			case 7://���ĳͼ��Ľ�������Ϣ
				printf("������Ҫ���ҵ�ͼ��ı�ţ�\n");
				scanf_s("%d", &book_num);
				res = SearchBTree(L, book_num);
				if (res.tag) {
					B = res.pt->recptr[res.i];
					printf("��������Ϣ���£�\n");
					PrintBorrower(B->reader);
				}
				else {
					printf("\n��ⲻ���ڴ��飬����ʧ�ܣ�\n");
				}
				printf("\t");
				system("pause");
				break;
			case 8:Creat(L);
				system("cls");
				break;
			case 0:  //�˳�����ϵͳ
				exit(0);
			default:
				break;
			}
		}
	}
	else {
		printf("�����������\n");
		system("pause");
	}
	return 0;
}