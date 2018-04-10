#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1205;

#define pii pair<int,int>

int n,m,step=0,top=0,BCC=0,Dfn[maxn],Lowlink[maxn],Belong[maxn],Stack[maxn],id[maxn];
bool Instack[maxn];
pii p[maxn];
vector<int> edges[maxn];

void Tarjan(int Now) {
	Dfn[Now]=Lowlink[Now]=++step;
	Instack[Stack[++top]=Now]=1;
	for(int Next:edges[Now]) {
		if(!Dfn[Next])Tarjan(Next),Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
		else if(Instack[Next])Lowlink[Now]=min(Lowlink[Now],Dfn[Next]);
	}
	if(Dfn[Now]==Lowlink[Now]) {
		BCC++;
		int y;
		do {
			y=Stack[top--];
			Belong[y]=BCC;
			Instack[y]=0;
		} while(y!=Now);
	}
}

void Clear() {
	step=top=BCC=0;
	memset(Dfn,0,sizeof(Dfn));
	for(int i=0; i<(m<<1); i++)edges[i].clear();
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int(),m=Get_Int();
		if(m>3*n-6) {
			for(int i=0; i<m; i++)Get_Int(),Get_Int();
			for(int i=1; i<=n; i++)Get_Int();
			puts("NO");
			continue;
		}
		Clear();
		for(int i=0; i<m; i++)p[i]=pii(Get_Int(),Get_Int());
		for(int i=1; i<=n; i++)id[Get_Int()]=i;
		for(int i=0; i<m; i++)
			for(int j=i+1; j<m; j++) {
				int x1=id[p[i].first],y1=id[p[i].second],x2=id[p[j].first],y2=id[p[j].second];
				if(x1>y1)swap(x1,y1);if(x2>y2)swap(x2,y2);
				if((x1<x2&&x2<y1&&y1<y2)||(x2<x1&&x1<y2&&y2<y1)) {
					edges[i<<1].push_back(j<<1|1),edges[j<<1|1].push_back(i<<1);
					edges[i<<1|1].push_back(j<<1),edges[j<<1].push_back(i<<1|1);
				}
			}
		for(int i=0; i<(m<<1); i++)if(!Dfn[i])Tarjan(i);
		bool bj=1;
		for(int i=0; i<(m<<1); i++)if(Belong[i]==Belong[i^1]) {bj=0;break;}
		puts(bj?"YES":"NO");
	}
	return 0;
}