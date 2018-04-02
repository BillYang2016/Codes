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

const int maxn=100005,mod=1e9+7,inv6=166666668;

#define pii pair<int,int>
#define lowbit(x) (x&(-x))
mt19937 g(rand());

int rk[maxn<<1],step=0;

void add(LL &x,LL v) {x+=v;if(x>=mod)x-=mod;}

struct Treap {
	struct Tree {
		int l,r,size,exist,sum;
		Tree(int v=0,int s=0):l(0),r(0),size(s),exist(v),sum(s) {}
	} tree[maxn<<1];
	int size;
#define ls(x) tree[x].l
#define rs(x) tree[x].r
#define val(x) tree[x].exist
#define sum(x) tree[x].sum
#define size(x) tree[x].size
	int newnode() {tree[++size]=Tree(1,1);return size;}
	void push_up(int x) {
		size(x)=size(ls(x))+size(rs(x))+1;
		sum(x)=sum(ls(x))+val(x)+sum(rs(x));
	}
	pii split(int x,int num) {
		if(!x)return pii(0,0);
		if(num<=size(ls(x))) {
			pii lt=split(ls(x),num);
			ls(x)=lt.second;
			push_up(x);
			return pii(lt.first,x);
		} else {
			pii rt=split(rs(x),num-size(ls(x))-1);
			rs(x)=rt.first;
			push_up(x);
			return pii(x,rt.second);
		}
	}
	int merge(int a,int b) {
		if(!a||!b)return a+b;
		if(g()%(size(a)+size(b))<size(a)) {
			rs(a)=merge(rs(a),b);
			push_up(a);
			return a;
		} else {
			ls(b)=merge(a,ls(b));
			push_up(b);
			return b;
		}
	}
	int get_rank(int x,int k) {
		if(!k)return 0;
		if(k<=sum(ls(x)))return get_rank(ls(x),k);
		if(k==sum(ls(x))+val(x))return size(ls(x))+1;
		return size(ls(x))+1+get_rank(rs(x),k-sum(ls(x))-val(x));
	}
	int find(int x,int k) {
		if(k<=sum(ls(x)))return find(ls(x),k);
		if(k==sum(ls(x))+val(x))return x;
		return find(rs(x),k-sum(ls(x))-val(x));
	}
	void dfs(int x) {
		if(ls(x))dfs(ls(x));
		rk[x]=++step;
		if(rs(x))dfs(rs(x));
	}
} treap;

#undef ls
#undef rs

struct Status {
	LL s0,s1,s2,s3;
	Status(LL s0=0,LL s1=0,LL s2=0,LL s3=0):s0(s0),s1(s1),s2(s2),s3(s3) {}
	void operator += (const int v) {
		int v2=1ll*v*v%mod;
		add(s1,v),add(s3,1ll*v2*v%mod);
		if(v>0)add(s0,1),add(s2,v2);
		else add(s0,mod-1),add(s2,mod-v2);
	}
	Status operator + (const Status b) {return Status(s0+b.s0,s1+b.s1,s2+b.s2,s3+b.s3);}
	void operator += (const Status b) {*this=*this+b;}
};

struct Segment_Tree {
	struct Tree {
		int l,r;
		Status s;
	} tree[maxn*200];
	int size;
#define ls tree[index].l
#define rs tree[index].r
#define S tree[index].s
#define mid ((left+right)>>1)
	void modify(int &index,int left,int right,int Left,int Right,int val) {
		if(right<Left||left>Right)return;
		if(!index)index=++size;
		if(Left<=left&&Right>=right) {S+=val;return;}
		modify(ls,left,mid,Left,Right,val);
		modify(rs,mid+1,right,Left,Right,val);
	}
	Status query(int index,int left,int right,int tar) {
		if(!index||left>tar||right<tar)return 0;
		if(left==right)return S;
		return query(ls,left,mid,tar)+query(rs,mid+1,right,tar)+S;
	}
} st;

#undef S

