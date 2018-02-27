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

const int maxn=30005,maxm=128;
const int mod=10007,inv2=5004;

struct FastWalshTransform {
	int n;
	void init(int n) {
		this->n=n;
	}
	void transform(int *a,int mul) {
		for(int len=2; len<=n; len<<=1) {
			int mid=len>>1;
			for(int *p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					LL x=p[i],y=p[mid+i];
					p[i]=(x+y)*mul%mod;
					p[mid+i]=(x-y+mod)*mul%mod;
				}
		}
	}
	void fwt(int *a) {
		transform(a,1);
	}
	void ufwt(int *a) {
		transform(a,inv2);
	}
} wtf;

int n,m,pos[maxn],root[maxn],val[maxn],father[maxn],Depth[maxn],Size[maxn],Son[maxn],Top[maxn];
int e[maxn][maxm],g[maxn][maxm],ans[maxm];
bool leaf[maxn];
vector<int> edges[maxn],chain[maxn],tops;
int inv[mod+5];

struct Integer {
	int num,cnt;
	Integer(int v=0) {
		if(v)num=v,cnt=0;
		else num=cnt=1;
	}
	Integer operator * (int v) {
		Integer a=*this;
		if(!v)a.cnt++;
		else a.num=a.num*v%mod;
		return a;
	}
	Integer operator / (int v) {
		Integer a=*this;
		if(!v)a.cnt--;
		else a.num=a.num*inv[v]%mod;
		return a;
	}
	void operator *=(int v) {*this=*this*v;}
	void operator /=(int v) {*this=*this/v;}
	int val() {return cnt?0:num;}
} f[maxn][maxm];

void Dfs1(int Now,int fa,int depth) {
	father[Now]=fa;
	Depth[Now]=depth;
	Size[Now]=1;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs1(Next,Now,depth+1);
		Size[Now]+=Size[Next];
		if(Size[Son[Now]]<Size[Next])Son[Now]=Next;
	}
	if(edges[Now].size()==1)leaf[Now]=1;
}

void Dfs2(int Now,int top) {
	Top[Now]=top;
	chain[top].push_back(Now);
	if(Now==top)tops.push_back(Now);
	if(Son[Now])Dfs2(Son[Now],top);
	for(int Next:edges[Now]) {
		if(Next==father[Now]||Next==Son[Now])continue;
		Dfs2(Next,Next);
	}
}

struct Tag {
	int a,b,c,d;
	Tag(int a=1,int b=0,int c=0,int d=0):a(a),b(b),c(c),d(d) {}
	int f() {return a+c;}
	int g() {return b+d;}
	Tag operator + (const Tag &y) const {
		return Tag(a*y.a,b+a*y.b,y.a*c+y.b,y.b*c+d+y.d);
	}
};

struct Segment_Tree {
	struct Tree {
		int left,right;
		int lson,rson;
		Tag tag[maxm];
		Tree(int l=0,int r=0):left(l),right(r),lson(0),rson(0) {}
	} tree[maxn<<1];
	int size;
#define ls tree[index].lson
#define rs tree[index].rson
#define mid ((left+right)>>1)
	void build(int &index,int left,int right,int top) {
		if(!index)index=++size;
		tree[index]=Tree(left,right);
		if(left==right) {
			int x=chain[top][left-1];
			for(int i=0; i<m; i++) {
				int tmp=f[x][i].val()*e[val[x]][i];
				tree[index].tag[i]=Tag(tmp,tmp,leaf[x]?0:tmp,(leaf[x]?0:tmp)+g[x][i]);
			}
			pos[chain[top][left-1]]=left;
			return;
		}
		build(ls,left,mid,top);
		build(rs,mid+1,right,top);
		push_up(index);
	}
	void push_up(int index) {
		for(int i=0; i<m; i++)tree[index].tag[i]=tree[rs].tag[i]+tree[ls].tag[i];
	}
	void modify(int index,int target,int j,Tag v) {
		if(target<tree[index].left||target>tree[index].right)return;
		if(tree[index].left==tree[index].right) {
			tree[index].tag[j]=v;
			return;
		}
		modify(ls,target,j,v);
		modify(rs,target,j,v);
		push_up(index);
	}
	Tag query(int index,int Left,int Right,int j) {
		if(Right<tree[index].left||Left>tree[index].right)return Tag();
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].tag[j];
		return query(rs,Left,Right,j)+query(ls,Left,Right,j);
	}
} st;

bool cmp(int x,int y) {
	return Depth[x]>Depth[y];
}

void Modify(int x,int v) {
	val[x]=v;
	for(int t; father[t=Top[x]]; x=father[t],t=Top[x])
		for(int i=0; i<m; i++) {
			LL lastf=st.tree[root[t]].tag[i].f(),lastg=st.tree[root[t]].tag[i].g();
			int tmp=f[x][i].val()*e[val[x]][i];
			st.modify(root[t],pos[x],i,Tag(tmp,tmp,leaf[x]?0:tmp,(leaf[x]?0:tmp)+g[x][i]));
			f[father[t]][i]/=lastf+e[0][i],f[father[t]][i]*=st.tree[root[t]].tag[i].f()+e[0][i];
			g[father[t]][i]=(g[father[t]][i]-lastg+mod)%mod,g[father[t]][i]=(g[father[t]][i]+st.tree[root[t]].tag[i].g())%mod;
		}
	for(int i=0; i<m; i++) {
		int tmp=f[x][i].val()*e[val[x]][i];
		st.modify(root[Top[x]],pos[x],i,Tag(tmp,tmp,leaf[x]?0:tmp,(leaf[x]?0:tmp)+g[x][i]));
	}
}

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

int main() {
	n=Get_Int();
	m=Get_Int();
	wtf.init(m);
	for(int i=0; i<m; i++) {
		e[i][i]=1;
		wtf.fwt(e[i]);
	}
	inv[1]=1;
	for(int i=2; i<mod; i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1; i<=n; i++) {
		val[i]=Get_Int();
		for(int j=0; j<m; j++)f[i][j]=Integer(1);
	}
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	Dfs1(1,0,1);
	Dfs2(1,1);
	sort(tops.begin(),tops.end(),cmp);
	for(int x:tops) {
		st.build(root[x],1,chain[x].size(),x);
		if(father[x])
			for(int i=0; i<m; i++) {
				f[father[x]][i]*=st.tree[root[x]].tag[i].f()+e[0][i];
				g[father[x]][i]=(g[father[x]][i]+st.tree[root[x]].tag[i].g())%mod;
			}
	}
	int q=Get_Int();
	while(q--) {
		char opt=' ';
		while(!isalpha(opt))opt=getchar();
		int x=Get_Int();
		if(opt=='C')Modify(x,Get_Int());
		else if(opt=='Q') {
			for(int i=0; i<m; i++)ans[i]=st.tree[root[1]].tag[i].g();
			wtf.ufwt(ans);
			printf("%d\n",ans[x]);
		}
	}
	return 0;
}