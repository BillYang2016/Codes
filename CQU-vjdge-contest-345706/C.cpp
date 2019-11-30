#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=5005;

int n,rev[maxn],a[maxn];

int Solve(int len) {
	fill(rev+1,rev+n+1,0);
	int cnt=0,ans=0;
	for(int i=1; i+len-1<=n; i++) {
		if((cnt+a[i])&1) {
			cnt++;
			ans++;
			rev[i]=1;
		}
		if(i-len+1>0)cnt-=rev[i-len+1];
	}
	for(int i=n-len+2; i<=n; i++) {
		if((cnt+a[i])&1)return 0x7fffffff;
		if(i-len+1>0)cnt-=rev[i-len+1];
	}
	return ans;
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		char x=getchar();
		while(!isalpha(x))x=getchar();
		a[i]=x=='B'?1:0;
	}
	int len,ans=0x7fffffff;
	for(int i=1; i<=n; i++) {
		int cnt=Solve(i);
		if(cnt<ans) {
			ans=cnt;
			len=i;
		}
	}
	printf("%d %d\n",len,ans);
	return 0;
}