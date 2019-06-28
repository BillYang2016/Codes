#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int main() {
	LL a=Get_Int(),b=Get_Int(),c=Get_Int();
	cout<<c*2+min(a,b)+min(max(a,b),min(a,b)+1);
	return 0;
}

