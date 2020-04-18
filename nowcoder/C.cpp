#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

string s1,s2;

int main() {
	ios::sync_with_stdio(false);
	cin>>s1>>s2;
	if(s1==s2)puts("-1");
	else printf("%d\n",int(max(s1.length(),s2.length())));
	return 0;
}