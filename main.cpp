#include <stdio.h>
#include "graphics.h"
#include <iostream>

using namespace std;

int const mash = 30;
void setQueen(int vert,int gor, int **board) //поставить ферз€
{
    int minim=8;
   for (int x = 0; x< minim;x++)
    {
        board[x][gor]++;  //идем вправо относительно клетки
        board[vert][x]++;  //идем вниз относительно клетки
        int foo;
        foo = gor-vert+x;
        if (foo >=0 && foo<minim)//диагональ вправо вниз
            board[x][foo]++;
        foo = gor+ vert - x;
         if (foo >=0 && foo<minim)//диагонал вправо вверх
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

bool tryQueen(int vert,int gor, int **board,int k)//ѕытаемс€ поставить верз€
{
    bool result = false;
    for (int j=0;j < gor ;j++)    //идем по столбцам
    {
        if (board[vert][j]==0)   //если клетка не зан€та,
        {
            setQueen(vert,j,board);  // тогда ставим ферз€
            if (vert==k)             // и если вертикаль последн€€
                result = true;       //возвращает то, что мы поставили все ферзи
            else
            {                         //если поставлены не все ферзы
               if(!(result =tryQueen(vert+1,gor,board,k))) // если не смогли поставить на следующий столбец
                resetQueen(vert,j,board);    //отмен€ем наш ход, обнуцл€ем клетку
            }
        }
        if (result)   //если поставили всех ферзй
            break;    //то останавливаем
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
    cout<<"¬ведите размеры пол€: "<<endl;
    cout<<"¬ведите количество клеток по вертикали:"<<endl;
    int vert;
    cin>>vert;
    cout<<"¬ведите количество клеток по горизонтали:"<<endl;
    int gor;
    cin>>gor;
    initwindow(gor*mash,vert*mash);
    int QN;
    //cout<<"¬ведите количество ферзей, которые хотите поставить:"<<endl;
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
