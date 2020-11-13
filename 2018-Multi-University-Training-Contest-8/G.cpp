#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;

struct Edge {
	int from,to;
	bool exist;
	Edge(int x=0,int y=0,bool v=0):from(x),to(y),exist(v) {}
} edge[maxn];

int n,father[maxn],sum_n=0,sum_m=0,tmp_ans=0,tmp_num=0,exists=0;
bool vst[maxn],vst2[maxn],incircle[maxn];
vector<int> G[maxn];
vector<Edge> edges;
stack<Edge> S;

void Clear() {
	for(int i=1; i<=n; i++) {
		father[i]=i;
		G[i].clear();
		vst[i]=vst2[i]=incircle[i]=0;
	}
	edges.clear();
}

void AddEdge(int x,int y,bool v) {
	edges.push_back(Edge(x,y,v));
	G[x].push_back(edges.size()-1);
}

int get_father(int x) {return father[x]==x?x:father[x]=get_father(father[x]);}

void Merge(int x,int y) {
	int fx=get_father(x),fy=get_father(y);
	if(fx!=fy)father[fx]=fy;
}

void Dfs(int Now) {
	sum_n++;
	sum_m+=G[Now].size();
	vst[Now]=1;
	for(int &id:G[Now]) {
		Edge &e=edges[id];
		if(!vst[e.to])Dfs(e.to);
	}
}

void Dfs1(int Now,int fa) {
	for(int &id:G[Now]) {
		Edge &e=edges[id];
		int Next=e.to;
		if((id^1)==fa)continue;
		if(incircle[Next])continue;
		tmp_ans+=e.exist;
		Dfs1(Next,id);
	}
}

void Dfs2(int Now,int fa,int nowans) {
	if(nowans==tmp_ans)tmp_num++;
	else if(nowans<tmp_ans) {
		tmp_ans=nowans;
		tmp_num=1;
	}
	for(int &id:G[Now]) {
		Edge &e=edges[id];
		int Next=e.to;
		if((id^1)==fa)continue;
		if(e.exist)Dfs2(Next,id,nowans-1);
		else Dfs2(Next,id,nowans+1);
	}
}

vector<Edge> circle;

void find_circle(int Now,int fa) {
	vst2[Now]=1;
	for(int &id:G[Now]) {
		Edge &e=edges[id];
		int Next=e.to;
		if((id^1)==fa)continue;
		S.push(e);
		if(vst2[Next]) {
			while(!S.empty()) {
				Edge &e2=S.top();
				S.pop();
				circle.push_back(e2);
				incircle[e2.to]=1;
				exists+=e2.exist;
				if(e2.from==Next)break;
			}
			break;
		}
		find_circle(Next,id);
		if(!circle.empty())break;
		S.pop();
	}
}

typedef long long LL;

const LL mod=998244353;

int main() {
	int t=Get_Int();
	while(t--) {
		int m=Get_Int();
		n=0;
		for(int i=1; i<=m; i++) {
			int x=Get_Int(),y=Get_Int();
			edge[i].from=x;
			edge[i].to=y;
			n=max(n,max(x,y));
		}
		Clear();
		for(int i=1; i<=m; i++) {
			int x=edge[i].from,y=edge[i].to;
			AddEdge(x,y,1);
			AddEdge(y,x,0);
			Merge(x,y);
		}
		int ans=0;
		LL ans_num=1;
		for(int i=1; i<=n; i++)if(father[i]==i) {
			sum_n=0;
			sum_m=0;
			Dfs(i);
			sum_m/=2;
			if(sum_m>sum_n) { //无解
				ans=-1;
				ans_num=-1;
				break;
			} else if(sum_m==sum_n-1) { //树
				tmp_ans=0;
				Dfs1(i,-1);
				tmp_num=0;
				Dfs2(i,-1,tmp_ans);
				ans+=tmp_ans;
				ans_num=ans_num*tmp_num%mod;
			} else { //基环树
				circle.clear();
				exists=0;
				while(!S.empty())S.pop();
				find_circle(i,-1);
				tmp_ans=0;
				for(Edge &e:circle)Dfs1(e.from,-1);
				int size=circle.size();
				if(size==exists*2) {
					tmp_ans+=exists;
					ans_num=ans_num*2%mod;
				} else tmp_ans+=min(exists,size-exists);
				ans+=tmp_ans;
			}
		}
		printf("%d %lld\n",ans,ans_num);
	}
	return 0;
}