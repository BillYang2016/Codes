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

typedef long long LL;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=1000005;

int n,m;
LL a[maxn],sum[maxn],pre0[maxn],pre1[maxn],suc0[maxn],suc1[maxn];

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	sort(a+1,a+n+1,greater<int>());
	pre0[0]=pre1[0]=-1;
	for(int i=1; i<=n; i++)
		if(a[i]&1)pre0[i]=pre0[i-1],pre1[i]=a[i];
		else pre0[i]=a[i],pre1[i]=pre1[i-1];
	suc0[n+1]=suc1[n+1]=-1;
	for(int i=n; i>=1; i--)
		if(a[i]&1)suc0[i]=suc0[i+1],suc1[i]=a[i];
		else suc0[i]=a[i],suc1[i]=suc1[i+1];
	for(int i=1; i<=n; i++)sum[i]=sum[i-1]+a[i];
	int t=Get_Int();
	while(t--) {
		int k=Get_Int();
		if(sum[k]&1)printf("%lld\n",sum[k]);
		else {
			LL ans=-1;
			if(~pre0[k]&&~suc1[k+1])ans=max(ans,sum[k]-pre0[k]+suc1[k+1]);
			if(~pre1[k]&&~suc0[k+1])ans=max(ans,sum[k]-pre1[k]+suc0[k+1]);
			printf("%lld\n",ans);
		}
	}
	return 0;
} 
