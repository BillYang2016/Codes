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

#define double long double

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

const int maxn=200005,maxq=5000005;

mt19937 g(rand());

struct Tree {
	int child[2];
	int val,d;
	double num;
	vector<int> vec;
};

int qlen,qs[maxq],a[maxn];

struct Treap {
	Tree tree[maxn];
	int size,root;
#define d(x) tree[x].d
#define ls(x) tree[x].child[0]
#define rs(x) tree[x].child[1]
#define val(x) tree[x].val
#define num(x) tree[x].num
#define mid (l+r)/2
	int newnode(int val) {
		int now=++size;
		val(now)=val;
		d(now)=g()%maxn;
		num(now)=ls(now)=rs(now)=0;
		return now;
	}
	void rebuild(int &index,double l,double r) { //重新计算映射
		if(!index)return;
		num(index)=mid;
		rebuild(ls(index),l,mid);
		rebuild(rs(index),mid,r);
	}
	void push_up(int index) { //vector归并
		int ls=ls(index),rs=rs(index);
		tree[index].vec.clear(),tree[index].vec.resize(tree[ls].vec.size()+tree[rs].vec.size());
		merge(tree[ls].vec.begin(),tree[ls].vec.end(),tree[rs].vec.begin(),tree[rs].vec.end(),tree[index].vec.begin());
		auto it=tree[index].vec.begin();
		for(; it!=tree[index].vec.end(); it++)if(*it>index)break;
		tree[index].vec.insert(it,index);
	}
	void rotate(int &index,bool side,double l,double r) {
		int son=tree[index].child[side^1];
		tree[index].child[side^1]=tree[son].child[side];
		tree[son].child[side]=index;
		tree[son].vec=tree[index].vec;
		push_up(index);
		index=son;
		rebuild(index,l,r);
	}
	int cmp(int x,int y) {
		return val(x)>val(y)||(val(x)==val(y)&&num(x-1)>=num(y-1));
	}
	void insert(int &index,double l,double r,int New) {
		if(!index) {
			index=New;
			num(index)=mid;
			tree[index].vec.push_back(New);
			return;
		}
		tree[index].vec.push_back(New);
		bool side=cmp(New,index);
		int &son=tree[index].child[side];
		if(side==0)insert(son,l,mid,New);
		else insert(son,mid,r,New);
		if(d(index)<d(son))rotate(index,side^1,l,r);
	}
	void insert(int val) {
		int New=newnode(val);
		insert(root,0,1e18,New);
	}
	void del(int &index,double l,double r) {
		if(!ls(index)&&!rs(index)) {
			tree[index].vec.clear();
			index=0;
			size--;
			return;
		}
		bool side=d(rs(index))<d(ls(index));
		rotate(index,side,l,r);
		tree[index].vec.pop_back();
		if(side==0)del(ls(index),l,mid);
		else del(rs(index),mid,r);
	}
	void find_del(int &index,double l,double r) {
		if(index==size) {
			del(index,l,r);
			return;
		}
		tree[index].vec.pop_back();
		bool side=!(ls(index)&&tree[ls(index)].vec.back()==size);
		if(side==0)find_del(ls(index),l,mid);
		else find_del(rs(index),mid,r);
	}
	int ask(int index,int l,int r) {
		if(!index)return 0;
		return upper_bound(tree[index].vec.begin(),tree[index].vec.end(),r)-lower_bound(tree[index].vec.begin(),tree[index].vec.end(),l);
	}
	int query(int index,int Left,int Right) {
		if(!index||Left>Right)return 0;
		bool side=0;
		for(int i=1; i<=min(qlen,index+1); i++)
			if(qs[i]!=a[index-i+1]) {
				side=a[index-i+1]<qs[i];
				break;
			}
		if(!side)return query(ls(index),Left,Right);
		return (Left<=index&&index<=Right)+ask(ls(index),Left,Right)+query(rs(index),Left,Right);
	}
} treap;

int trans(char x) {
	return islower(x)?x-'a':x-'A'+26;
}

int q,len,lastans=0;
char s[maxq],s2[maxq];

void Decode() {
	qlen=strlen(s2+1);
	for(int i=1; i<=qlen; i++)qs[i]=(trans(s2[i])+lastans)%52;
	reverse(qs+1,qs+qlen+1);
}

int main() {
	srand(99995999);
	scanf("%s",s+1);
	len=strlen(s+1);
	for(int i=1; i<=len; i++)treap.insert(a[i]=trans(s[i]));
	a[0]=treap.tree[0].d=-1;
	q=Get_Int();
	for(int i=1; i<=q; i++) {
		int opt=Get_Int();
		if(opt==1) {
			char x=' ';
			while(!isalpha(x))x=getchar();
			treap.insert(a[++len]=(trans(x)+lastans)%52);
		} else if(opt==2) {
			treap.find_del(treap.root,0,1e18);
			len--;
		} else {
			int x=Get_Int()^lastans,y=Get_Int()^lastans;
			scanf("%s",s2+1);
			Decode();
			qs[++qlen]=-2,lastans=-treap.query(treap.root,x+qlen-2,y);
			qs[qlen]=53,lastans+=treap.query(treap.root,x+qlen-2,y);
			printf("%d\n",lastans);
		}
	}
	return 0;
} 