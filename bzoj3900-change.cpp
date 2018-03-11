#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=25;

int n,c,a[maxn],b[maxn],f[1<<16];

int main() {
	n=Get_Int();
	c=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		b[i]=Get_Int();
	}
	for(int S=0; S<(1<<n); S++) {
		vector<int> vec;
		bool bj=0;
		for(int i=1; i<=n; i++)
			if(S&(1<<(i-1))) {
				if(abs(a[i]-b[i])>c)bj=1;
				vec.push_back(a[i]),vec.push_back(b[i]);
			}
		if(!bj) {f[S]=0;continue;}
		sort(vec.begin(),vec.end());
		bj=1;
		for(int i=1; i<vec.size(); i+=2)if(vec[i]-vec[i-1]>c) {bj=0;break;}
		if(bj)f[S]=vec.size()/2-1;
		else f[S]=INT_MAX/2;
	}
	for(int S=0; S<(1<<n); S++)
		for(int T=S; T; T=(T-1)&S)f[S]=min(f[S],f[T]+f[S^T]);
	if(f[(1<<n)-1]>=INT_MAX/2)puts("-1");
	else printf("%d\n",f[(1<<n)-1]);
	return 0;
}