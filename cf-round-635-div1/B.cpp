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

vector<int> r,g,b;

LL Cal(LL x,LL y,LL z) {return (x-y)*(x-y)+(y-z)*(y-z)+(x-z)*(x-z);}

int main() {
	int t=Get_Int();
	while(t--) {
		int nr=Get_Int(),ng=Get_Int(),nb=Get_Int();
		r.clear(),g.clear(),b.clear();
		for(int i=1; i<=nr; i++)r.push_back(Get_Int());
		for(int i=1; i<=ng; i++)g.push_back(Get_Int());
		for(int i=1; i<=nb; i++)b.push_back(Get_Int());
		sort(r.begin(),r.end());
		sort(g.begin(),g.end());
		sort(b.begin(),b.end());
		auto p1=r.begin(),p2=g.begin(),p3=b.begin();
		LL ans=Cal(*p1,*p2,*p3);
		while(!(p1==r.end()-1&&p2==g.end()-1&&p3==b.end()-1)) {
			LL sum=LLONG_MAX/3;
			auto move=&p1;
			if(p1!=r.end()-1) {
				LL tmp=Cal(*(p1+1),*p2,*p3);
				if(tmp<sum) {sum=tmp;move=&p1;}
			}
			if(p2!=g.end()-1) {
				LL tmp=Cal(*p1,*(p2+1),*p3);
				if(tmp<sum) {sum=tmp;move=&p2;}
			}
			if(p3!=b.end()-1) {
				LL tmp=Cal(*p1,*p2,*(p3+1));
				if(tmp<sum) {sum=tmp;move=&p3;}
			}
			(*move)++;
			ans=min(ans,sum);
		}
		printf("%lld\n",ans);
	}
	return 0;
}