#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=105;

int n,d[maxn];

int main() {
	int Max=0;
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		d[i]=Get_Int();
		Max=max(Max,d[i]);
	}
	for(int i=1; i<=n; i++) {
		int s=ceil(50.0*d[i]/Max);
		putchar('+');
		for(int i=1; i<=s; i++)putchar('-');
		putchar('+');
		putchar('\n');
		putchar('|');
		for(int i=1; i<s; i++)putchar(' ');
		if(d[i]==Max) {
			if(s)putchar('*');
		} else if(s) putchar(' ');
		putchar('|');
		printf("%d\n",d[i]);
		putchar('+');
		for(int i=1; i<=s; i++)putchar('-');
		putchar('+');
		putchar('\n');
	}
	return 0;
}