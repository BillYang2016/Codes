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

inline const LL Get_Int() {
	LL num=0,bj=1;
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

const int maxk=50005;

LL now,last,cost,f[2][maxk];
vector<LL>Value[305];

LL Cal(int j,int k) {
	return f[last][j-k*cost]+Value[cost][k];
}

int Binary(int Left,int Right,int x,int y) {
	while(Left<=Right) {
		int mid=(Left+Right)>>1;
		if(Cal(mid,x)>Cal(mid,y))Right=mid-1;
		else Left=mid+1;
	}
	return Left;
}

int n,k;
vector<int>Thing[305];

struct QueNode {
	int pos,l,r;
	QueNode(int p=0,int _l=0,int _r=0):pos(p),l(_l),r(_r) {}
};

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++) {
		int c=Get_Int(),v=Get_Int();
		Thing[c].push_back(v);
	}
	for(int i=1; i<=300; i++) {
		sort(Thing[i].begin(),Thing[i].end(),greater<LL>());
		Value[i].push_back(0);
		for(int j=1; i*j<=k; j++)
			if(j<=Thing[i].size())Value[i].push_back(Value[i].back()+p[i][j-1]);
			else Value[i].push_back(Value[i].back());
	}
	for(int i=1; i<=k; i++)f[0][i]=-INT_MAX;
	for(cost=1; cost<=300; cost++) {
		now=cost&1,last=now^1;
		for(int mod=0; mod<cost; mod++) {
			deque<QueNode>Q;
			Q.push_back(QueNode(0,1,n));
			for(int i=0,index; (index=i*cost+mod)<=k; i++) {
				while(!Q.empty()&&Q.front().r<i)Q.pop_front();
				if(!Q.empty())f[cost][i]=Cal(i,Q.front().pos);
				if(Q.empty()&&Cal(n,i)>Cal(n,Q.back().pos)) {
					while(!Q.empty()&&Cal(Q.back().l,i)>Cal(Q.back().l,Q.back().pos))Q.pop_back();
					if(Q.empty()) {
						if(i+1<=n)Q.push_back(QueNode(i,i+1,n));
					} else {
						int pos=Binary(Q.back().l,Q.back().r,i,Q.back().pos);
						Q.back().r=pos;
						if(pos+1<=n)Q.push_back(QueNode(i,pos+1,n));
					}
				}
			}
		}
	}
	for(int i=1; i<=k; i++) {
		f[now][i]=max(f[now][i],f[now][i-1]);
		printf("%lld\n",f[now][i]);
	}
	return 0;
} 
