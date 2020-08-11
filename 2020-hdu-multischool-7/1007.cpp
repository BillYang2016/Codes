#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
    int num=0,bj=1;
    char x=getchar();
    while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
    while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
    return num*bj;
}

const int maxn=2005;

typedef long long LL;

struct node {
    LL x,y;
} a[maxn];

struct dists {
    int from,to;
	LL dist;
    dists(int x=0,int y=0,LL d=0):from(x),to(y),dist(d) {}
    bool operator < (const dists& b) const {return dist<b.dist;}
} D[maxn*maxn];

vector<int> status[maxn];

int cnt,n,Left[maxn],Right[maxn];
bool f[maxn*maxn],flag[maxn];

LL Dist(node a,node b) {return 1ll*(a.x-b.x)*(a.x-b.x)+1ll*(a.y-b.y)*(a.y-b.y);}

int main() {
    int t=Get_Int();
    while(t--) {
        n=Get_Int();
        for(int i=1; i<=n; i++) {
            a[i].x=Get_Int();
            a[i].y=Get_Int();
            status[i].clear();
        }
        cnt=0;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++) {
                if(i==j)continue;
                D[++cnt]=dists(i,j,Dist(a[i],a[j]));
            }
        sort(D+1,D+cnt+1);
        for(int i=1; i<=cnt; i++) {
            status[D[i].from].push_back(i);
            Right[D[i].from]=status[D[i].from].size()-1;
            f[i]=0;
        }
        for(int i=1; i<=n; i++) {
            Left[i]=Right[i];
            flag[i]=0;
            while(Left[i]>0&&D[status[i][Left[i]-1]].dist==D[status[i][Right[i]]].dist)Left[i]--;
        }
        for(int i=cnt; i>=1; i--) {
            int y=D[i].to;
            if(Left[y]>0&&D[status[y][Left[y]-1]].dist>=D[i].dist) {
                while(Left[y]>0&&D[status[y][Left[y]-1]].dist>=D[i].dist)Left[y]--;
                while(Right[y]>0&&D[status[y][Right[y]]].dist!=D[status[y][Left[y]]].dist) {
                    if(f[status[y][Right[y]]]==1)flag[y]=1;
                    Right[y]--;
                }
            }
            if(flag[y])f[i]=0;
            else f[i]=1;
        }
        bool flag=0;
        for(int id:status[1])if(f[id]) {flag=1;break;}
        puts(flag?"YES":"NO");
    }
    return 0;
}