#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>

using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

char s[10005];

int main() {
	scanf("%s",s);
	printf("%s",s);
	int len=strlen(s);
	reverse(s,s+len);
	printf("%s",s);
	return 0;
}