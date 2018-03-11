#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int Cal_Phi(int x) {
	int ans=x;
	for(int i=2; i<=sqrt(x); i++)
		if(x%i==0) {
			ans-=ans/i;
			while(x%i==0)x/=i;
		}
	if(x>1)ans-=ans/x;
	return ans;
}

const int maxn=50005;

vector<int> mods;
int n,m,p,c,a[maxn],cnt[35],pow1[35][1<<16],pow2[35][1<<16];

int Pow(int b,int id,int mod) {
	if(b<cnt[id])return pow1[id][b];
	return 1ll*pow1[id][b&65535]*pow2[id][b>>16]%mod+mod;
}

int Cal(int a,int cnt,int times) {
	int mod=times>0?mods[times]:1;
	if(c==1)return c%mod;
	if(cnt==0)return a<mod?a:a%mod+mod;
	return Pow(Cal(a,cnt-1,times-1),times,mod);
}

struct Segment_Tree {
	struct Tree {
		int left,right;
		int sum,cnt;
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index].left=Left,tree[index].right=Right;
		if(Left==Right) {tree[index].sum=a[Left];return;}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].sum=(tree[ls].sum+tree[rs].sum)%p;
		tree[index].cnt=min(tree[ls].cnt,tree[rs].cnt);
	}
	void modify(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right||tree[index].cnt>=mods.size())return;
		if(tree[index].left==tree[index].right) {tree[index].sum=Cal(a[tree[index].left],++tree[index].cnt,mods.size()-1)%p;return;}
		modify(ls,Left,Right);
		modify(rs,Left,Right);
		push_up(index);
	}
	int query(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].sum;
		return (query(ls,Left,Right)+query(rs,Left,Right))%p;
	}
} st;

int main() {
	n=Get_Int();
	m=Get_Int();
	p=Get_Int();
	c=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	int now=p;
	while(now>1)mods.push_back(now),now=Cal_Phi(now);
	mods.push_back(now);
	reverse(mods.begin(),mods.end());
	for(int i=0; i<mods.size(); i++) {
		pow1[i][0]=1;
		for(int j=1; j<(1<<16); j++)pow1[i][j]=1ll*pow1[i][j-1]*c%mods[i];
		for(int j=0; j<(1<<16); j++) {
			pow2[i][j]=pow1[i][j];
			for(int k=1; k<=16; k++)pow2[i][j]=1ll*pow2[i][j]*pow2[i][j]%mods[i];
		}
		if(c>1) {
			int now=1;
			while(now<mods[i])now*=c,cnt[i]++;
		}
	}
	st.build(1,1,n);
	while(m--) {
		int opt=Get_Int(),x=Get_Int(),y=Get_Int();
		if(opt==0)st.modify(1,x,y);
		else printf("%d\n",st.query(1,x,y));
	}
	return 0;
}