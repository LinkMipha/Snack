#include <stdio.h>
#include<stdlib.h>
#include <tchar.h>
#include<windows.h>
#include"conio.h"
#include<iostream>
using namespace std;
#define W 1
#define S 2
#define A 3
#define D 4
typedef struct snack
{
	int x, y;
	struct snack*next;
}SN;

int score=0, status=0, sleeptime=0,gamestatus=0,lon=0,add=1,lv=1;
int snc = 0, tipc = 0, wec = 0,wallc=0,foodc=0,beginc=0,endc=0;//��ɫ��ͬ
int s=0;
SN*head, *food,*q;
HANDLE hout;//����̨���

void welcomegame();
void gotoxy(int, int);//λ��
void color(int);//��ɫ
void clrscr();//����
void map();
void init();//��ʼ��λ�úͳ���
void tip();
void creatfood();
int self();
void wall();
void begin();
void keyboard();
void move();
void speed(int spee);//�ٶȸ���
int state();//״̬
void end();
void choose();
void gamelv();



void gotoxy(int a, int b)//���Ĭ��120 30
{
	HANDLE hout;
	COORD coord;
	coord.X = a;
	coord.Y = b;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨���
	SetConsoleCursorPosition(hout, coord);//����λ��
}


void clrscr()
{
	system("cls");
}

void color(int a)//��ɫ����
{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);

}




void map()//�ַ�ռ�����ֽڿ��
{
	for (int i = 0; i < 100; i+=2)
	{
		wallc = rand() % 5 + 10;
		color(wallc);
		gotoxy(i, 0);
		printf("#");
		gotoxy(i,49);
		printf("#");
	}

	for (int i = 0; i < 50; i++)
	{
		wallc = rand() % 5 + 10;
		color(wallc);
		gotoxy(0,i);
		printf("#");
		gotoxy(100,i);
		printf("#");

	}
}

void tip()
{
	//tipc = rand() % 5 + 10;
	//color(tipc);
	gotoxy(105, 19);
	printf("ESC�˳���Ϸ");
	gotoxy(105, 22);
	printf("�ո���ͣ��Ϸ");
	gotoxy(105, 25);
	printf("�������������ƶ�");

	gotoxy(105, 28);
	printf("�ȼ�Ϊ: %d", lv);
	gotoxy(105, 31);
	printf("����Ϊ: %d", score);

}

void init()//ͷ�巨������ʼ����
{
	SN*s;
	head = new SN;
	head->next = NULL;
	head->x = 52;
	head->y = 25;
	for (int i = 1; i < 5; i++)
	{
		s = new SN;
		s->x = 52 - 2 * i;
		s->y = 25;
		s->next = head;
		head = s;
	}
	SN*t = head;
	while (t!=NULL)
	{
		gotoxy(t->x,t->y);
		printf("��");
		t = t->next;
	}
}

void creatfood()
{
	SN*fd = new SN;
	fd->x = rand() % 94 + 2;
	while (fd->x % 2 != 0)
	{
		fd->x = rand() % 94 + 2;
	}
	fd->y = rand() % 47 + 1;
	q = head;
	while (q!= NULL)
	{
		if (q->x == fd->x&&q->y == fd->y)
		{
			delete fd;
			fd = NULL;
			creatfood();
		}
		q = q->next;
	}
	food = fd;
	foodc = rand() % 5 + 10;
	color(foodc);
	gotoxy(food->x, food->y);
	printf("��");
	

}

int self()
{
	q = head;
	SN*self = head;
	while (q->next != NULL)
	{
		if (self->x == q->next->x&&self->y == q->next->y)//��һ���ǿ��ж���һ����ֵ
			return 1;
		q = q->next;
	}
	return 0;

}

void wall()
{
	if (head->x == 0 || head->x == 98 || head->y == 0 || head->y == 49)
	{
		gamestatus = 1;
		end();
	}

}

