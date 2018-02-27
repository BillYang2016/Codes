#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>

using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxt=55,maxn=25,mod=1e9+7,dx[4]= {1,0,-1,0},dy[4]= {0,1,0,-1};

int n,m,T,a[maxt],F[maxt][maxn][maxn][4][13][2][13];
bool map[maxn][maxn],vst[maxt][maxn][maxn][4][13][2][13];

struct Node {
	int t,x,y,d,s1,t1,s2;
	Node(int t=0,int x=0,int y=0,int d=0,int s1=0,int t1=0,int s2=0):t(t),x(x),y(y),d(d),s1(s1),t1(t1),s2(s2) {}
} st;

#define f(X) F[X.t][X.x][X.y][X.d][X.s1][X.t1][X.s2]
#define v(X) vst[X.t][X.x][X.y][X.d][X.s1][X.t1][X.s2]

bool Check(Node x) {
	if(x.t>T)return false;
	if(x.t1==1)return true;
	for(int i=x.s1; i<=x.s1+x.s2; i++)if(a[x.t-i]==i)return false;
	return true;
}

void Bfs(Node st) {
	queue<Node> Q;
	Q.push(st);
	f(st)=v(st)=1;
	while(!Q.empty()) {
		Node Now=Q.front();
		Q.pop();
		Node Next=Node(Now.t+1,Now.x,Now.y,Now.d,0,0,Now.s1);
		if(Check(Next)) {
			f(Next)=(f(Next)+f(Now))%mod;
			if(!v(Next)) {
				v(Next)=1;
				Q.push(Next);
			}
		}
		for(int d=0; d<4; d++) {
			Node Next=Node(Now.t+1,Now.x+dx[d],Now.y+dy[d],d);
			if(map[Next.x][Next.y]==0)continue;
			if(d==Now.d)Next.s1=min(Now.s1+1,12),Next.t1=Now.t1,Next.s2=min(Now.s2,12-Next.s1);
			else Next.s1=0,Next.t1=1;
			if(!Check(Next))continue;
			f(Next)=(f(Next)+f(Now))%mod;
			if(!v(Next)) {
				v(Next)=1;
				Q.push(Next);
			}
		}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	T=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			char ch=' ';
			while(!isdigit(ch)&&ch!='.'&&ch!='*')ch=getchar();
			if(isdigit(ch)) {
				map[i][j]=1;
				st=Node(0,i,j,ch-'0',0,1,0);
			} else if(ch=='.')map[i][j]=1;
		}
	for(int i=1; i<T; i++)a[i]=Get_Int();
	a[T]=INT_MAX/2;
	Bfs(st);
	for(int x=1; x<=n; x++) {
		for(int y=1; y<=m; y++) {
			int sum=0;
			for(int d=0; d<4; d++)
				for(int s1=0; s1<=12; s1++)
					for(int t1=0; t1<=1; t1++)
						for(int s2=0; s2<=12; s2++)sum=(sum+F[T][x][y][d][s1][t1][s2])%mod;
			printf("%d ",sum);
		}
		putchar('\n');
	}
	return 0;
}