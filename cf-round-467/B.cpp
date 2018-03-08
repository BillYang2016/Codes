#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int p,y;

int main() {
	p=Get_Int();
	y=Get_Int();
	for(; y>p; y--) {
		int x=y;
		for(int i=2; i<=sqrt(y); i++)if(y%i==0) {x=i;break;}
		if(x>p) {printf("%d\n",y);return 0;}
	}
	puts("-1");
	return 0;
}