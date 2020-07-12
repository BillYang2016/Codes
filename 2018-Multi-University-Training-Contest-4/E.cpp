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

int n;
LL a[15],M[105][105],sum[105][105];

LL Cal(int x,int y) {
	int numx=x/n,numy=y/n,resx=x%n,resy=y%n;
	return sum[n-1][n-1]*numx*numy+numx*sum[n-1][resy]+numy*sum[resx][n-1]+sum[resx][resy];
}

int main() {
	int t=Get_Int();
	while(t--) {
		int len=Get_Int();
		if(len&1)n=len;
		else n=len<<1;
		for(int i=0; i<len; i++)a[i]=Get_Int();
		int p=0;
		for(int i=0; i<(n<<1); i++)
			for(int j=0; j<=i; j++) {
				M[j][i-j]=a[p];
				p=(p+1)%len;
			}
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+M[i][j];
		int m=Get_Int();
		while(m--) {
			int x0=Get_Int(),y0=Get_Int(),x1=Get_Int(),y1=Get_Int();
			printf("%lld\n",Cal(x1,y1)-Cal(x0-1,y1)-Cal(x1,y0-1)+Cal(x0-1,y0-1));
		}
	}
	return 0;
}