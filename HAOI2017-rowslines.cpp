#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1005,K=1000;

#define bit bitset<K+1>

bit get_bit() {
	static char s[K+1];
	bit ans;
	scanf("%s",s);
	int n=strlen(s);
	for(int i=0; i<n; i++)ans[i]=s[n-1-i]-'0';
	return ans;
}

void put_bit(const bit &b) {
	bool fir=0;
	for(int i=K; i>=0; i--) {
		if(b[i])fir=1;
		if(fir)printf("%d",b[i]);
	}
	putchar('\n');
}

struct Linear_Bases {
	bit b[K+1];
	void add(bit num) {
		for(int j=K; j>=0; j--)if(num[j]) {
			if(b[j].any()) {num^=b[j];continue;}
			b[j]=num;
			break;
		}
	}
	bit cal() {
		bit ans=0;
		for(int i=K; i>=0; i--)if(!ans[i])ans^=b[i];
		return ans;
	}
};

bit Ans[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right;
		vector<bit> p;
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index].left=Left,tree[index].right=Right;
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
	}
	void insert(int index,int Left,int Right,const bit &b) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {tree[index].p.push_back(b);return;}
		insert(ls,Left,Right,b);
		insert(rs,Left,Right,b);
	}
	void dfs(int index,Linear_Bases lb) {
		for(bit &x:tree[index].p)lb.add(x);
		if(tree[index].left==tree[index].right)Ans[tree[index].left]=lb.cal();
		else dfs(ls,lb),dfs(rs,lb);
	}
} st;

Linear_Bases lb;
bit sum[maxn],val[maxn];
int n,m,q,cnt=0,father[maxn],last[maxn];
struct Edge {
	int from,to;
	Edge(int x=0,int y=0):from(x),to(y) {}
} edges[maxn];

int Get_Father(int x) {
	if(father[x]==x)return x;
	int fa=Get_Father(father[x]);
	sum[x]^=sum[father[x]];
	return father[x]=fa;
}

void AddEdge(int x,int y,const bit &b) {
	int fx=Get_Father(x),fy=Get_Father(y);
	if(fx==fy) {lb.add(sum[x]^sum[y]^b);return;}
	father[fx]=fy;
	sum[fx]=sum[x]^sum[y]^b;
}

void NewEdge(int t,int x,int y,const bit &b) {
	edges[++cnt]=Edge(x,y);
	val[cnt]=sum[x]^sum[y]^b;
	last[cnt]=t;
}

void DelEdge(int t,int id) {
	st.insert(1,last[id],t-1,val[id]);
	last[id]=0;
}

void ModEdge(int t,int id,const bit &b) {
	st.insert(1,last[id],t-1,val[id]);
	val[id]=sum[edges[id].from]^sum[edges[id].to]^b;
	last[id]=t;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++)father[i]=i;
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y,get_bit());
	}
	if(q)st.build(1,1,q);
	for(int i=1; i<=n; i++)Get_Father(i);
	for(int i=1; i<=q; i++) {
		char opt=' ';
		while(!isalpha(opt))opt=getchar();
		if(opt=='A') {
			int x=Get_Int(),y=Get_Int();
			NewEdge(i,x,y,get_bit());
		} else {
			opt=' ';
			while(!isalpha(opt))opt=getchar();
			if(opt=='a')DelEdge(i,Get_Int());
			else {
				int x=Get_Int();
				ModEdge(i,x,get_bit());
			}
		}
	}
	for(int i=1; i<=cnt; i++)if(last[i])st.insert(1,last[i],q,val[i]);
	put_bit(lb.cal());
	st.dfs(1,lb);
	for(int i=1; i<=q; i++)put_bit(Ans[i]);
	return 0;
}