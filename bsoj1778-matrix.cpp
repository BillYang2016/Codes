#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=75;

int p;

void add(LL &x,LL v) {x=x+v>=p?x+v-p:x+v;}

struct Matrix {
	int n;
	LL a[maxn][maxn];
	Matrix(int n=0,bool f=0):n(n) {
		memset(a,0,sizeof(a));
		for(int i=0; i<n; i++)a[i][i]=f;
	}
	LL* operator [] (const int x) {return a[x];}
	Matrix operator * (Matrix b) {
		Matrix c(n);
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++) {
				for(int k=0; k<n; k++)c[i][j]+=a[i][k]*b[k][j];
				c[i][j]%=p;
			}
		return c;
	}
	bool operator == (const Matrix &b) const {
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)if(a[i][j]!=b.a[i][j])return false;
		return true;
	}
	struct hasher {
		size_t operator() (const Matrix &b) const{
			unsigned long long ha=0;
			for(int i=0; i<b.n; i++)
				for(int j=0; j<b.n; j++)ha=ha*131+b.a[i][j];
			return ha;
		}
	};
};

int n;

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)ans=ans*a%p;
	return ans;
}

LL inv(LL x) {return Quick_Pow(x,p-2);}

Matrix inv(Matrix a) { //Gauss_Jordan
	Matrix b(n,1);
	for(int i=0; i<n; i++) {
		int row=i;
		for(; row<n; row++)if(a[row][i])break;
		if(row!=i)for(int j=0; j<n; j++)swap(a[i][j],a[row][j]),swap(b[i][j],b[row][j]);
		LL t=inv(a[i][i]);
		for(int j=0; j<n; j++)a[i][j]=a[i][j]*t%p,b[i][j]=b[i][j]*t%p;
		for(int j=0; j<n; j++)
			if(j!=i) {
				t=a[j][i];
				for(int k=0; k<n; k++) {
					add(a[j][k],p-t*a[i][k]%p);
					add(b[j][k],p-t*b[i][k]%p);
				}
			}
	}
	return b;
}

LL BSGS(const Matrix &a,const Matrix &b,LL p) {
	static unordered_map<Matrix,int,Matrix::hasher> M;
	LL mid=ceil(sqrt(p));
	Matrix sum=Matrix(n,1);
	for(int i=0; i<mid; i++) {
		if(!M.count(sum))M[sum]=i;
		sum=sum*a;
	}
	Matrix neg=inv(sum);
	sum=b;
	for(int i=0; i<mid; i++) {
		if(M.count(sum))return i*mid+M[sum];
		sum=sum*neg;
	}
	return -1;
}

int main() {
	n=Get_Int();
	p=Get_Int();
	Matrix A(n),B(n);
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)A[i][j]=Get_Int();
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)B[i][j]=Get_Int();
	printf("%lld\n",BSGS(A,B,p));
	return 0;
}