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

int n,m,a[maxn],b[maxn];

int main() {
	n=Get_Int();Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	m=Get_Int();Get_Int();
	for(int i=1; i<=m; i++)b[i]=Get_Int();
	int ans=2; //diff=0
	for(int k=1; k<=1e9; k<<=1) {
		map<int,int> M;
		for(int i=1; i<=n; i++)ans=max(ans,++M[(a[i]+k)%(2*k)]);
		for(int i=1; i<=m; i++)ans=max(ans,++M[b[i]%(2*k)]);
	}
	printf("%d\n",ans);
	return 0;
}