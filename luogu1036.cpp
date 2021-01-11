#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn=25;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

bool Check(LL x) {
	LL up=sqrt(x);
	for(int i=2; i<=up; i++)if(x%i==0)return false;
	return true;
}

int n,k,cnt=0;
LL a[maxn];

void Dfs(int Depth,int pos,LL sum) {
	if(Depth==k+1) {
		if(Check(sum))cnt++;
		return;
	}
	for(int i=pos; i<=n; i++)Dfs(Depth+1,i+1,sum+a[i]);
}

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	Dfs(1,1,0);
	printf("%d\n",cnt);
	return 0;
}