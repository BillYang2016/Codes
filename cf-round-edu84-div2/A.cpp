#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int main() {
	int t=Get_Int();
	while(t--) {
		int n=Get_Int(),k=Get_Int();
		if((n&1)&&(k&1)) {
			if(n/k-k+1<1)puts("NO");
			else puts("YES");
		}
		if(!(n&1)&&(k&1))puts("NO");
		if((n&1)&&!(k&1))puts("NO");
		if(!(n&1)&&!(k&1)) {
			if(n/k-k+1<1)puts("NO");
			else puts("YES");
		}
	}
	return 0;
}