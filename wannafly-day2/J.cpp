#include<cstdio>
using namespace std;
const int N=3010;
int g[N<<1],nxt[N<<1],v[N<<1],num;
int q[N<<1],t;
bool vis[N<<1];
int CNT;
int n,m;
void add(int x,int y){
	nxt[++num]=g[x];
	v[num]=y;
	g[x]=num;
}
bool dfs(int x){
	CNT++;
	if(vis[x>n?x-n:x+n])return 0;
	if(vis[x])return 1;
	vis[q[++t]=x]=1;
	for(int i=g[x];i;i=nxt[i])if(!dfs(v[i]))return 0;
	return 1;
}
bool solve(){
	for(int i=1;i<=n;i++)if(!vis[i]&&!vis[i+n]){
		t=0;
		if(!dfs(i)){
			while(t)vis[q[t--]]=0;
			if(!dfs(i+n))return 0;
		}
	}
	return 1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		if(x<0)x=n-x;if(y<0)y=n-y;
		add(x>n?x-n:x+n,y);add(y>n?y-n:y+n,x);
	}
	solve();
	return 0;
}