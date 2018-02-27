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

const int maxn=100005,maxc=4;
const double eps=1e-5;

int f[maxn][maxc];
vector<int> edges[maxn];

int Get_Father(int x) {
	if(father[x]==x)return x;
	return father[x]=Get_Father(father[x]);
}

void Find_Circle() {
	for(int i=1; i<=n; i++)father[i]=i;
	for(int i=1; i<n+k; i++) {
		int fx=Get_Father(from[i]),fy=Get_Father(to[i]);
		if(fx!=fy) {
			AddEdge(from[i],to[i]),AddEdge(to[i],from[i]);
			father[fx]=fy;
		} else Cir.push_back(mp(from[i],to[i]));
	}
}

void TreeDp(int Now,int father) {
	int chose=0,notchose=0;
	for(int i=0; i<Cir.size(); i++) {
		pii x=Cir[i];
		if(x.first==Now) {
			for(int i=0; i<maxc; i++)f[Now][i]=-1e18;
			f[Now][c[i]]=Cal(c[i]);
			chose=c[i];
		}
		if(x.second==Now) {
			for(int i=0; i<maxc; i++)
				if(f[Now][i]==-1e18)continue;
				else f[Now][i]=Cal(c[i]);
			f[Now][c[i]]=-1e18;
			notchose=c[i];
		}
	}
	for(int Next:edges[Now]) {
		if(Next==father)continue;
		TreeDp(Next);
		for(int i=0; i<maxc; i++) {
			if(bj1&&i!=chose)continue;
			if(bj2&&i==notchose)continue;
			LL tmp=-1e18;
			for(int j=0; j<maxc; j++) {
				if(i==j)continue;
				tmp=max(tmp,f[Next][j]);
			}
			f[Now][i]+=tmp;
		}
	}
}

bool Check() {
	double ans=0;
	if(k==0) {
		TreeDp(1,0);
		for(int i=0; i<maxc; i++)ans=max(ans,f[1][i]);
	} else if(k==1) {
		for(c[0]=0; c[0]<maxc; c[0]++) {
			TreeDp(1,0);
			for(int i=0; i<maxc; i++)ans=max(ans,f[1][i]);
		}
	} else if(k==2) {
		for(c[0]=0; c[0]<maxc; c[0]++)
			for(c[1]=0; c[1]<maxc; c[1]++) {
				if(Cir[0].first==Cir[1].first&&c[0]!=c[1])continue;
				TreeDp(1,0);
				for(int i=0; i<maxc; i++)ans=max(ans,f[1][i]);
			}
	}
	return ans>=mid;
}

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<n+k; i++) {
		int x=Get_Int(),y=Get_Int();
		from[i]=x;
		to[i]=y;
	}
	scanf("%lf",&p);
	Find_Circle();
	double Left=0,Right=n/(1.0+p*n);
	while(Right-Left>eps) {
		mid=(Left+Right)>>1;
		if(Check())Left=mid;
		else Right=mid;
	}
	printf("%0.3lf\n",Left);
	return 0;
}