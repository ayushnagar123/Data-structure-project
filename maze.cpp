#include<stack>
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<bits/stdc++.h>
#include<string>
#include<ctime>

using namespace std;

int score=0;
class mazegame//:public Levels
{
public:

    int n , lives , steps;
    char **maze;
    string player;
    stack<pair<int,int>> S;

    void randomObstruction(double percent)
    {
        srand(time(NULL));
        int c=(percent*n*n);
        while(c>0)
        {
            int i=rand()%8;
            int j=rand()%8;
            if(maze[i][j]!='X' && maze[i][j]!='#' && (i!=0 || j!=0))
            {
                maze[i][j]='X';
                c--;
            }
        }
    }

    mazegame(int n , string name)
    {
        this->n=n;
        player = name;
        lives=3;
        steps=0;
        maze = new char * [n];
        for (int i = 0; i < n; ++i )
            maze[i] = new char [n];

        for(int i=0;i<n;i++)
        {
          for(int j=0;j<n;j++)
             maze[i][j]=' ';
        }

        maze[0][0]='@';
        maze[n-1][n-1]='#';
    }

 void drawMaze()
 {
     int i,j=0;
     cout<<"\n\n\n\n\n";
     for(i=0;i<n;i++)
     {
         cout<<"\t   "<<(i+1)<<"  ";
     }
     cout<<"\n";
    for(i=0;i<n;i++)
     {
         cout<<"\t  ___  ";
     }
     cout<<"\n";
     while(j<n)
     {
        for(i=0;i<n;i++)
        {
            if(maze[i][j]!=' ')
                printf("\t| _%c_ |",maze[i][j]);
            else
                cout<<"\t| ___ |";
        }
        cout<<"\n";
        j++;
     }
    cout<<"\n\n\n\n\n";
 }

 void move(int x,int y)
 {
     pair<int,int> K;
     char ch;
     do
     {
         cout<<"\nUP....'W'";
         cout<<"\nLEFT....'A'";
         cout<<"\nDOWN....'S'";
         cout<<"\nRIGHT....'D'";
         cout<<"\nUNDO....'U'";
         cout<<"\nQUIT....'Q'";
         cout<<"\n\t\t\t\t Your Lives:- "<<lives;
         cout<<"\nEnter Your Move:- ";
         cin>>ch;
         switch(ch)
         {
         case 'W':
             {
                 if(y>0 && maze[x][y-1]!='X'&& maze[x][y-1]!='#')
                   {
                     maze[x][y]='_';
                     if(!S.empty())
                     {  K=S.top();}
                     S.push(make_pair(x,y));
                     y-=1;
                     if((K.first==x)&&(K.second==y))
                     {  lives--;}
                     maze[x][y] = '@';
                     steps++;
                   }
                else if(maze[x][y-1]=='#')
                    {
                        cout<<"\n\t\t\tHURRAY!! Level Cleared !!";
                        y-=1;
                        break;
                    }
                else
                    cout<<"\nCan't Move up";

                if(lives==0)
                {
                    cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                    exit(0);
                }
                break;
             }
         case 'A':
             {
                 if(x>0 && maze[x-1][y]!='X'&& maze[x-1][y]!='#')
                    {
                        maze[x][y]='_';
                        if(!S.empty())
                        {  K=S.top();}
                        S.push(make_pair(x,y));
                        x-=1;
                         if((K.first==x)&&(K.second==y))
                     {  lives--;}
                        maze[x][y] = '@';
                        steps++;
                    }
                else if(maze[x-1][y]=='#')
                   {
                       cout<<"\n\t\t\tHURRAY!! Level Cleared !!";
                       x-=1;
                       break;
                   }
                else
                    cout<<"\nCan't Move left";

                if(lives==0)
                {
                    cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                    exit(0);
                }
                break;
             }
        case 'S':
             {
                 if(y>=0 && y+1<n && maze[x][y+1]!='X' && maze[x][y+1]!='#')
                    {
                        maze[x][y]='_';
                        if(!S.empty())
                        {  K=S.top();}
                        S.push(make_pair(x,y));
                        y+=1;
                         if((K.first==x)&&(K.second==y))
                     {  lives--;}
                        maze[x][y] = '@';
                        steps++;
                    }
                else if(maze[x][y+1]=='#')
                    {
                        cout<<"\n\t\t\tHURRAY!! Level Cleared !!";
                        y+=1;
                        break;
                    }
                else
                    cout<<"\nCan't Move Down";

                if(lives==0)
                {
                    cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                    exit(0);
                }
                break;
             }

        case 'D':
             {
                 if(x>=0 && x+1<n && maze[x+1][y]!='X' && maze[x+1][y]!='#')
                    {
                        maze[x][y]='_';
                        if(!S.empty())
                        {  K=S.top();}
                        S.push(make_pair(x,y));
                        x+=1;
                         if((K.first==x)&&(K.second==y))
                     {  lives--;}
                        maze[x][y] = '@';
                        steps++;
                    }
                else if(maze[x+1][y]=='#')
                    {
                        cout<<"\n\t\t\tHURRAY!! Level Cleared !!";
                        x+=1;
                        break;
                    }
                else
                    cout<<"\nCan't Move Right";

                    if(lives==0)
                {
                    cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                    exit(0);
                }
                break;
             }
        case 'U':
            {
                int i,j;
                if(S.empty()==true)
                    {   cout<<"\nUNDO NOT POSSIBLE";
                        break;

                    }
                    else
                    {
                        pair<int,int> P=S.top();
                        i=P.first;
                        j=P.second;
                        S.pop();
                        maze[x][y] = '_';
                        maze[i][j] = '@';
                        x=i;
                        y=j;
                        steps--;
                    }
                if(lives==0)
                {
                    cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                    exit(0);
                }
                else
                    lives--;
                break;
            }

        case 'Q':
            {
                cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                exit(0);
            }

        }
        //system("clear");
        drawMaze();

        }while(maze[x][y]!='#');
    }

   void scoreBoard(int shortest , int longest)
    {
            int avg = (longest+shortest)/2;
            int count=0;
            if(steps>avg)
               {
                 score += 40;
               }
            else if(steps == avg)
            {
                score+=50;
            }
            else
            {
                if(steps==shortest)
                    score+=100;
                else
                {
                    count = steps-shortest;
                    score+= (100-count*10);
                }
            }
    }
 };

/*class Levels
{
 public:
    int size;
    double obstruct;
    Levels()
    {
        size =0;
        obstruct =0;
    }*/
    double level(int size)
    {
        if(size==8)
            return(.25);
        if(size==9)
            return(.35);
        if(size==10)
            return(.45);
        if(size==11)
            return(.55);
        if(size==12)
            return(.6);
    }
 //};



/*class leaderboard
 {
public:

 };*/


 int main()
 {
     string name;
     int n=8;
     double c;
     cout<<"\n\t\t\t\t WELCOME \n\n\n";
     cout<<"\n\t Enter your name:- ";
     cin>>name;
     int counter = 1;
     //Levels l();
     while(counter<=5)
     {
        cout<<"\n\n\t\t LEVEL "<<counter<<"\n\n";
        c = level(n);
        mazegame a(n,name);
        a.randomObstruction(c);
        a.drawMaze();
        a.move(0,0);
        a.scoreBoard(20,45); /** parameters to be decided according to the graph for every level **/
        counter++;
        n++;
     }

     cout<<"\nYour Score is:- ";
     return 0;
 }
