#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int K=30;

int n,a[18],ans=INT_MAX;

void Dfs(int Now,int sum) {
	if(sum>=ans)return;
	if(Now<0) {ans=sum;return;}
	int sum1=0;
	for(int i=1; i<=n; i++)if(a[i]&(1<<Now))sum1++;
	if(sum1%2==0) {Dfs(Now-1,sum);return;}
	int Min=INT_MAX,Max=INT_MIN,posmin=0,posmax=0;
	for(int i=1; i<=n; i++)
		if(a[i]&(1<<Now)) {if((a[i]&((1<<(Now+1))-1))<Min)Min=(a[i]&((1<<(Now+1))-1)),posmin=i;}
		else {if((a[i]&((1<<(Now+1))-1))>Max)Max=(a[i]&((1<<(Now+1))-1)),posmax=i;}
	if(posmax) {
		int tmp=a[posmax];
		a[posmax]=0;
		Dfs(Now-1,sum+(1<<Now)-(tmp&((1<<Now)-1)));
		a[posmax]=tmp;
	}
	if(posmin) {
		int tmp=a[posmin];
		a[posmin]=(1<<Now)-1;
		Dfs(Now-1,sum+(tmp&((1<<(Now+1))-1))-a[posmin]);
		a[posmin]=tmp;
	}
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		if(n==2) {printf("%d\n",abs(a[1]-a[2]));continue;}
		ans=INT_MAX;
		Dfs(K-1,0);
		printf("%d\n",ans);
	}
	return 0;
}