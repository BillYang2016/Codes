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

typedef long long LL;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

int n,a[(1<<12)+5];
LL ans=0,fac[13];

int check(int x,int y) {
	for(int i=x+1; i<=y; i++)
		if(a[i]!=a[i-1]+1)return 0;
	return 1;
}

void Swap(int x,int y,int len) {
	for(int i=0; i<len; i++)swap(a[x+i],a[y+i]);
}

void Dfs(int depth,int cnt) {
	if(depth==n) {
		ans+=fac[cnt];
		return;
	}
	vector<int> st;
	for(int i=1; i<=(1<<n); i+=1<<(depth+1))
		if(!check(i,i+(1<<(depth+1))-1)) {
			if(st.size()>2)return;
			st.push_back(i);
			st.push_back(i+(1<<depth));
		}
	if(st.empty())Dfs(depth+1,cnt);
	if(st.size()==2) {
		if(a[st[1]]+(1<<depth)==a[st[0]]) {
			Swap(st[0],st[1],1<<depth);
			Dfs(depth+1,cnt+1);
			Swap(st[0],st[1],1<<depth);
		}
	}
	if(st.size()==4) {
		if(a[st[2]]+(1<<depth)==a[st[1]]&&a[st[0]]+(1<<depth)==a[st[3]]) {
			Swap(st[1],st[3],1<<depth);
			Dfs(depth+1,cnt+1);
			Swap(st[1],st[3],1<<depth);
			Swap(st[0],st[2],1<<depth);
			Dfs(depth+1,cnt+1);
			Swap(st[0],st[2],1<<depth);
		}
		if(a[st[2]]+(1<<depth)==a[st[0]]&&a[st[3]]+(1<<depth)==a[st[1]]) {
			Swap(st[0],st[3],1<<depth);
			Dfs(depth+1,cnt+1);
			Swap(st[0],st[3],1<<depth);
		}
		if(a[st[1]]+(1<<depth)==a[st[3]]&&a[st[0]]+(1<<depth)==a[st[2]]) {
			Swap(st[1],st[2],1<<depth);
			Dfs(depth+1,cnt+1);
			Swap(st[1],st[2],1<<depth);
		}
	}
}

int main() {
	n=Get_Int();
	fac[0]=1;
	for(int i=1; i<=n; i++)fac[i]=fac[i-1]*i;
	for(int i=1; i<=(1<<n); i++)a[i]=Get_Int();
	Dfs(0,0);
	printf("%lld\n",ans);
	return 0;
}