#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

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

const int maxn=1005;

int n,a[maxn],b[maxn],pos[maxn];

void Discretization() {
	memcpy(b,a,sizeof(b));
	sort(a+1,a+n+1);
	int cnt=unique(a+1,a+n+1)-a-1;
	for(int i=1; i<=n; i++)b[i]=lower_bound(a+1,a+cnt+1,b[i])-a;
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	Discretization();
	for(int i=1; i<=n; i++) {
		b[i]=n-b[i]+1;
		pos[b[i]]=i;
	}
	memset(f,0x3f,sizeof(f));
	f[n+1][n+1]=0;
	for(int i=n; i>=1; i--) {
		int c1=1,c2=1;
		for(int j=1; j<pos[i]; j++)
			if(b[j]<i)c1++;
		for(int j=1; j<=n+1; j++) {
			f[i][j]=f[i+1][j]+c1+c2-1;
			if(b[j]<i+1)c2++;
		}
		int c=0;
		for(int j=pos[i]+1; j<=n+1; j++) {
			f[i][pos[i]]=min(f[i][pos[i]],f[i+1][j]+c);
			if(b[j]<i)c+=i-b[j];
		}
	}
	int ans=INT_MAX;
	for(int i=1; i<=n+1; i++)ans=min(ans,f[1][i]);
	printf("%d\n",ans);
	return 0;
}