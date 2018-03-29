#include<bits/stdc++.h>

#define double long double

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const double eps=1e-8,pi=acos(-1);

int n,x,y,a,b,c;

int main() {
	int T=Get_Int();
	for(int t=1; t<=T; t++) {
		n=Get_Int(),x=Get_Int(),y=Get_Int(),a=Get_Int(),b=Get_Int(),c=Get_Int();
		double sumx=x,sumy=y,sumx2=x*x,sumy2=y*y,sumxy=x*y;
		for(int i=2; i<=n; i++) {
			x=(a*x*x+b*x+c)%107;
			y=(a*y*y+b*y+c)%107;
			sumx+=x,sumy+=y,sumx2+=x*x,sumy2+=y*y,sumxy+=x*y;
		}
		if(fabs(sumx*sumy/n-sumxy)<=eps) {printf("Case %d: 0.00000\n",t);continue;}
		double C=(sumy2-sumx2+(sumx*sumx-sumy*sumy)/n)/(sumx*sumy/n-sumxy),B=(-C+sqrt(C*C+4))/2,A=(sumy-B*sumx)/n;
		double ans=(sumy2+n*A*A+B*B*sumx2-2*A*sumy-2*B*sumxy+2*A*B*sumx)/(1+B*B);
		B=(-C-sqrt(C*C+4))/2,A=(sumy-B*sumx)/n;
		ans=fmin(ans,(sumy2+n*A*A+B*B*sumx2-2*A*sumy-2*B*sumxy+2*A*B*sumx)/(1+B*B));
		printf("Case %d: %0.5Lf\n",t,ans*pi/n);
	}
	return 0;
}