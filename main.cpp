#include <stdio.h>
#include "graphics.h"
#include <iostream>

using namespace std;

int const mash = 30;
void setQueen(int vert,int gor, int **board) //��������� �����
{
    int minim=8;
   for (int x = 0; x< minim;x++)
    {
        board[x][gor]++;  //���� ������ ������������ ������
        board[vert][x]++;  //���� ���� ������������ ������
        int foo;
        foo = gor-vert+x;
        if (foo >=0 && foo<minim)//��������� ������ ����
            board[x][foo]++;
        foo = gor+ vert - x;
         if (foo >=0 && foo<minim)//�������� ������ �����
            board[x][foo]++;
    }
    board[vert][gor]=-1;
}

void resetQueen(int vert,int gor, int **board)
{
    int minim=8;


    for (int x = 0; x< minim;x++)
    {
        board[x][gor]--;
        board[vert][x]--;
        int foo;
        foo = gor-vert+x;
        if (foo >=0 && foo<minim)
            board[x][foo]--;
        foo = gor+ vert - x;
         if (foo >=0 && foo<minim)
            board[x][foo]--;
    }
    board[vert][gor]=0;
}

bool tryQueen(int vert,int gor, int **board,int k)//�������� ��������� �����
{
    bool result = false;
    for (int j=0;j < gor ;j++)    //���� �� ��������
    {
        if (board[vert][j]==0)   //���� ������ �� ������,
        {
            setQueen(vert,j,board);  // ����� ������ �����
            if (vert==k)             // � ���� ��������� ���������
                result = true;       //���������� ��, ��� �� ��������� ��� �����
            else
            {                         //���� ���������� �� ��� �����
               if(!(result =tryQueen(vert+1,gor,board,k))) // ���� �� ������ ��������� �� ��������� �������
                resetQueen(vert,j,board);    //�������� ��� ���, ��������� ������
            }
        }
        if (result)   //���� ��������� ���� �����
            break;    //�� �������������
    }
    return result;
}

void printpole(int **board,int vert,int gor)
{
   int counter = 1;
   for (int i=0;i<vert;i++)
   {
    for (int j=0;j<gor;j++)
       {
          if (board[i][j]==-1)
          {
              setfillstyle(1,4);
              bar(j*mash,i*mash,(j+1)*mash,(i+1)*mash);
          }
          else
            {
                if (counter%2==1)
                setfillstyle(1,15);
                else
                setfillstyle(1,0);
                bar(j*mash,i*mash,(j+1)*mash,(i+1)*mash);
            }
            counter++;
       }
       if (gor%2!=1)
         counter++;
       }
}
int main ()
{
    setlocale(LC_ALL, "Russian");
    cout<<"������� ������� ����: "<<endl;
    cout<<"������� ���������� ������ �� ���������:"<<endl;
    int vert;
    cin>>vert;
    cout<<"������� ���������� ������ �� �����������:"<<endl;
    int gor;
    cin>>gor;
    initwindow(gor*mash,vert*mash);
    int QN;
    //cout<<"������� ���������� ������, ������� ������ ���������:"<<endl;
    //cin>> QN;
    int **board = new int *[vert];
		for (int i = 0; i < vert; i++)
		{
			board[i] = new int[gor];
		}
    int k= vert-1;
    for (int i=0;i<vert;i++)
       for (int j=0;j<gor;j++)
        board[i][j]=0;
    tryQueen(0,gor,board,k);
    printpole(board,vert,gor);
    system("PAUSE");
    getch();
    closegraph();

    return 0;
}
