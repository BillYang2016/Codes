#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n,a,b,p,m;
char s[1000005];

struct Interval {
	int left,right;
	Interval(int l=0,int r=0):left(l),right(r) {}
	bool operator < (const Interval &b) const {return left<b.left;}
};

vector<Interval> vec;

int main() {
	n=Get_Int();
	a=Get_Int();
	b=Get_Int();
	p=Get_Int();
	m=Get_Int();
	scanf("%s",s);
	for(int i=0; i<m; i++) {
		int L,R;
		if(s[i]=='0') {
			L=(p-1ll*a*i%n+n)%n;
			R=((-1ll*a*i-1)%n+n)%n;
		} else {
			L=((-1ll*a*i)%n+n)%n;
			R=((p-1ll*a*i-1)%n+n)%n;
		}
		if(L<=R)vec.push_back(Interval(L,R));
		else vec.push_back(Interval(0,R)),vec.push_back(Interval(L,n-1));
	}
	for(int i=n-m+1; i<n; i++)vec.push_back(Interval((1ll*a*i+b)%n,(1ll*a*i+b)%n));
	sort(vec.begin(),vec.end());
	int ed=-1,ans=0;
	for(auto x:vec) {
		if(ed<x.left)ans+=x.left-ed-1;
		ed=max(ed,x.right);
	}
	printf("%d\n",ans+(n-1-ed));
	return 0;
}