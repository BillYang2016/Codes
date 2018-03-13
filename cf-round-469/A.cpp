#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int l,r,a;

int main() {
	l=Get_Int();
	r=Get_Int();
	a=Get_Int();
	int Min=min(l,r),Max=max(l,r);
	if(Max-Min>a)printf("%d\n",2*(Min+a));
	else printf("%d\n",2*Max+(a-(Max-Min))/2*2);
	return 0;
}