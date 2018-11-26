#include<stack>
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<bits/stdc++.h>
#include<string>
#include<ctime>
using namespace std;
int score=0;
char **maze;
static int lives= 3;


class Graph
{
    public:
        int nodes;
        vector<int>*adj;
        int sp;
        int lp;

    Graph(int n)
    {
        sp=0;
        this->nodes=n;
        adj=new vector<int>[n*n];
    }

    void checkEdge()
    {
        for(int i=0;i<nodes;i++)
        {
            for(int j=0;j<nodes;j++)
            {
                edge(i,j);
            }
        }
    }

    void add_edge(int org,int dest)
    {
        adj[org].push_back(dest);
    }

    void edge(int i,int j)
    {
        if(maze[i][j]!='X')
        {
            if(i>0 && maze[i-1][j]!='X')
            {
                add_edge((i*nodes)+j,(i-1)*nodes+j);
            }
            if(i<nodes-1 && maze[i+1][j]!='X')
            {
                add_edge((i*nodes)+j,(i+1)*nodes+j);
            }
            if(j>0 && maze[i][j-1]!='X')
            {
                add_edge((i*nodes)+j,(i*nodes)+(j-1));
            }
            if(j<nodes-1 && maze[i][j+1]!='X')
            {
                add_edge((i*nodes)+j,(i*nodes)+(j+1));
            }
        }
    }

    int minEdgeBFS(int u, int v)
    {
        vector<bool> visited(nodes*nodes, false);
        vector<int> distance(nodes*nodes, 0);
        queue <int> Q;
        distance[u] = 0;
        Q.push(u);
        visited[u] = true;
        while (!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            for (int i=0; i<adj[x].size(); i++)
            {
                if (visited[adj[x][i]])
                    continue;
                distance[adj[x][i]] = distance[x] + 1;
                Q.push(adj[x][i]);
                visited[adj[x][i]] = 1;
            }
        }
        return distance[v];
    }
};


class mazegame
{
public:
   string player;
    stack<pair<int,int> > S;
    int n , steps;


    void randomObstruction(double percent)
    {
        int c=(percent*n*n);
        while(c>0)
        {
            int i=rand()%n;
            int j=rand()%n;
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
   void scoreBoard(int shortest , double percent)
    {
            int longest = (n*n)-(percent*n*n);
            int avg = (longest+shortest)/2;
            int count=0;
            if((steps+1)>avg)
               {
                 score += 40;
               }
            else if((steps+1) == avg)
            {
                score+=50;
            }
            else if((steps+1)<avg)
            {
                if((steps+1)==shortest)
                    score+=100;
                else
                {
                    count = (steps+1)-shortest;
                    if(count==1)
                        score+=95;
                    else if(count==2)
                        score+=90;
                    else if(count==3)
                        score+=85;
                    else if(count==4)
                        score+=80;
                     else if(count==5)
                        score+=75;
                     else if(count==6)
                        score+=70;
                     else if(count==7)
                        score+=65;
                     else if(count==8)
                        score+=60;
                     else if(count==9)
                        score+=55;
                    else
                        score+=50;

                }
            }
    }
 };

    double level(int size)
    {
        if(size==8)
            return(.15);
        if(size==9)
            return(.20);
        if(size==10)
            return(.25);
        if(size==11)
            return(.30);
        if(size==12)
            return(.35);
    }


 int main()
 {
     srand(time(NULL));
     string name;
     int n=8;
     double c;

     cout<<"\n\t\t\t\t WELCOME \n\n\n";
     cout<<"\n\t Enter your name:- ";
     cin>>name;

     int counter = 1;
     int sp=0;

     while(counter<=5)
     {
        char ch;
        cout<<"\n\n\t\t LEVEL "<<counter<<"\n\n";
        c = level(n);
        mazegame a(n,name);

        do
        {
            mazegame a(n,name);
            a.randomObstruction(c);
            a.drawMaze();
            cout<<"\nTo RELOD .....'R' else do not ";
            cin>>ch;
        }while(ch=='R');

        Graph g(n) ;
        g.checkEdge();
        sp=g.minEdgeBFS(0,n*n-1);
        a.move(0,0);
        a.scoreBoard(sp,c);
        cout<<"\nYour total Steps were:- "<<(a.steps+1);
        cout<<"\nYour Score:- "<<score;
        cout<<"\nMin steps were:- "<<sp;
        counter++;
        n++;
    }
    return 0;
 }

