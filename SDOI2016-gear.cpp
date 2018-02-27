#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>

using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

int Get_Father(int x) {
	if(father[x]==x)return x;
	int fx=Get_Father(father[x]);
	sum[x]*=sum[father[x]];
	return father[x]=fx;
}

int main() {
	T=Get_Int();
	for(int t=1; t<=T; t++) {
		printf("Case #%d: ",t);
		n=Get_Int();
		m=Get_Int();
		for(int i=1; i<=n; i++) {
			father[i]=i;
			sum[i]=1;
		}
		bool bj=1;
		for(int i=1; i<=m; i++) {
			int u=Get_Int(),v=Get_Int();
			double x=Get_Int(),y=Get_Int();
			int fu=Get_Father(u),fv=Get_Father(v);
			if(fu!=fv) {
				father[fu]=fv;
				sum[fu]*=sum[u]/sum[v]*y/x;
			} else if(dcmp(sum[u]/sum[v]-x/y))bj=0;
		}
		puts(bj?"Yes":"No");
	}
	return 0;
}