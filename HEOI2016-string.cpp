#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005,K=20;

namespace Suffix_Array {
	int sa[maxn],rk[maxn],fir[maxn],sec[maxn],buc[maxn],tmp[maxn],height[maxn];

	void fill_buc(int n,int *a) {
		fill(buc,buc+n+1,0);
		for(int i=1; i<=n; i++)buc[a[i]]++;
		for(int i=1; i<=n; i++)buc[i]+=buc[i-1];
	}

	void build(int n,int *a) {
		fill_buc(n,a);
		for(int i=1; i<=n; i++)rk[i]=buc[a[i]-1]+1;
		for(int t=1; t<=n; t<<=1) {
			for(int i=1; i<=n; i++) {
				fir[i]=rk[i];
				sec[i]=(i+t)>n?0:rk[i+t];
			}
			fill_buc(n,sec);
			for(int i=1; i<=n; i++)tmp[n-(--buc[sec[i]])]=i;
			fill_buc(n,fir);
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

struct President_Tree {
	struct Tree {
		int lson,rson,size;
	} tree[maxn*20];
	int size;
#define mid ((left+right)>>1)
	int insert(int left,int right,int pre,int val) {
		int now=++size;
		tree[now]=tree[pre];
		tree[now].size++;
		if(left==right)return now;
		if(val<=mid)tree[now].lson=insert(left,mid,tree[pre].lson,val);
		else tree[now].rson=insert(mid+1,right,tree[pre].rson,val);
		return now;
	}
	int query(int left,int right,int Left,int Right,int lt,int rt) {
		if(Right<left||Left>right)return 0;
		if(Left<=left&&Right>=right)return tree[rt].size-tree[lt].size;
		return query(left,mid,Left,Right,tree[lt].lson,tree[rt].lson)+query(mid+1,right,Left,Right,tree[lt].rson,tree[rt].rson);
	}
} pt;

#undef mid

int n,m,a,b,c,d,f[maxn][K],g[maxn][K],root[maxn],A[maxn],B[maxn];
char s[maxn],t[maxn];

bool Check(int x) {
	int L=rk[c],R=rk[c]+1;
	for(int i=K-1; i>=0; i--) {
		if(L-(1<<i)>=1&&f[L][i]>=x)L-=1<<i;
		if(R+(1<<i)<=n&&g[R][i]>=x)R+=1<<i;
	}
	return pt.query(1,n,a,b-x+1,root[L-1],root[R-1]);
}

int main() {
	n=Get_Int();
	m=Get_Int();
	scanf("%s",s+1);
	copy(s+1,s+n+1,t+1);
	for(int i=1; i<=n; i++)A[i]=B[i]=s[i]-'a';
	sort(A+1,A+n+1);
	int tot=unique(A+1,A+n+1)-A-1;
	for(int i=1; i<=n; i++)B[i]=lower_bound(A+1,A+tot+1,B[i])-A;
	build(n,B);
	for(int i=1; i<=n; i++) {
		root[i]=pt.insert(1,n,root[i-1],sa[i]);
		f[i][0]=g[i][0]=height[i];
	}
	for(int j=1; j<K; j++)
		for(int i=1; i<=n; i++) {
			if(i-(1<<(j-1))>=1)f[i][j]=min(f[i][j-1],f[i-(1<<(j-1))][j-1]);
			if(i+(1<<(j-1))<=n)g[i][j]=min(g[i][j-1],g[i+(1<<(j-1))][j-1]);
		}
	while(m--) {
		a=Get_Int(),b=Get_Int(),c=Get_Int(),d=Get_Int();
		int Left=1,Right=min(b-a+1,d-c+1);
		while(Left<=Right) {
			int mid=(Left+Right)>>1;
			if(Check(mid))Left=mid+1;
			else Right=mid-1;
		}
		printf("%d\n",Right);
	}
	return 0;
}