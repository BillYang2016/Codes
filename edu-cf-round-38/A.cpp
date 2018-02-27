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

int n;
char s[105];
bool vst[105];

bool vow(char x) {
	return x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='y';
}

int main() {
	n=Get_Int();
	scanf("%s",s+1);
	for(int i=1; i<n; i++)if(vow(s[i])&&vow(s[i+1]))vst[i+1]=1;
	for(int i=1; i<=n; i++)if(!vst[i])putchar(s[i]);
	return 0;
}