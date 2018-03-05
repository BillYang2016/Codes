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

const int maxn=200005;

namespace Suffix_Array {
	int sa[maxn],rk[maxn],fir[maxn],sec[maxn],buc[maxn],tmp[maxn],height[maxn];

	void fill_buc(int n,int m,int *a) {
		fill(buc,buc+m+1,0);
		for(int i=1; i<=n; i++)buc[a[i]]++;
		for(int i=1; i<=n; i++)buc[i]+=buc[i-1];
	}

	void build(int n,int m,int *a) {
		fill_buc(n,m,a);
		for(int i=1; i<=n; i++)rk[i]=buc[a[i]-1]+1;
		for(int t=1; t<=n; t<<=1) {
			for(int i=1; i<=n; i++) {
				fir[i]=rk[i];
				sec[i]=(i+t)>n?0:rk[i+t];
			}
			fill_buc(n,m,sec);
			for(int i=1; i<=n; i++)tmp[n-(--buc[sec[i]])]=i;
			fill_buc(n,m,fir);
			for(int i=1; i<=n; i++)sa[buc[fir[tmp[i]]]--]=tmp[i];
			bool unique=1;
			for(int j=1,last=0; j<=n; j++) {
				int i=sa[j];
				if(!last)rk[i]=1;
				else if(fir[i]==fir[last]&&sec[i]==sec[last])rk[i]=rk[last],unique=0;
				else rk[i]=rk[last]+1;
				last=i;
			}
			if(unique)break;
		}
		int k=0;
		for(int i=1; i<=n; i++) {
			if(rk[i]==1)k=0;
			else {
				if(k>0)k--;
				int j=sa[rk[i]-1];
				while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k])k++;
			}
			height[rk[i]]=k;
		}
	}
}

using namespace Suffix_Array;

int n,q,f[maxn][25],a[maxn],b[maxn];

void Sparse_Table(int len) {
	for(int i=1; i<=len; i++)f[i][0]=height[i];
	for(int j=1; j<=log2(len); j++)
		for(int i=1; i+(1<<(j-1))<=len; i++)
			f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}

int Ask(int Left,int Right) {
	int k=log2(Right-Left+1);
	return min(f[Left][k],f[Right-(1<<k)+1][k]);
}

int main() {
	n=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++)b[i]=a[i]=Get_Int();
	sort(a+1,a+n+1);
	int tot=unique(a+1,a+n+1)-a-1;
	for(int i=1; i<=n; i++)b[i]=lower_bound(a+1,a+tot+1,b[i])-a;
	build(n,tot,b);
	Sparse_Table(n);
	for(int i=1; i<=q; i++) {
		int x=Get_Int(),y=Get_Int();
		if(x==y) {
			printf("%d\n",n-x+1);
			continue;
		}
		x=rk[x];
		y=rk[y];
		if(x>y)swap(x,y);
		printf("%d\n",Ask(x+1,y));
	}
	return 0;
}