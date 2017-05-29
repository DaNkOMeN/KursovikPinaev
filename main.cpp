#include <stdio.h>
#include "graphics.h"
#include <iostream>
#include <locale.h>

using namespace std;

int const mash = 30;
void setQueen(int i, int j, int vert, int gor, int **board)
{
    for (int counter = 0; counter < gor; counter++)
    {
        board[i][counter]++;
    };
    for (int counter = 0; counter < vert; counter++)
    {
        board[counter][j]++;
    };
    int curI = i ,curJ = j;
    while ((curI >= 0) && (curJ >= 0))
    {
        board[curI][curJ]++;
        curI--;
        curJ--;
    }
    curI = i ;curJ = j;
    while ((curI < vert) && (curJ < gor))
    {
        board[curI][curJ]++;
        curI++;
        curJ++;
    }
    curI = i ;curJ = j;
    while ((curI < vert) && (curJ >= 0))
    {
        board[curI][curJ]++;
        curI++;
        curJ--;
    }
    curI = i ;curJ = j;
    while ((curI >= 0) && (curJ < gor))
    {
        board[curI][curJ]++;
        curI--;
        curJ++;
    }
    board[i][j] = -1;

}


void resetQueen(int i, int j, int vert, int gor, int **board)
{
    for (int counter = 0; counter < gor; counter++)
    {
        board[i][counter]--;
    };
    for (int counter = 0; counter < vert; counter++)
    {
        board[counter][j]--;
    };
    int curI = i ,curJ = j;
    while ((curI >= 0) && (curJ >= 0))
    {
        board[curI][curJ]--;
        curI--;
        curJ--;
    }
    curI = i ;curJ = j;
    while ((curI < vert) && (curJ < gor))
    {
        board[curI][curJ]--;
        curI++;
        curJ++;
    }
    curI = i ;curJ = j;
    while ((curI < vert) && (curJ >= 0))
    {
        board[curI][curJ]--;
        curI++;
        curJ--;
    }
    curI = i ;curJ = j;
    while ((curI >= 0) && (curJ < gor))
    {
        board[curI][curJ]--;
        curI--;
        curJ++;
    }
    board[i][j] = 0;
}

bool tryQueen(int i, int vert, int gor, int **board, int QN,int counter)
{
    bool result = false ;
    if (counter > QN)
    {
        return true;
    }
    else
    {
      for (int j = 0; j < gor; j++)
      {
          if (board[i][j] == 0)
          {
            setQueen(i,j,vert,gor,board);
            bool nextDone = tryQueen(i + 1,vert,gor,board,QN,counter + 1);
            if (nextDone != true)
            {
               resetQueen(i,j,vert,gor,board);
            }
            else
            {
               return true;
            }
          }
      }
    }
    return result;
}


void printpole(int **board, int vert, int gor, int **board2)
{
    int counter = 1;
    for (int i = 0; i < vert; i ++)
    {
        for (int j = 0; j < gor; j ++)
        {
            if (board[i][j] == -1)
            {
                setfillstyle(1, 4);
                bar(j * mash, i * mash,(j + 1) * mash,(i + 1) * mash);
            }
            else
            {
                if (board2[i][j] == 1){
                    setfillstyle(1, 6);
                    bar(j * mash, i * mash,(j + 1) * mash,(i + 1) * mash);
                }
                else
                {
                    if (counter % 2 == 1)
                        setfillstyle(1, 15);
                    else
                        setfillstyle(1, 0);
                    bar(j * mash, i * mash,(j + 1) * mash,(i + 1) * mash);
                }
            }
            counter ++;
       }
       if (gor % 2 != 1)
         counter++;
       }
}

int main ()
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите размеры поля: " << endl;
    cout << "Введите количество клеток по вертикали:" << endl;
    int vert;
    cin >> vert;
    cout << "Введите количество клеток по горизонтали:" << endl;
    int gor;
    cin >> gor;
    int QN;
    cout << "Введите количество ферзей, которые хотите поставить:" << endl;
    cin >> QN;
    if ((QN <= gor) && (QN <= vert) && (QN >= 0))
    {
        int **board = new int *[vert];
		for (int i = 0; i < vert; i ++)
			board[i] = new int[gor];
        int k = vert - 1;
        for (int i = 0; i < vert; i ++)
            for (int j = 0; j < gor; j ++)
                board[i][j] = 0;


        int **board2 = new int *[vert];
		for (int i = 0; i < vert; i ++)
			board2[i] = new int[gor];
        for (int i = 0; i < vert; i ++)
            for (int j = 0; j < gor; j ++)
                board2[i][j] = 0;


        cout << "Хотите чтобы клетки исчезли? Y/y-да , N/n - нет" << endl;
        char b;
        cin >> b;
        if ((b == 'y') || (b == 'Y'))
        {
            cout << "Введите количество исчезнувших клеток: " << endl;
            int q;
            cin >> q;
            int i1,j1;
            for (int l = 0; l < q; l ++)
            {
                cout << "Введите координаты клетки:" << endl;
                cin >> i1;
                cin >> j1;
                board2[i1-1][j1-1] = 1;
            }

            tryQueen(0, vert, gor, board, QN,0);
            for (int i = 0; i < vert; i ++)
            {
                for (int j = 0; j < gor; j ++)
                    cout << board[i][j]<<' ';
                cout << endl;
            }
            initwindow(gor * mash, vert * mash);
            printpole(board, vert, gor,board2);
        }
        else
            if  ((b == 'n')|| (b == 'N'))
            {

                tryQueen(0, vert, gor, board, QN ,1);
                for (int i = 0; i < vert; i ++)
                    {
                        for (int j = 0; j < gor; j ++)
                            cout << board[i][j]<<' ';
                        cout << endl;
                    }
                initwindow(gor * mash, vert * mash);
                printpole(board, vert, gor,board2);
            }
            else cout << "Введено неверное значение!!!" << endl;
    }
    else cout << "Невозможно поставить такое количество ферзей на доску" << endl;
    system("PAUSE");
    getch();
    closegraph();

    return 0;
}

