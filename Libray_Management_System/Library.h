#pragma once
#include	"windows.h"
#include	"stdio.h"
#include	"conio.h"
#include	"stdlib.h"
#include	"malloc.h"
#include	"time.h"
#include    "string.h"
#include    "errno.h"


#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define OK 1
#define ERROR 0
#define M 3//�������
#define Super_Manager_Code 5419  //��������Ա����
#define MAX_NAME_LEN 20//��������
#define MAX_BKNAME_LEN 50
#define OK 1
#define ERROR 0
#define	bookinfomationfile "bookinfo.dat"	// ͼ����Ϣ�ļ�
#define	borrowerfile "borrower.dat"		// �����������ļ�
typedef int KeyType;
typedef int Status;

/*****************************��ͽ����߽��洢����*************************/
typedef struct ReaderNode {//������
	int IDnum;                      //ID��
	char reader_name[MAX_NAME_LEN]; //����
	ReaderNode *rnext;              //ָ����һ�������ߵ�ָ��
}ReaderNode, *ReaderType;

typedef struct BookNode {
	int booknum;   //���
	char bookname[MAX_BKNAME_LEN];  //����
	char writer[MAX_NAME_LEN];      //��������
	int current;                    //�ִ���
	int total;						//�ܿ��
	int published_year;				//�������
	float price;					//�۸�
	ReaderType reader;				//����������ָ��
}BookNode, *BookType;				//ͼ������

typedef BookNode Record;			//����Ľ�㶨��Ϊ��¼

									/*******************************B���洢����***************************/

typedef struct BTNode {        //B��������Ͷ���
	int keynum;			       //����йؼ��ָ����������Ĵ�С
	KeyType key[M + 1];		   //�ؼ��֣�key[0]δ��
	struct BTNode *parent;	   //˫�׽��ָ��
	struct BTNode *ptr[M + 1]; //���ӽ��ָ������
	Record *recptr[M + 1];     //��¼ָ��������0�ŵ�Ԫδ��
}BTNode, *BTree;			   //B������B������

typedef struct result {
	BTNode *pt;				  //ָ���ҵ��Ľ��
	int i;					  //1<=i<=m,�ڽ���еĹؼ���λ��
	int tag;				  //1:���ҳɹ���0:����ʧ��
}result, *resultPtr;		  //B���Ĳ��ҽ������



							  /*******************************B���ӿڶ���***************************/


result SearchBTree(BTree T, int k);
/*
��ʼ����:��T����
�������:��m��B��T�ϲ��ҹؼ���k������p{pt,i,tag}
*/

Status InsertBTree(BTree &T, int k, BTree q, int i, Record *recptr);
/*
��ʼ����:��T����
�������:��B��T�Ͻ��p->pt��key[i]��key[i+1]֮�����ؼ���k
*/

Status DeleteBTree(BTree &T, int k);
/*
��ʼ����:B����p������
�������:ɾ��B��T�Ͻ��p->pt�Ĺؼ���k
*/

void BTreeTraverse(BTree T, void(*visit)(BTree));
/*
��ʼ����:��T����
�������:����B��
*/


int menu();
/*
���ѡ��˵�
*/

void ShowBTree(BTree T, short x = 8);
/*
�԰�������ʽ���B��
*/
int login();
/*
��½����
*/

/*******************************ͼ��ݽӿڶ���***************************/
void InitLibrary(BTree &L);
/*
��ʼ��һ�ÿ���
*/
void InsertBook(BTree &L, BookType B, result res);
/*
�����µ��鼮
*/
int DeleteBook(BTree &L, BookType B);
/*
ɾ���Ѵ��ڵ��鼮������������ʾ������
*/
int CanBorrow(BTree L, BookType B, ReaderType R);
/*
�ж�ָ���鼮�ܷ����
*/
void BorrowBook(BTree L, BookType B, ReaderType R);
/*
�鼮����
*/
int ReturnBook(BTree L, int booknum, int IDnum, BookType &B, ReaderType &R);
/*
�鼮�黹
*/
void PrintH();
/*
�������ͷ��
*/
void PrintB(BookType B);
/*
���ָ���鼮����Ϣ
*/
void PrintT();
/*
�������β��
*/
void PrintAll(BTree p);
/*
���B������ȫ���ؼ�����Ϣ
*/
void PrintBook(BookType B);
/*
�Ա����ʽ���һ�������Ϣ
*/
void PrintAllbooks(BTree L);
/*
������������Ϣ
*/
int ShowBookinfo(BTree L, int booknum);
/*
���ָ��ĳ�������Ϣ
*/
void PrintBorrower(ReaderType R);
/*
���ĳ����Ľ�������Ϣ
*/
void	Welcome(int color);
/*
��ʾ��ӭ����
*/
void	Creat(BTree &L);
/*
���ļ��ж�ȡͼ����Ϣ
*/