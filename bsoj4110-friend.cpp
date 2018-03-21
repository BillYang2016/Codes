#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,K=2;

int D;

struct Point {
	int d[K],Min[K],Max[K],id;
	int ls,rs,val;
	int& operator [] (int x) {return d[x];}
	bool operator < (const Point& b) const {return d[D]<b.d[D];}
} p[maxn];

int ans,ansid;

struct KD_Tree {
#define lson p[index].ls
#define rson p[index].rs
	void update(int index) {
		for(int i=0; i<K; i++) {
			p[index].Max[i]=p[index].Min[i]=p[index][i];
			if(lson) {
				p[index].Min[i]=min(p[index].Min[i],p[lson].Min[i]);
				p[index].Max[i]=max(p[index].Max[i],p[lson].Max[i]);
			}
			if(rson) {
				p[index].Min[i]=min(p[index].Min[i],p[rson].Min[i]);
				p[index].Max[i]=max(p[index].Max[i],p[rson].Max[i]);
			}
		}
	}
	int build(int Left,int Right,int now) {
		int mid=(Left+Right)>>1,root=mid;
		D=now;
		nth_element(p+Left,p+mid,p+Right+1);
		if(Left<mid)p[root].ls=build(Left,mid-1,(now+1)%K);
		if(Right>mid)p[root].rs=build(mid+1,Right,(now+1)%K);
		update(root);
		return root;
	}
	LL dist(Point a,Point b) {
		LL ans=0;
		for(int i=0; i<K; i++)ans+=abs(a[i]-b[i]);
		return ans;
	}
	int get_min(int index,Point P) {
		if(!index)return INT_MAX/2;
		int ans=0;
		for(int i=0; i<K; i++) {
			if(p[index].Min[i]-P[i]>0)ans+=abs(p[index].Min[i]-P[i]);
			if(P[i]-p[index].Max[i]>0)ans+=abs(P[i]-p[index].Max[i]);
		}
		return ans;
	}
	void find_min(int index,Point P,int now) {
		if(!index)return;
		if(p[index].id!=P.id) {
			LL Dist=dist(p[index],P);
			if(Dist<ans||(Dist==ans&&p[index].id<ansid))ans=Dist,ansid=p[index].id;
		}
		LL ldist=get_min(lson,P),rdist=get_min(rson,P);
		if(ldist<=rdist) {
			if(ldist<=ans)find_min(lson,P,(now+1)%K);
			if(rdist<=ans&&P[now]+ans>=p[index][now])find_min(rson,P,(now+1)%K);
		} else {
			if(rdist<=ans)find_min(rson,P,(now+1)%K);
			if(ldist<=ans&&P[now]-ans<=p[index][now])find_min(lson,P,(now+1)%K);
		}
	}
} kdtree;

int n,f[maxn],g[maxn],First=0,Second=0,Max=0;
bool vst[maxn];
vector<int> edges[maxn];

void Dfs(int Now) {
	vst[Now]=1;
	for(int Next:edges[Now]) {
		if(vst[Next])continue;
		Dfs(Next);
		if(f[Next]+1>f[Now]) {
			g[Now]=f[Now];
			f[Now]=f[Next]+1;
		} else g[Now]=max(g[Now],f[Next]+1);
	}
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		p[i][0]=Get_Int();
		p[i][1]=Get_Int();
		p[i].id=i;
	}
	int root=kdtree.build(1,n,0);
	for(int i=1; i<=n; i++) {
		ans=ansid=INT_MAX;
		kdtree.find_min(root,p[i],0);
		edges[p[i].id].push_back(ansid);
		edges[ansid].push_back(p[i].id);
	}
	for(int i=1; i<=n; i++) {
		if(vst[i])continue;
		Dfs(i);
		int now=(f[i]+g[i]+1)/2;
		if(now>First) {
			Second=First;
			First=now;
		} else Second=max(Second,now);
		Max=max(Max,f[i]+g[i]);
	}
	printf("%d\n",max(Max,First+Second+2));
	return 0;
}