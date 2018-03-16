#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;

int n,f[maxn];
bool ban[maxn][26];
char s[maxn];

int main() {
	n=Get_Int();
	f[1]=1;
	for(int i=1; i<=n; i++)f[i<<1]=Get_Int()+1;
	for(int i=1; i<n; i++)f[i<<1|1]=Get_Int()+1;
	int Max=0,id=0;
	for(int i=1; i<=(n<<1); i++) {
		if(i&1)s[i]='#';
		else if(!s[i])for(char c='a'; c<='z'; c++)if(!ban[i][c-'a']) {s[i]=c;break;}
		int len=id+Max>i?min(f[2*id-i],id+Max-i):1;
		while(len<f[i])s[i+len]=s[i-len],len++;
		if(i-f[i]>=1&&(i-f[i])%2==0)ban[i+f[i]][s[i-f[i]]-'a']=1;
		if(id+f[i]>Max) {Max=f[i];id=i;}
	}
	for(int i=2; i<=(n<<1); i+=2)putchar(s[i]);
	return 0;
}