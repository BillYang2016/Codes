#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=205;

int n,a[maxn];
char tmp[maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		int Max=0;
		for(int i=1; i<=n; i++)a[i]=Get_Int(),Max=max(Max,a[i]);
		Max++;
		for(int i=1; i<=Max; i++)tmp[i]='a';
		for(int i=1; i<=Max; i++)printf("a");
		putchar('\n');
		for(int i=1; i<=n; i++) {
			tmp[a[i]+1]=tmp[a[i]+1]+1;
			if(tmp[a[i]+1]=='z'+1)tmp[a[i]+1]='a';
			for(int j=1; j<=Max; j++)printf("%c",tmp[j]);
			putchar('\n');
		}
	}
	return 0;
}