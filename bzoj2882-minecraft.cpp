#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=300005;

int n,s[maxn<<1];

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)s[n+i]=s[i]=Get_Int();
	int i=1,j=2,k=0;
	while(i<=n&&j<=n&&k<=n) {
		if(s[i+k]==s[j+k]) {k++;continue;}
		if(s[i+k]<s[j+k])j=j+k+1;
		else i=i+k+1;
		k=0;
		if(i==j)j++;
	}
	for(int j=0; j<n; j++)printf("%d ",s[i+j]);
	return 0;
}