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

const int maxn=300005;
const LL mod=1e9+7;

struct Matrix {
	const static int n=3;
	LL a[n][n];
	Matrix(bool f=0) {
		memset(a,0,sizeof(a));
		for(int i=0; i<n; i++)a[i][i]=f;
	}
	LL* operator [] (const int x) {
		return a[x];
	}
	Matrix T() {
		Matrix c(n);
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)c[j][i]=a[i][j];
		return c;
	}
	Matrix operator + (Matrix b) {
		Matrix c;
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)c[i][j]=a[i][j]+b[i][j]>=mod?a[i][j]+b[i][j]-mod:a[i][j]+b[i][j];
		return c;
	}
	Matrix operator * (Matrix b) {
		Matrix c;
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++) {
				for(int k=0; k<n; k++)c[i][j]+=a[i][k]*b[k][j];
				c[i][j]%=mod;
			}
		return c;
	}
	Matrix operator ^ (LL k) {
		Matrix a=*this,c(1);
		for(; k; k>>=1,a=a*a)if(k&1)c=c*a;
		return c;
	}
} linc,rinc,ldec,rdec,lf,rf,null=Matrix(),e=Matrix(1);

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL inv(LL x) {
	return Quick_Pow(x,mod-2);
}

LL a,b,A[maxn];

void Build_Matrix() {
	if(a) {
		linc[0][0]=1,linc[0][1]=a,linc[0][2]=b,linc[1][0]=1,linc[2][2]=1;
		ldec[0][1]=1,ldec[1][0]=inv(a),ldec[1][1]=mod-inv(a),ldec[1][2]=mod-b*inv(a)%mod,ldec[2][2]=1;
		lf[0][0]=2,lf[1][0]=1,lf[2][0]=1;
	} else {
		linc[0][0]=1,linc[0][1]=b,linc[1][1]=1;
		ldec[0][0]=1,ldec[0][1]=mod-b,ldec[1][1]=1;
		lf[0][0]=2,lf[1][0]=1;
	}
	rinc=linc.T(),rdec=ldec.T(),rf=lf.T();
}

struct Segment_Tree {
	struct Tree {
		int left,right;
		Matrix l,r,sum;
		Tree(int l=0,int r=0):left(l),right(r),l(e),r(e),sum(e) {}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index].sum=(linc^(A[Left-1]+1-2))*lf*rf*(rinc^(A[Left+1]-1-2));
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].sum=tree[ls].sum+tree[rs].sum;
	}
	void modify(int index,Matrix l,Matrix r) {
		tree[index].sum=l*tree[index].sum*r;
		tree[index].l=l*tree[index].l;
		tree[index].r=tree[index].r*r;
	}
	void push_down(int index) {
		modify(ls,tree[index].l,tree[index].r);
		modify(rs,tree[index].l,tree[index].r);
		tree[index].l=tree[index].r=e;
	}
	void modify(int index,int Left,int Right,Matrix l,Matrix r) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			modify(index,l,r);
			return;
		}
		push_down(index);
		modify(ls,Left,Right,l,r);
		modify(rs,Left,Right,l,r);
		push_up(index);
	}
	Matrix query(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return null;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].sum;
		push_down(index);
		return query(ls,Left,Right)+query(rs,Left,Right);
	}
} st;

int n,q;

int main() {
	n=Get_Int();
	q=Get_Int();
	a=Get_Int();
	b=Get_Int();
	for(int i=1; i<=n; i++)A[i]=Get_Int();
	Build_Matrix();
	st.build(1,2,n-1);
	while(q--) {
		char opt=' ';
		while(!isalpha(opt))opt=getchar();
		int x=Get_Int(),y=Get_Int();
		if(opt=='p')st.modify(1,x+1,y+1,linc,e),st.modify(1,x-1,y-1,e,rinc);
		else if(opt=='m')st.modify(1,x+1,y+1,ldec,e),st.modify(1,x-1,y-1,e,rdec);
		else printf("%lld\n",st.query(1,x+1,y-1)[0][0]);
	}
	return 0;
}