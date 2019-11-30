#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<set>
#include<map>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1000005;

map<int,int> M;
set<int> S;
int n,tot,sum,ans=0x7fffffff/2,a[maxn];

void Add(int x) {
	if(!M.count(x)||M[x]==0)sum++;
	M[x]++;
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		S.insert(a[i]);
	}
	tot=S.size();
	int j=1;
	for(int i=1; i<=n; i++) {
		Add(a[i]);
		while(j<n&&M[a[j]]>1)M[a[j]]--,j++;
		if(sum==tot)ans=min(ans,i-j+1);
	}
	printf("%d\n",ans);
	return 0;
}