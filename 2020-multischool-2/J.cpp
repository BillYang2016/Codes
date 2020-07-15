#include<bits/stdc++.h>

using namespace std;

const int maxn=100005;

int n,k,cnt=0,a[maxn],pos[maxn],ans[maxn],ori[maxn],pre[maxn];
bool vst[maxn];
vector<int> vec[maxn];

void Dfs(int x) {
	vec[cnt].push_back(x);
	vst[x]=1;
	if(!vst[a[x]])Dfs(a[x]);
}

int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++) {
		scanf("%d",&a[i]);
		pos[a[i]]=i;
	}
	for(int i=1; i<=n; i++)if(!vst[i]) {
		cnt++;
		Dfs(i);
		int size=vec[cnt].size();
		int x=k%size;
		for(int j=0; j<size; j++)ori[j*x%size]=j;
		for(int j=0; j<size; j++)ans[vec[cnt][ori[j]]]=vec[cnt][ori[(j+1)%size]];
	}
	for(int i=1; i<=n; i++)printf("%d ",ans[i]);
	return 0;
}