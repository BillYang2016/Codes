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

#define mp make_pair
#define pii pair<int,int>

int inv[1000005];

int main() {
	int t=Get_Int();
	vector<pii> v;
	while(t--) {
		int p=Get_Int();
		v.clear();
		int Min=INT_MAX;
		inv[1]=1;
		for(int i=2; i<p&&Min>=i; i++) {
			inv[i]=1ll*(p-p/i)*inv[p%i]%p;
			int x=inv[i];
			Min=min(Min,x);
			if(Min==x)v.push_back(mp(i,x));
		}
		if(v.empty())puts("0");
		else if(v.back().first==v.back().second) {
			int n=v.size();
			printf("%d\n",n*2-1);
			for(int i=0; i<n; i++)printf("%d %d\n",v[i].first,v[i].second);
			for(int i=n-2; i>=0; i--)printf("%d %d\n",v[i].second,v[i].first);
		} else {
			int n=v.size()-1;
			printf("%d\n",n*2-(v[n].first==v[n].second));
			for(int i=0; i<n; i++)printf("%d %d\n",v[i].first,v[i].second);
			if(v[n].first==v[n].second)n--;
			for(int i=n-1; i>=0; i--)printf("%d %d\n",v[i].second,v[i].first);
		}
	}
	return 0;
}