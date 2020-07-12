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

typedef long long LL;

int L,R,a[maxn];
LL cost,f[25][maxn],cnt[maxn];

LL Move(int left,int right) {
	while(L<left)cost-=--cnt[a[L++]];
	while(L>left)cost+=cnt[a[--L]]++;
	while(R<right)cost+=cnt[a[++R]]++;
	while(R>right)cost-=--cnt[a[R--]];
	return cost;
}

LL Cal(int k,int from,int to) {return f[k-1][from]+Move(from+1,to);}

void Solve(int k,int Left,int Right,int left,int right) {
	if(Left>Right)return;
	int mid=(Left+Right)>>1,id=left;
	f[k][mid]=Cal(k,left,mid);
	for(int i=left+1; i<=min(mid-1,right); i++) {
		int tmp=Cal(k,i,mid);
		if(tmp<=f[k][mid]) {f[k][mid]=tmp;id=i;}
	}
	Solve(k,Left,mid-1,left,id);
	Solve(k,mid+1,Right,id,right);
}

int n,k;

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		f[1][i]=f[1][i-1]+cnt[a[i]]++;
	}
	for(int i=2; i<=k; i++) {
		fill(cnt+1,cnt+n+1,0);
		L=R=1;
		cnt[a[1]]=1;
		Solve(i,1,n,0,n-1);
	}
	printf("%lld\n",f[k][n]);
	return 0;
}