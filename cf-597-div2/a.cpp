#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

void Exgcd(int a,int b,int &gcd,int &x,int &y) {
	if(!b)gcd=a,x=1,y=0;
	else Exgcd(b,a%b,gcd,y,x),y-=x*(a/b);
}

int t;

int main() {
	t=Get_Int();
	while(t--) {
		int a=Get_Int(),b=Get_Int(),d,x,y;
		Exgcd(a,b,d,x,y);
		if(d==1)puts("Finite");
		else puts("Infinite");
	}
	return 0;
}