#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

LL k,fac[25];
int n,a[25],num[25];

void Cal(int n,LL k) {
	vector<int> ans;
	for(int i=1; i<=n; i++)num[i-1]=i;
	if(k==0)k=fac[n];
	k--;
	for(int i=n; i>=1; i--) {
		int j=k/fac[i-1];
		k%=fac[i-1];
		ans.push_back(num[j]);
		for(int pos=j; pos<n; pos++)num[pos]=num[pos+1];
	}
	for(int x:ans)printf("%d%c",x,x==ans.back()?'\n':' ');
}

int main() {
	fac[0]=1;
	for(int i=1; i<=20; i++)fac[i]=fac[i-1]*i;
	int t;
	scanf("%d",&t);
	while(t--) {
		scanf("%d%lld",&n,&k);
		k=k%fac[n];
		for(int i=1; i<=n; i++)scanf("%d",&a[i]);
		LL num=0;
		for(int i=1; i<=n; i++) {
			int cnt=0;
			for(int j=i+1; j<=n; j++)if(a[j]<a[i])cnt++;
			num+=fac[n-i]*cnt;
		}
		num++;
		Cal(n,(k+num)%fac[n]);
	}
	return 0;
}