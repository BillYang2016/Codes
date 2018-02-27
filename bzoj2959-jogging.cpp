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

const int maxn=150005;

struct Union_Set {
	int father[maxn];
	Union_Set() {
		init();
	}
	void init(int n) {
		for(int i=1; i<=n; i++)father[i]=-1;
	}
	int Get_Father(int x) {
		if(father[x]<0)return x;
		else return father[x]=Get_Father(father[x]);
	}
	void merge(int x,int y) {
		int fx=Get_Father(x),fy=Get_Father(y);
		if(father[fx]<father[fy])swap(fx,fy);
		father[fy]+=father[fx];
		father[fx]=fy;
	}
	bool check(int x,int y) {
		return Get_Father(x)==Get_Father(y);
	}
} Together,Belong;

struct Link_Cut_Tree {
	struct Tree {
		int father,child[2];
		bool rev;
		int sum,val;
	} tree[maxn];
	stack<int>S;
	#define fa(x) tree[x].father
	#define ls(x) tree[x].child[0]
	#define rs(x) tree[x].child[1]
	#define rev(x) tree[x].rev
	bool isroot(int index) {
		return ls(fa(index))!=index&&rs(fa(index))!=index;
	}
	bool checkson(int index) {
		return rs(fa(index))==index;
	}
	void push_down(int index) {
		if(!rev(index))return;
		swap(ls(index),rs(index));
		rev(ls(index))^=1;
		rev(rs(index))^=1;
		rev(index)=0;
	}
	void push_up(int index) {
		tree[index].sum=tree[ls(index)].sum+tree[rs(index)].sum+tree[index].val;
	}
	void rotate(int index) {
		int father=fa(index),grand=fa(father),side=checkson(index);
		if(!isroot(father))tree[grand].child[checkson(father)]=index;
		tree[father].child[side]=tree[index].child[side^1];
		fa(tree[father].child[side])=father;
		fa(father)=index;
		tree[index].child[side^1]=father;
		fa(index)=grand;
		push_up(father);
		push_up(index);
	}
	void splay(int index) {
		S.push(index);
		for(int i=index; !isroot(i); i=fa(i))S.push(fa(i));
		while(!S.empty())push_down(S.top()),S.pop();
		for(int father; !isroot(index); rotate(index)) {
			father=fa(index);
			if(!isroot(father))rotate(checkson(index)==checkson(father)?father:index);
		}
	}
	void access(int index) {
		for(int son=0; index; son=index,index=fa(index)) {
			splay(index);
			rs(index)=son;
			push_up(index);
		}
	}
	void reverse(int index) {
		access(index);
		splay(index);
		rev(index)^=1;
	}
	void link(int x,int y) {
		reverse(x);
		fa(x)=y;
	}
	void split(int x,int y) {
		reverse(x);
		access(y);
		splay(y);
	} 
	void cut(int x,int y) { 
		split(x,y);
		ls(y)=fa(x)=0;
	}
	void rebuid(int x,int y) {
		split(x,y);
		queue<int>Q;
		Q.push(y);
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop();
			Belong.father[Now]=y;
			if(ls(Now))Q.push(ls(Now));
			if(rs(Now))Q.push(rs(Now));
			ls(Now)=rs(Now)=0;
		}
		tree[y].val=tree[y].sum;
	}
} lct;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)val[i]=lct.tree[i].val=Get_Int();
	for(int i=1; i<=m; i++) {
		int opt=Get_Father(),x=Get_Int(),y=Get_Int();
		if(opt==1) {
			if(Belong.check(x,y))continue;
			if(!Together.check(x,y))lct.link(x,y),Together.merge(x,y);
			else lct.rebuild(x,y);
		} else if(opt==2) {
			int tmp=Belong.Get_Father(x);
			lct.tree[tmp].val+=y-val[tmp];
			lct.splay(tmp);
			val[x]=y;
		} else {
			if(!Together.check(x,y)) {
				puts("-1");
				continue;
			}
			x=Belong.Get_Father(x),y=Belong.Get_Father(y);
			if(x==y)printf("%d\n",lct.tree[x].val);
			else lct.split(x,y),printf("%d\n",lct.tree[y].sum);
		}
	}
	return 0;
} 
