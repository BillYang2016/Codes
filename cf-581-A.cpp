#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

string s;
int cnt=0;

int main() {
	cin>>s;
	int n=s.length();
	for(auto ch:s)if(ch=='1')cnt++;
	if(n==1&&cnt==0)puts("0");
	else if(cnt!=1&&n%2==1)printf("%d\n",n/2+1);
	else printf("%d\n",n/2);
	return 0;
}

