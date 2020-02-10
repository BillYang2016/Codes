#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxm=50005;

void Exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
	if(!b)d=a,x=1,y=0;
	else Exgcd(b,a%b,d,y,x),y-=(a/b)*x;
}

LL Quick_Mul(LL a,LL b,LL p) {
	LL sum=0;
	for(; b; b>>=1,a=(a<<1)%p)if(b&1)sum=(sum+a)%p;
	return sum;
}

LL Excrt(int n,LL *r,LL *m) {
	LL M=m[1],ans=r[1];
	for(int i=2; i<=n; i++) { //Mx_1+m_ix_2=a_i-ans
		LL a=M,b=m[i],x,y,c=(r[i]-ans%m[i]+m[i])%m[i],gcd;
		Exgcd(a,b,gcd,x,y);
		if(c%gcd)return -1;
		x=Quick_Mul(x,c/gcd,b/gcd);
		ans+=x*M;
		M=M/gcd*b;
		ans=(ans%M+M)%M;
	}
	return ans;
}

LL n,m,a[maxm],b[maxm];
double f[15][15][15];

double Dp(LL x,LL y,LL z) {
	if(y==0) {
		if(z!=1)return Dp(x,1,z-1);
		else return Dp(x,1,x);
	}
	if(x==2) {
		if(y==1)return z==1;
		else return 0.5;
	}
	if(f[x][y][z]!=-1)return f[x][y][z];
	if(y==1) {
		if(z==1)return f[x][y][z]=Dp(x-1,1,x-1);
		else {
			if(z==2)return f[x][y][z]=Dp(x-1,1,1);
			else if(z==x)return f[x][y][z]=Dp(x-1,1,z-2);
			else return f[x][y][z]=min(Dp(x-1,1,z-1),Dp(x-1,1,z-2));
		}
	} else {
		if(z==1) {
			double black=1,white=1;
			if(y>=2)black=Dp(x-1,y-2,x-y+2);
			if(x>y)black=min(black,Dp(x-1,y-1,x-y+1));
			if(y>2)white=Dp(x-1,y-2,1);
			if(x>y)white=min(white,Dp(x-1,y-1,1));
			return f[x][y][z]=black*(1.0/y)+white*((y-1.0)/y);
		} else {
			f[x][y][z]=1;
			if(y>=2)f[x][y][z]=Dp(x-1,y-2,z);
			if(z>2)f[x][y][z]=min(f[x][y][z],Dp(x-1,y-1,z-1));
			if(z<x-y+1)f[x][y][z]=min(f[x][y][z],Dp(x-1,y-1,z));
			return f[x][y][z];
		}
	}
}

int main() {
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		a[i]=Get_Int();
		b[i]=Get_Int();
	}
	n=Excrt(m,a,b);
	if(n<2)puts("error");
	else if(n>10)puts("0.000000");
	else {
		for(int i=0; i<=n; i++)
			for(int j=0; j<=n; j++)
				for(int k=0; k<=n; k++)f[i][j][k]=-1;
		printf("%.6lf\n",Dp(n,n,1));
	}
	return 0;
}