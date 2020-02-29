#pragma GCC optimize(3)
#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

#define mp make_pair
typedef pair<int,int> pii;

const int maxn=100005,K=18;

int n,m,step,Dfn[maxn],Depth[maxn],p[maxn][K],List[maxn<<1][K],Log[maxn<<1];
vector<int> edges[maxn];

void Dfs(int Now,int fa) {
	Dfn[Now]=++step;
	List[step][0]=Now;
	Depth[Now]=Depth[fa]+1;
	p[Now][0]=fa;
	for(int i=1; i<K; i++)p[Now][i]=p[p[Now][i-1]][i-1];
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs(Next,Now);
		List[++step][0]=Now;
	}
}

void Sparse_Table() {
	for(int i=2; i<=step; i++)Log[i]=Log[i>>1]+1;
	for(int j=1; (1<<j)<=step; j++)
		for(int i=1; i+(1<<j)-1<=step; i++) {
			int l=List[i][j-1],r=List[i+(1<<(j-1))][j-1];
			List[i][j]=Depth[l]<Depth[r]?l:r;
		}
}

int LCA(int a,int b) {
	if(Dfn[a]>Dfn[b])swap(a,b);
	int k=Log[Dfn[b]-Dfn[a]+1];
	int l=List[Dfn[a]][k],r=List[Dfn[b]-(1<<k)+1][k];
	return Depth[l]<Depth[r]?l:r;
}

int Dist(int x,int y) {return Depth[x]+Depth[y]-2*Depth[LCA(x,y)];}

struct Sum {
	vector<int> a;
	int n;
	Sum() {init(0);}
	void init(int n) {
		this->n=n;
		a.resize(n+1);
		a.clear();
	}
	void modify(int x,int v) {
		if(x<0||x>n)return;
		a[x]+=v;
	}
	void build() {
		for(int i=1; i<=n; i++)a[i]+=a[i-1];
	}
	int query(int x) {
		if(x<0)return 0;
		return a[min(x,n)];
	}
} f[maxn],fa_f[maxn];

namespace Tree {
	int Size[maxn],Maxson[maxn],Mind[maxn],Min,Core;
	int DT_father[maxn],DT_Depth[maxn];
	bool vst[maxn];

	void Get_Size(int Now,int fa) {
		Size[Now]=1;
		Maxson[Now]=0;
		for(int Next:edges[Now]) {
			if(Next==fa||vst[Next])continue;
			Get_Size(Next,Now);
			Size[Now]+=Size[Next];
			Maxson[Now]=max(Maxson[Now],Size[Next]);
		}
	}

	void Get_Core(int Now,int fa,int num) {
		Maxson[Now]=max(Maxson[Now],Size[num]-Size[Now]);
		if(Maxson[Now]<Min) {
			Min=Maxson[Now];
			Core=Now;
		}
		for(int Next:edges[Now]) {
			if(Next==fa||vst[Next])continue;
			Get_Core(Next,Now,num);
		}
	}

	void Cal_Min(int Now,int fa) { //点分树当前根的父亲到子树的最近距离
		Mind[Core]=min(Mind[Core],Dist(DT_father[Core],Now));
		for(int Next:edges[Now]) {
			if(Next==fa||vst[Next])continue;
			Cal_Min(Next,Now);
		}
	}

	void Cal_Sum(int Now,int fa) {
		f[Core].modify(Dist(Now,Core),1);
		if(DT_father[Core])fa_f[Core].modify(Dist(Now,DT_father[Core])-Mind[Core],1);
		for(int Next:edges[Now]) {
			if(Next==fa||vst[Next])continue;
			Cal_Sum(Next,Now);
		}
	}

	void Build(int Now,int fa) {
		Min=n;
		Get_Size(Now,0);
		Get_Core(Now,0,Now);
		int tot=Size[Now];
		Now=Core;
		vst[Now]=1;
		DT_father[Now]=fa;
		DT_Depth[Now]=DT_Depth[fa]+1;
		f[Now].init(tot);
		if(fa) {
			fa_f[Now].init(tot);
			Mind[Now]=Dist(Now,fa);
			Cal_Min(Now,0);
		}
		Cal_Sum(Now,0);
		f[Now].build();
		if(fa)fa_f[Now].build();
		for(int Next:edges[Now]) {
			if(vst[Next])continue;
			Build(Next,Now);
		}
	}
}

using namespace Tree;

int query(int x,int y,int v) {
	int ans=f[x].query(v-Dist(x,y)),fd=Dist(DT_father[x],y);
	if(DT_father[x])ans+=query(DT_father[x],y,v)-fa_f[x].query(v-fd-Mind[x]);
	return ans;
}

int query(int x,int a,int b,int v) {
	int ans=f[x].query(v-min(Dist(x,a),Dist(x,b))),fd=min(Dist(DT_father[x],a),Dist(DT_father[x],b));
	if(DT_father[x])ans+=query(DT_father[x],a,b,v)-fa_f[x].query(v-fd-Mind[x]);
	return ans;
}

int kth_father(int x,int k) {
	for(int i=K-1; i>=0; i--)if(k>=(1<<i))k-=(1<<i),x=p[x][i];
	return x;
}

int mid(int x,int y) {
	int dist=Dist(x,y);
	if(Depth[x]>Depth[y])return kth_father(x,dist/2);
	else return kth_father(y,dist/2);
}

pii midp(int x,int y) {
	int lca=LCA(x,y),dist=Dist(x,y);
	if(Depth[x]-Depth[lca]>=dist/2+1) {
		int f=kth_father(x,dist/2);
		return mp(f,p[f][0]);
	} else {
		int f=kth_father(y,dist/2);
		return mp(f,p[f][0]);
	}
}

void AddEdge(int x,int y) {edges[x].push_back(y);}

void Clear() {
	step=0;
	for(int i=1; i<=n; i++)edges[i].clear(),vst[i]=0;
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		Clear();
		for(int i=1; i<n; i++) {
			int x=Get_Int(),y=Get_Int();
			AddEdge(x,y);
			AddEdge(y,x);
		}
		Dfs(1,0);
		Sparse_Table();
		Build(1,0);
		int ans=0;
		for(int i=1; i<=m; i++) {
			int x=(Get_Int()+ans)%n+1,y=(Get_Int()+ans)%n+1,v=(Get_Int()+ans)%n;
			// int x=Get_Int(),y=Get_Int(),v=Get_Int();
			int dist=Dist(x,y);
			query(7,7,7);
			ans=query(x,x,v)+query(y,y,v);
			if(dist<=2*v) {
				if(dist&1) {
					pii tmp=midp(x,y);
					ans-=query(DT_Depth[tmp.first]>DT_Depth[tmp.second]?tmp.first:tmp.second,tmp.first,tmp.second,v-dist/2-1);
				} else {
					int tmp=mid(x,y);
					ans-=query(tmp,tmp,v-dist/2);
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}