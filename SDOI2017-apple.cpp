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

void trans(int *f,const Thing& a) {
	for(int mod=0; mod<a.cost; mod++) {
		deque<pii>Q;
		for(int i=0,index; (index=i*a.cost+mod)<=m; i++) {
			while(!Q.empty()&&Q.front().first<i-a.num)Q.pop_front();
			while(!Q.empty()&&Q.back().second<=f[index]-i*a.value)Q.pop_back(); //允许自己转移到自己
			Q.push_back(mp(i,f[index]-i*a.value));
			f[index]=Q.front().second+i*a.value;
		}
	}
}

void Dfs1(int Now) {
	if(a[Now].num)trans(f+Now*Wid,a[Now]);
	for(int Next:edges[Now]) {
		memcpy(f+Next*Wid,f+Now*Wid,Len);
		Dfs1(Next);
		for(int j=1,*p=f+Now*Wid+1,*q=f+Next*Wid; j<=m; j++,p++,q++)*p=max(*p,*q+a[Next].value);
	}
}

void Dfs2(int Now,int sum) {
	y+=a[Now].value;
	for(int Next:edges[Now]) {
		memcpy(g+Next*Wid,g+Now*Wid,Len);
		Dfs2(Next,sum);
		for(int j=1,*p=g+Now*Wid+1,*q=g+Next*Wid; j<=m; j++,p++,q++)*p=max(*p,*q+a[Next].value);
	}
	if(!edges[Now].size())for(int j=1,*p=g+Now*Width+m,*q=g+Next*Width; j<=m; j++,p--,q++)ans=max(ans,*p+*q+sum);
	if(a[Now].num)trans(g+Now*Wid,a[Now]);
}

void Clear() {
	for(int i=1; i<=n; i++)edges[i].clear();
	memset(f+Wid,0,Len);
	memset(g+Wid,0,Len);
	ans=0;
}

int main() {
	int t=Get_Int();
	while(t--) {
		Clear();
		cnt=n=Get_Int();
		m=Get_Int();
		Wid=m+1;Len=Wid*sizeof(int);
		for(int i=1; i<=n; i++) {
			fa[i]=Get_Int();
			if(fa[i])AddEdge(fa[i],i);
			a[i].num=Get_Int()-1;
			a[i].val=Get_Int();
			vst[i]=1;
		}
		Dfs1(1);
		for(int i=1; i<=n; i++)edges[i].clear();
		for(int i=n; i>=1; i--)if(fa[i])AddEdge(fa[i],i);
		Dfs2(1,0);
		printf("%d\n",ans);
	}
	return 0;
}