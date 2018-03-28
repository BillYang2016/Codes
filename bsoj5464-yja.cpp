#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const double eps=1e-8,pi=acos(-1);

int dcmp(double x) {return fabs(x)<=eps?0:(x>eps?1:-1);}

int n;
double r[15],theta[15],ans=0;

double Cal(double lambda) {
	double sum=0;
	r[n+1]=r[1];
	for(int i=1; i<=n; i++)theta[i]=acos(lambda/(r[i]*r[i+1])),sum+=theta[i];
	return sum;
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)r[i]=Get_Int();
	sort(r+1,r+n+1);
	for(; n>=3; n--) {
		double L=-r[1]*r[2],R=r[1]*r[2];
		do {
			double Left=L,Right=R;
			while(Right-Left>=eps) {
				double mid=(Left+Right)/2;
				if(Cal(mid)>=2*pi)Left=mid;
				else Right=mid;
			}
			double mid=(Left+Right)/2;
			if(dcmp(Cal(mid)-2*pi)==0) {
				double sum=0;
				theta[n+1]=theta[1];
				for(int i=1; i<=n; i++)sum+=sin(theta[i])*r[i]*r[i+1];
				ans=max(ans,sum);
			}
		} while(next_permutation(r+1,r+n+1));
		sort(r+1,r+n+1);
		for(int i=1; i<n; i++)r[i]=r[i+1];
	}
	printf("%0.8lf\n",ans/2);
	return 0;
}