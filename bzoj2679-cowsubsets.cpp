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

const int maxn=60005;

struct Node {
	int sum,S;
	Node(int a=0,int b=0):sum(a),S(b) {}
	bool operator < (const Node& b) const {
		return sum<b.sum;
	}
};

vector<int> f[maxn];
vector<Node> g;
int n,mid;

void Dfsl(int Now,int sum,int S) {
	if(Now>mid) {
		f[S].push_back(sum);
		return;
	}
	Dfsl(Now+1,sum,S);
	Dfsl(Now+1,sum-a[Now],S|(1<<(Now-1)));
	Dfsl(Now+1,sum+a[Now],S|(1<<(Now-1)));
}

void Dfsr(int Now,int sum,int S) {
	if(Now>n) {
		g.push_back(Node(sum,S));
		return;
	}
	Dfsr(Now+1,sum,S);
	Dfsr(Now+1,sum-a[Now],S|(1<<(Now-1)));
	Dfsr(Now+1,sum+a[Now],S|(1<<(Now-1)));
}

int main() {
	n=Get_Int();
	mid=n>>1;
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	Dfsl(1,0,0);
	Dfsr(mid+1,0,0);
	sort(g.begin(),g.end());
	for(int S=0; S<(1<<(mid-1)); i++) {
		sort(f[S].begin(),f[S].end());
		auto it=f[S].begin();
		for(auto x:g) {
			while(it!=f[S].end()&&*it<x.sum)it++;
			if(it==f[S].end())break;
			if(*it==x.sum)vst[S|x.S]=1;
		}
	}
	for(int i=1; i<(1<<(n-1)); i++)ans+=vst[i];
	printf("%d\n",ans);
	return 0;
} 
