#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

vector<int> edges[maxn];
int n,x,f[maxn][7];

void TreeDp(int Now,int fa) {
	int num=0,x1=INT_MIN/2;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		TreeDp(Next,Now);
		int last[7];
		copy(f[Now],f[Now]+7,last);
		f[Now][1]=max({f[Now][1],f[Next][1],f[Next][3]+1,f[Next][4]+1});
		f[Now][2]=max({f[Now][2],f[Next][2],f[Next][5]+1,f[Next][6]+1,f[Next][3]+last[1],f[Next][4]+last[1]});
		f[Now][3]=max(f[Now][3]+1,f[Next][3]+num);
		f[Now][4]=max(f[Now][4]+1,last[3]+f[Next][3]);
		f[Now][5]=max({f[Now][5]+1,f[Next][5]+num,last[3]+f[Next][1],last[4]+f[Next][3],last[3]+f[Next][4],f[Next][3]+x1});
		f[Now][6]=max({f[Now][6]+1,last[4]+f[Next][4],last[5]+f[Next][3],last[3]+f[Next][5],last[4]+f[Next][1]});
		x1=max(x1+1,num+max({f[Next][1],f[Next][3],f[Next][4]}));
		num++;
	}
	f[Now][3]=max(f[Now][3],num);
}

void Clear() {
	for(int i=1; i<=n; i++) {
		edges[i].clear();
		fill(f[i],f[i]+7,0);
	}
}

int main() {
	int t=Get_Int();
	x=Get_Int();
	while(t--) {
		Clear();
		n=Get_Int();
		if(x==1)Get_Int(),Get_Int();
		if(x==2)Get_Int(),Get_Int(),Get_Int(),Get_Int();
		for(int i=1; i<n; i++) {
			int x=Get_Int(),y=Get_Int();
			edges[x].push_back(y);
			edges[y].push_back(x);
		}
		TreeDp(1,0);
		printf("%d\n",max({f[1][2],f[1][5],f[1][6]}));
	}
	return 0;
}