void speed(int spee)//�ٶ�ѡ��
{
	if (spee == 1)
	{
		if (sleeptime >= 100)
		{
			sleeptime = sleeptime - 5;
		}
		add = add + 2;
	}
	else if (spee == 2)
	{
		if (sleeptime >= 50)
		{
			sleeptime = sleeptime - 6;
		}
		add = add + 4;
	}
	else if (spee == 3)
	{
		if (sleeptime >= 20)
		{
			sleeptime = sleeptime - 7;
		}
		add = add + 8;
	}
	lv++;
}



void move()
{
	q = head;
	SN*nexttip = new SN;
	wall();
	tip();
	if (status == W)
	{
		nexttip->x = q->x;
		nexttip->y = q->y - 1;
		nexttip->next = head;
		head = nexttip;
		q = head;
		if (nexttip->x == food->x&&nexttip->y == food->y)//��ʳ���غ�
		{
			while (q!= NULL)
			{

				gotoxy(q->x, q->y);
				printf("��");
				q = q->next;
			}
			speed(s);
			score += add;
			creatfood();

			s = snc;
			snc = rand() % 5 + 10;
			while (snc == s)
			{
				snc = rand() % 5 + 10;
			}
			color(snc);
		}
		else
		{

			while (q->next->next!= NULL)
			{
				gotoxy(q->x, q->y);
				printf("��");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);
			printf(" ");
			delete q->next;
			q->next= NULL;

		}

	}


	if (status == S)
	{
		nexttip->x = q->x;
		nexttip->y = q->y+1;
		nexttip->next = head;
		head = nexttip;
		q = head;
		if (nexttip->x == food->x&&nexttip->y == food->y)//��ʳ���غ�
		{

			while (q != NULL)
			{

				gotoxy(q->x, q->y);
				printf("��");
				q = q->next;
			}
			speed(s);
			score += add;
			creatfood();

			s = snc;
			snc = rand() % 5 + 10;
			while (snc == s)
			{
				snc = rand() % 5 + 10;
			}
			color(snc);
		}
		else
		{

			while (q->next->next != NULL)
			{

				gotoxy(q->x, q->y);
				printf("��");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);
			printf(" ");
			delete q->next;
			q->next = NULL;

		}



	}

	if (status == A)//���������
	{
		nexttip->x = q->x-2;
		nexttip->y = q->y;
		nexttip->next = head;
		head = nexttip;
		q = head;
		if (nexttip->x == food->x&&nexttip->y == food->y)//��ʳ���غ�
		{

			while (q != NULL)
			{

				gotoxy(q->x, q->y);
				printf("��");
				q = q->next;
			}
			speed(s);
			score += add;
			creatfood();

			s = snc;
			snc = rand() % 5 + 10;
			while (snc == s)
			{
				snc = rand() % 5 + 10;
			}
			color(snc);
		}
		else
		{
			while (q->next->next != NULL)
			{

				gotoxy(q->x, q->y);
				printf("��");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);
			printf(" ");
			delete q->next;
			q->next = NULL;

		}



	}

	if (status == D)
	{
		nexttip->x = q->x+2;
		nexttip->y = q->y;
		nexttip->next = head;
		head = nexttip;
		q = head;
		if (nexttip->x == food->x&&nexttip->y == food->y)//��ʳ���غ�
		{

			while (q != NULL)
			{

				gotoxy(q->x, q->y);
				printf("��");
				q = q->next;
			}
			speed(s);
			score += add;
			creatfood();

			s = snc;
			snc = rand() % 5 + 10;
			while (snc == s)
			{
				snc = rand() % 5 + 10;
			}
			color(snc);
		}
		else
		{

			while (q->next->next != NULL)
			{

				gotoxy(q->x, q->y);
				printf("��");
				q = q->next;
			}
			gotoxy(q->next->x, q->next->y);
			printf(" ");
			delete q->next;
			q->next = NULL;

		}



	}


	if (self() == 1)       //�ж��Ƿ��ҧ���Լ�
	{
		gamestatus = 2;
		end();
	}

}