set<int> S[maxn<<1];
int n,m,tot=0,a[maxn<<1],b[maxn<<1],root,rt[maxn<<1],val[maxn<<1];

void Insert(int pos,int val) {
	int pval=lower_bound(b+1,b+tot+1,val)-b;
	int pre=*prev(S[pval].lower_bound(pos)),nxt=*S[pval].lower_bound(pos);
	S[pval].insert(pos);
	for(int i=pre+1; i<=step; i+=lowbit(i))st.modify(rt[i],1,step,pos,nxt-1,val);
	for(int i=pos+1; i<=step; i+=lowbit(i))st.modify(rt[i],1,step,pos,nxt-1,-val);
}

void Erase(int pos,int val) {
	int pval=lower_bound(b+1,b+tot+1,val)-b;
	S[pval].erase(pos);
	int pre=*prev(S[pval].lower_bound(pos)),nxt=*S[pval].lower_bound(pos);
	for(int i=pre+1; i<=step; i+=lowbit(i))st.modify(rt[i],1,step,pos,nxt-1,-val);
	for(int i=pos+1; i<=step; i+=lowbit(i))st.modify(rt[i],1,step,pos,nxt-1,val);
}

struct Query {
	int opt,x,y;
	Query(int o=0,int x=0,int y=0):opt(o),x(x),y(y) {}
} q[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++) {
		b[++tot]=a[i]=Get_Int();
		root=treap.merge(root,treap.newnode());
	}
	for(int i=1; i<=m; i++) {
		int opt=Get_Int();
		if(opt==1) {
			int x=Get_Int(),y=Get_Int();
			q[i]=Query(opt,treap.find(root,x),treap.find(root,y));
		} else if(opt==2) {
			int x=Get_Int(),y=Get_Int();
			q[i]=Query(opt,treap.find(root,x),b[++tot]=y);
		} else if(opt==3) {
			int x=treap.get_rank(root,Get_Int());
			pii l=treap.split(root,x-1),r=treap.split(l.second,1);
			treap.tree[r.first].exist--,treap.tree[r.first].sum--;
			root=treap.merge(l.first,treap.merge(r.first,r.second));
			q[i]=Query(opt,r.first,0);
		} else if(opt==4) {
			int x=treap.get_rank(root,Get_Int()),y=Get_Int();
			pii t=treap.split(root,x);
			root=treap.merge(treap.merge(t.first,treap.newnode()),t.second);
			q[i]=Query(opt,treap.size,b[++tot]=y);
		} else {
			int x=Get_Int(),y=Get_Int();
			q[i]=Query(opt,treap.find(root,x),treap.find(root,y));
		}
	}
	treap.dfs(root);
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1; i<=tot; i++)S[i].insert(0),S[i].insert(step+1);
	for(int i=1; i<=n; i++) {
		Insert(rk[i],a[i]);
		val[rk[i]]=a[i];
	}
	for(int j=1; j<=m; j++) {
		int opt=q[j].opt,x=q[j].x,y=q[j].y;
		if(opt==1) {
			x=rk[x],y=rk[y];
			Status s;
			for(int i=x; i>0; i-=lowbit(i))s+=st.query(rt[i],1,step,y);
			s.s1%=mod,s.s2%=mod,s.s3%=mod;
			printf("%lld\n",((s.s1*s.s1%mod*s.s1%mod-3*s.s2*s.s1%mod+2*s.s3%mod)%mod*inv6%mod+mod)%mod);
		} else if(opt==2) {
			Erase(rk[x],val[rk[x]]);
			val[rk[x]]=y;
			Insert(rk[x],val[rk[x]]);
		} else if(opt==3) {
			Erase(rk[x],val[rk[x]]);
			val[rk[x]]=0;
		} else if(opt==4) {
			val[rk[x]]=y;
			Insert(rk[x],val[rk[x]]);
		} else {
			x=rk[x],y=rk[y];
			Status s;
			for(int i=x; i>0; i-=lowbit(i))s+=st.query(rt[i],1,step,y);
			printf("%lld\n",s.s0%mod);
		}
	}
	return 0;
}