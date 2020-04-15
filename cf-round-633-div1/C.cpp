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

const int num[]= {0,2,3,1};

int main() {
	int t=Get_Int();
	while(t--) {
		LL n=Get_Int();
		if(n<=4) {cout<<n<<endl;continue;}
		LL val=1;
		while(val<=n)val*=4;
		val/=4;
		LL x=n-val+1; //距离010000...还有x个数
		LL a=(x-1)/3,b=x%3;
		LL ans1=val+a,ans2=2*val;
		if(b==1) {cout<<ans1<<endl;continue;}
		LL base4=1;
		while(a) {
			ans2+=num[a%4]*base4;
			a/=4;
			base4*=4;
		}
		if(b==2) {cout<<ans2<<endl;continue;}
		else cout<<(ans1^ans2)<<endl;
	}
	return 0;
}