void keyboard()
{

	status = A;
	snc = 10;
	color(snc);//��ɫ��ʼ
	while (1)
	{
		if (GetAsyncKeyState(VK_UP) && status != S)            //GetAsyncKeyState���������жϺ�������ʱָ���������״̬
		{
			status = W;
		}
		if (GetAsyncKeyState(VK_DOWN) && status != W)
		{
			status = S;
		}
		if (GetAsyncKeyState(VK_LEFT) && status != D)
		{
			status = A;
		}
		if (GetAsyncKeyState(VK_RIGHT) && status != A)
		{
			status = D;
		}
		if (GetAsyncKeyState(VK_SPACE))		//����ͣ����ִ��pause��ͣ����
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE))      //���ո����ͣ
				{
					break;
				}

			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			gamestatus = 3;    //��esc����ֱ�ӵ���������
			break;
		}
		Sleep(sleeptime);

		move();
	}

}


void welcomegame()
{
	int x;
	beginc = rand() % 5 + 10;//�ı���ɫ
	color(beginc);
	for (int i = 40; i < 85; i += 2)
	{
		gotoxy(i, 12);
		printf("��");
		gotoxy(i, 40);
		printf("��");
	}

	for (int i = 13; i < 40; i++)
	{
		gotoxy(40, i);
		printf("|");
		gotoxy(84, i);
		printf("|");
	}

	for (int i = 48; i < 60; i += 2)
	{
		gotoxy(i, 20);
		printf("��");
	}
	gotoxy(65, 24);
	printf("��");


	gotoxy(60, 15);
	printf("̰����");
	gotoxy(55, 35);
	printf("��ʼ��Ϸ------1");
	gotoxy(55, 36);
	printf("�˳���Ϸ------2");
	gotoxy(55, 37);
	printf("����ѡ��");
	scanf("%d", &x);
	switch (x)
	{
	case 1:
		begin();
		break;
	case 2:
		exit(0);
		break;
	default:
		system("cls");
		gotoxy(48, 25);
		printf("�����������������");
		system("pause");
		system("cls");
		welcomegame();
		break;
	}


}

void begin()
{
	system("cls");          //����
	score = 0;                //��������
	add = 1;
	lv=1;
	gamelv();
	system("cls");
	map();
	init();
	tip();
	creatfood();
	keyboard();

}


void end()
{

		system("cls");
		endc = rand() % 10 + 5;
		color(endc);
		if (gamestatus == 1)
		{

			gotoxy(55, 15);
			printf("GAME  OVER !");
		}
		else if (gamestatus == 2)
		{

			gotoxy(55, 15);
			printf("GAME  OVER !");
		}
		else if (gamestatus == 3)
		{

			gotoxy(55, 15);
			printf("�ѽ�����Ϸ��");
		}
		gotoxy(55, 17);
		printf("��ĵ÷��� %d", score);
		choose();


}

void gamelv()//��Ϸ�ȼ�
{
	int option;
	system("cls");
	gotoxy(58, 24);
	printf("ѡ���Ѷ�");
	gotoxy(55, 25);
	color(12);
	printf("��-----1");
	gotoxy(55, 26);
	printf("�е�-----2");
	gotoxy(55, 27);
	printf("����-----3");
	gotoxy(55, 28);
	printf("����ѡ��");
	scanf("%d", &option);
	switch (option)
	{
	case 1:
		sleeptime = 150;
		s = 1;
		break;
	case 2:
		sleeptime = 120;
		s = 2;
		break;
	case 3:
		sleeptime = 90;
		s = 3;
		break;
	default:
		system("cls");
		gotoxy(50, 25);
		printf("�������,��������");
		system("pause");
		gamelv();
		break;
	}
}

void choose()
{
		int n;
		gotoxy(55, 25);
		color(12);
		printf("������Ϸ------1");
		gotoxy(55, 26);
		printf("�˳�------2");
		gotoxy(55, 28);
		printf("ѡ�� ");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			begin();
			break;
		case 2:
			exit(0);                //�˳���Ϸ
			break;
		default:
			color(12);
			system("cls");
			gotoxy(55, 15);
			printf(" �������� �������� !");
			system("pause >nul");
			end();
			choose();
			break;
		}

}

int main()
{
	system("mode con cols=134 lines=50");
	welcomegame();
	end();
	return 0;
}
