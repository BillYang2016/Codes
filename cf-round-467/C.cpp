#include<bits/stdc++.h>

using namespace std;

inline long long Get_Int() {
	long long num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

double k,d,t;

int main() {
	k=Get_Int();
	d=Get_Int();
	t=Get_Int();
	double x=ceil(k/d)*d,delta=x-k;
	double period=k*1.0+delta*0.5;
	double times=floor(t/period);
	double remain=t-times*period,ans=times*x;
	if(k>remain)printf("%0.1lf\n",ans+remain);
	else printf("%0.1lf\n",ans+k+(remain-1.0*k)/0.5);
	return 0;
}