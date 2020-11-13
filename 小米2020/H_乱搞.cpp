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

typedef long long LL;

struct Thing {
	int cost,value;
	bool bj=0;
	bool operator < (const Thing &b) const {return 1ll*value*b.cost>1ll*b.value*cost;}
} a[maxn];

int n,m;
LL f[maxn];

int main() {
	while(scanf("%d%d",&n,&m)!=EOF) {
		for(int i=1; i<=n; i++) {
			a[i].cost=Get_Int();
			a[i].value=Get_Int();
			a[i].bj=0;
		}
		sort(a+1,a+n+1);
		LL ans=0,ans2=0;
		for(int i=1; i<=n; i++)
			if(m-a[i].cost>=500) {
				m-=a[i].cost;
				a[i].bj=1;
				ans+=a[i].value;
			}
		for(int i=0; i<=m; i++)f[i]=0;
		for(int i=1; i<=n; i++)if(!a[i].bj)
			for(int j=m; j>=a[i].cost; j--)f[j]=max(f[j-a[i].cost]+a[i].value,f[j]);
		for(int i=0; i<=m; i++)ans2=max(ans2,f[i]);
		printf("%lld\n",ans+ans2);
	}
	return 0;
}