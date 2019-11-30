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

vector<LL> ans;

void Cal(LL x,LL y) {
	LL gcd=__gcd(x,y);
	x/=gcd;
	y/=gcd;
	ans.push_back(x/y);
	if(x%y==1) {
		ans.push_back(y);
		return;
	}
	Cal(y,x%y);
}

int main() {
	int t=Get_Int();
	while(t--) {
		ans.clear();
		LL a=Get_Int(),b=Get_Int();
		Cal(a,b);
		for(int i=0; i<ans.size()-1; i++)printf("%lld ",ans[i]);
		printf("%lld\n",ans.back());
	}
	return 0;
}