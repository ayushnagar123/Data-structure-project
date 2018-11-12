#include<iostream>
#include<cstdlib>
#include<time.h>
#include <list>
#include<array>
#include<vector>
using namespace std;
class allpaths
{
    int n;
    int **adj;
    public:
    allpaths(int n)
    {
        this->n=n;
        adj=new int*[n];
        for(int i=0;i<n;i++)
        {
            adj[i]=new int[n];
            for(int j=0;j<n;j++)
            {
                adj[i][j]=0;
            }
        }
    }
    void add_edge(int org,int dest)
    {
        if(org>n||dest>n||org<0||dest<0)
        {
            cout<<"Invalid edge!";
        }
        else
        {
            adj[org][dest]=1;
        }
    }
    void printAllPaths(int s, int d)
    {
        bool *visited = new bool[n];
        int *path = new int[n];
        int path_index = 0;
        for (int i = 0; i < n; i++)
        {
            visited[i] = false;
        }
        printAllPathsUtil(s, d, visited, path, path_index);
    }
    void printAllPathsUtil(int u, int d, bool visited[],
                                  int path[], int &path_index)
    {
        visited[u] = true;
        path[path_index] = u;
        path_index++;
        if (u == d)
        {
            int c=0;
            for (int i = 0; i<path_index; i++)
            {
                cout << path[i] << " ";
                c++;
            }
            cout<< "\t length= " << c;
            cout << endl;
        }
        else
        {
            int i,j;
                for(i=0;i<n;i++)
                {
                        if (!visited[i])
                        {
                            printAllPathsUtil(i, d, visited, path, path_index);
                        }
                }
        }
        path_index--;
        visited[u] = false;
    }
};
int main()
{
    srand(time(0));
    allpaths g(16);

    int maze[6][6];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            maze[i][j]=1;
        }
    }
    int c=0;
    while(c<4)
    {
        int i=rand()%4;
        int j=rand()%4;
        if(maze[i][j]!=0&& (i!=0&&j!=0)||(i!=3 && j!=3))
        {
            maze[i][j]=0;
            c++;
        }
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<maze[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(maze[i][j]==1)
            {
                if(i<7 && maze[i+1][j]==1)
                {
                    g.add_edge(i*4+j,(i+1)*4+j);
                }
                if(j<7 && maze[i][j+1]==1)
                {
                    g.add_edge(i*4+j,i*4+(j+1));
                }
            }
        }
    }
    int s = 0, d = 15;
    cout << "Following are all different paths from " << s
         << " to " << d << endl;
    g.printAllPaths(s, d);
    return 0;
}
