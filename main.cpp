#include <stdio.h>
#include "graphics.h"
#include <iostream>

using namespace std;

int const mash = 30;
void setQueen(int i,int j,int vert,int gor, int **board,int QN) //поставить ферз€
{
    int minim=min(vert,gor);

   for (int x = 0; x< minim;x++)
    {
        board[x][j]++;  //идем вправо относительно клетки
        board[i][x]++;  //идем вниз относительно клетки
        int foo;
        foo = j-i+x;
        if (foo >=0 && foo<gor)//диагональ вправо вниз
            board[x][foo]++;
        foo = j+ i - x;
         if (foo >=0 && foo<gor)//диагонал вправо вверх
            board[x][foo]++;

    }
    board[i][j]=-1;
}

void resetQueen(int i,int j, int vert,int gor, int **board,int QN)
{
    int minim=min(vert,gor);
    for (int x = 0; x< minim;x++)
    {

        board[x][j]--;
        board[i][x]--;
        int foo;
        foo = j - i + x;
        if (foo >=0 && foo<gor)
            board[x][foo]--;
        foo = j + i - x;
         if (foo >=0 && foo<gor)
            board[x][foo]--;

    }
    board[i][j]=0;
}

bool tryQueen(int i,int vert,int gor, int **board,int k,int QN)//ѕытаемс€ поставить ферз€ на i-ый столбец
{
    bool result = false;
    int counter = 0;
    for (int j=0;j < gor ;j++)    //идем по столбцам
    {
        if (counter < QN)
        {
          if ((board[i][j]==0)  )  //если клетка не зан€та,
           {
            setQueen(i,j,vert,gor,board,QN);
            counter++;  // тогда ставим ферз€
            if (counter ==QN)        // и если вертикаль последн€€
                result = true;       //возвращает то, что мы поставили все ферзи
            else
              {                         //если поставлены не все ферзы
               if(!(result =tryQueen(i+1,vert,gor,board,k,QN-1))) // если не смогли поставить на следующий столбец
                resetQueen(i,j,vert,gor,board,QN);
                   //отмен€ем наш ход, обнуцл€ем клетку
               }
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
            { if (board[i][j]==-10)
                 setfillstyle(1,9);
                 else
                 {
                    if (counter%2==1)
                   setfillstyle(1,15);
                   else
                   setfillstyle(1,0);
                   bar(j*mash,i*mash,(j+1)*mash,(i+1)*mash);
                 }
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
    cout<<"¬ведите количество ферзей, которые хотите поставить:"<<endl;
    cin>> QN;
    if ((QN <= gor) && (QN <= vert) &&(QN >= 0))
    {
    int **board = new int *[vert];
		for (int i = 0; i < vert; i++)
		{
			board[i] = new int[gor];
		}
    int k= vert-1;
    for (int i=0;i<vert;i++)
       for (int j=0;j<gor;j++)
        board[i][j]=0;
    cout<<"’отите чтобы клетки исчезли? Y/y-да , N/n - нет"<<endl;
    char b;
    cin>>b;
    if ((b == 'y')|| (b == 'Y'))
    {
        cout <<"¬ведите количество исчезнувших клеток: "<<endl;
        int q;
        cin >> q;
        int i1,j1;
       for (int l=0;l<q;l++)
       {
           cout<<"¬ведите координаты клетки:"<<endl;
           cin>>i1;
           cin>>j1;
           board[i1][j1] = -10;
       }
      tryQueen(0,vert,gor,board,k, QN);
      printpole(board,vert,gor);
    }
    else if  ((b == 'n')|| (b == 'N'))
     {
      tryQueen(0,vert,gor,board,k, QN);
      printpole(board,vert,gor);
     }
     else cout <<"¬ведено неверное значение!!!"<<endl;
    }
    else cout <<"Ќевозможно поставить такое количество ферзей на доску"<<endl;
    system("PAUSE");
    getch();
    closegraph();

    return 0;
}
