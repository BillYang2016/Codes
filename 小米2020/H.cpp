#pragma gcc optimize(3)
#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
    int num=0,bj=1;
    char x=getchar();
    while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
    while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
    return num*bj;
}

const int maxk=200005;

typedef long long LL;

LL cost,now,last,f[2][maxk];
vector<LL> Value[105];

LL Cal(int j,int k) {
	if(j<k)return -LLONG_MAX/2;
	return f[last][k]+Value[cost][(j-k)/cost];
}

int Binary(int Left,int Right,int x,int y) {
	while(Left<=Right) {
		int mid=(Left+Right)>>1;
		if(Cal(mid,x)>Cal(mid,y))Left=mid+1;
		else Right=mid-1;
	}
	return Right;
}

int n,k;
vector<int>Thing[105];

struct QueNode {
	int pos,l,r;
	QueNode(int p=0,int _l=0,int _r=0):pos(p),l(_l),r(_r) {}
} Q[maxk];

int main() {
	while(scanf("%d%d",&n,&k)!=EOF) {
		for(int i=1; i<=100; i++)Thing[i].clear();
		for(int i=0; i<=k; i++)f[0][i]=f[1][i]=0;
		for(int i=1; i<=n; i++) {
			int c=Get_Int();
			int v=Get_Int();
			Thing[c].push_back(v);
		}
		for(int i=1; i<=100; i++) {
			sort(Thing[i].begin(),Thing[i].end(),greater<LL>());
			Value[i].clear();
			Value[i].push_back(0);
			for(int j=1; i*j<=k; j++)
				if(j<=Thing[i].size())Value[i].push_back(Value[i].back()+Thing[i][j-1]);
				else Value[i].push_back(Value[i].back());
		}
		for(cost=1; cost<=100; cost++) {
			now=cost&1,last=now^1;
			for(int mod=0; mod<cost; mod++) {
				int Left=1,Right=1;
				Q[Left]=QueNode(mod,0,k);
				for(int i=0,index; (index=i*cost+mod)<=k; i++) {
					while(Left<=Right&&Q[Left].r<index)Left++;
					if(Left<=Right)Q[Left].l=index;
					if(Left>Right||Cal(k,index)>Cal(k,Q[Right].pos)) {
						while(Left<=Right&&Cal(Q[Right].l,index)>=Cal(Q[Right].l,Q[Right].pos))Right--;
						if(Left>Right)Q[++Right]=QueNode(index,index,k);
						else {
							int pos=Binary(Q[Right].l,Q[Right].r,Q[Right].pos,index);
							Q[Right].r=pos;
							if(pos+1<=k)Q[++Right]=QueNode(index,pos+1,k);
						}
					}
					if(Left<=Right)f[now][index]=Cal(index,Q[Left].pos);
				}
			}
		}
		for(int i=1; i<=k; i++)f[now][i]=max(f[now][i],f[now][i-1]);
		printf("%lld\n",f[now][k]);
	}
	return 0;
} 