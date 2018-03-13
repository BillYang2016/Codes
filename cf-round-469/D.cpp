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

LL n,q; 

int main() {
	n=Get_Int();
	q=Get_Int();
	while(q--) {
		LL x=Get_Int();
		if(x&1)printf("%I64d\n",(x+1)>>1);
		else {
			LL pos=n-x+1,len=n;
			while((len-pos+1)%2==0) {
				pos=(pos+1)/2;
				len=(len+1)/2;
			}
			pos=len-pos+1;
			printf("%I64d\n",((pos+1)>>1)+n-len);
		}
	}
	return 0;
}