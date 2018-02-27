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

typedef long long LL;

inline const LL Get_Int() {
	LL num=0,bj=1;
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

const int maxn=400005,K=20;

LL sum[maxn][K],val[maxn];
int n,p[maxn][K],lastans;

void Sparse_Table(int Now,int fa) {
	int pos=fa;
	for(int i=K-1; i>=0; i--)if(~p[pos][i]&&val[p[pos][i]]<val[Now])pos=p[pos][i];
	if(val[fa]>=val[Now]) {
		p[Now][0]=fa;
		sum[Now][0]=val[fa];
	} else {
		p[Now][0]=p[pos][0];
		sum[Now][0]=val[p[pos][0]];
	}
	for(int i=1; i<K; i++)
		if(~p[Now][i-1]) {
			p[Now][i]=p[p[Now][i-1]][i-1];
			sum[Now][i]=sum[Now][i-1]+sum[p[Now][i-1]][i-1];
		} else break;
}

int main() {
	int t=Get_Int();
	memset(p,-1,sizeof(p));
	p[n=1][0]=-1;
	while(t--) {
		int opt=Get_Int();
		if(opt==1) {
			LL x=Get_Int()^lastans;
			val[++n]=Get_Int()^lastans;
			Sparse_Table(n,x);
		} else {
			LL x=Get_Int()^lastans,lim=Get_Int()^lastans,now=val[x];
			if(val[x]>lim) {
				printf("%d\n",lastans=0);
				continue;
			}
			lastans=1;
			for(int j=K-1; j>=0; j--)
				if(~p[x][j]&&now+sum[x][j]<=lim) {
					lastans+=1<<j;
					now+=sum[x][j];
					x=p[x][j];
				}
			printf("%d\n",lastans);
		}
	}
	return 0;
}