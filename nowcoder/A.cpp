#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int a[10];

int main() {
	for(int i=1; i<=4; i++)a[i]=Get_Int();
	sort(a+1,a+5);
	cout<<abs((a[1]+a[4])-(a[2]+a[3]))<<endl;
	return 0;
}