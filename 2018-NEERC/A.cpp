#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

#define node pair<int,int>
#define pos second
#define val first

const int maxn=200005;

int n,m,d,ans[maxn],cnt=0;

int main() {
	n=Get_Int();
	m=Get_Int();
	d=Get_Int();
	set<node> S;
	for(int i=1; i<=n; i++)S.insert(node(Get_Int(),i));
	while(!S.empty()) {
		int Now=S.begin()->second,nowv=S.begin()->first;
		ans[Now]=++cnt;
		S.erase(S.begin());
		while(true) {
			auto it=S.lower_bound(node(nowv+d+1,0));
			if(it==S.end())break;
			Now=it->second;
			nowv=it->first;
			ans[Now]=cnt;
			S.erase(it);
		}
	}
	printf("%d\n",cnt);
	for(int i=1; i<=n; i++)printf("%d ",ans[i]);
	return 0;
}