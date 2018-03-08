#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n,a[105];

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	sort(a+1,a+n+1);
	int tot=unique(a+1,a+n+1)-a-1;
	printf("%d\n",tot-(a[1]==0));
	return 0;
}