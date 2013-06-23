#include<iostream>
#include<fstream>

using namespace std;

int sudoku[9][9][10];
int p[9][9];

void print()
{
    ofstream file("out.txt",ios::out);

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            file << sudoku[i][j][0] << "  ";
            cout << sudoku[i][j][0] << "  ";
        }
        file << endl;
        cout << endl;
    }
    file.close();
}

void input()
{
    ifstream file("sudo.txt",ios::in);

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            file >> sudoku[i][j][0];
            if(sudoku[i][j][0]!=0)
                p[i][j] = -1;
        }
    }
    file.close();
    print();
}

void build(int x,int y)
{
    int flag[10] = {0};
    int xh,yh,i,j,count;

    if(x<3)
        xh=3;
    else if(x<6)
        xh=6;
    else if(x<9)
        xh=9;

    if(y<3)
        yh=3;
    else if(y<6)
        yh=6;
    else if(y<9)
        yh=9;

    for(i=0;i<9;i++)
        flag[sudoku[x][i][0]] = 1;

    for(i=0;i<9;i++)
        flag[sudoku[i][y][0]] = 1;

    for(i=xh-3;i<xh;i++)
        for(j=yh-3;j<yh;j++)
            flag[sudoku[i][j][0]] = 1;

    count = 1;
    for(i=0;i<10;i++)
        if(flag[i]==0)
            sudoku[x][y][count++] = i;

    p[x][y] = count-1;

    for(i=count;i<10;i++)
        sudoku[x][y][i] = 0;
}

int solve(int i,int j)
{
    if(p[i][j] == -1)
    {
        if(i==8 && j==8)
        {
            return 1;
        }
        else if(j==8)
        {
            if(solve(i+1,0))
                return 1;
            else
                return 0;
        }
        else if(j<8)
        {
            if(solve(i,j+1))
                return 1;
            else
                return 0;
        }
    }

    build(i,j);
    if(p[i][j]==0)
        return 0;

    for(int count=1;count<=p[i][j];count++)
    {
        sudoku[i][j][0] = sudoku[i][j][count];

        if(i==8 && j==8)
        {
            return 1;
        }
        else if(j==8)
        {
            if(solve(i+1,0))
                return 1;
        }
        else if(j<8)
        {
            if(solve(i,j+1))
                return 1;
        }
    }
    sudoku[i][j][0] = 0;
    return 0;
}

int main()
{
    input();

    solve(0,0);

    cout << "\nSOLUTION : \n";
    print();

    return 0;
}
