#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=10485765;

int n,m,g[maxn];
char s[maxn];

int main() {
	m=Get_Int();
	n=Get_Int();
	scanf("%s",s);
	if(n==1) {printf("%d\n%s",m,s);return 0;}
	int Max=pow(m,n-1);
	printf("%d\n",Max*m+n-1);
	for(int i=1; i<n; i++)putchar(s[0]);
	for(int i=0,j; g[i]<m; i=j) {
		putchar(s[m-1-g[i]]);
		j=i*m%Max+(m-1-g[i]);
		g[i]++;
	}
	return 0;
}