#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=10005,maxm=15;

int n,m,a[maxm],f[maxn];

int Solve(int n) {
	if(!n)return 0;
	if(~f[n])return f[n];
	for(int i=1; i<=m; i++)if(n>=a[i]&&!Solve(n-a[i]))return f[n]=1;
	return f[n]=0;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++)a[i]=Get_Int();
	fill(f,f+n+1,-1);
	if(Solve(n))puts("xiaoqianglll");
	else puts("Grafiore");
	return 0;
}