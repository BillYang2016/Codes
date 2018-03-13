#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
#define pii pair<LL,LL>

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int pr[]= {2,3,5,7},maxs=50005,mod=20120427;

int count(int x,int k) {int cnt=0;while(x%k==0)x/=k,cnt++;return cnt;}

struct node {
	int len,cnt[4];
	node(int a=0,int b=0,int c=0,int d=0,int e=0) {len=a,cnt[0]=b,cnt[1]=c,cnt[2]=d,cnt[3]=e;}
};

LL Pow[20];
int idx[65][40][30][25],trans[maxs][10],tot=0;

void init() {
	Pow[0]=1;
	for(int i=1; i<=18; i++)Pow[i]=Pow[i-1]*10%mod;
	int cnt[10][4];
	for(int i=1; i<=9; i++)
		for(int p=0; p<4; p++)
			cnt[i][p]=count(i,pr[p]);
	queue<node> Q;
	Q.push(node());
	idx[0][0][0][0]=++tot;
	while(!Q.empty()) {
		node Now=Q.front();
		Q.pop();
		int id=idx[Now.cnt[0]][Now.cnt[1]][Now.cnt[2]][Now.cnt[3]];
		trans[id][0]=id;
		if(Now.len>18)continue;
		for(int i=1; i<=9; i++) {
			node Next=node(Now.len+1,Now.cnt[0]+cnt[i][0],Now.cnt[1]+cnt[i][1],Now.cnt[2]+cnt[i][2],Now.cnt[3]+cnt[i][3]);
			int &nid=idx[Next.cnt[0]][Next.cnt[1]][Next.cnt[2]][Next.cnt[3]];
			if(!nid) {nid=++tot;Q.push(Next);}
			trans[nid][i]=id;
		}
	}
}

int a[20];

int index(LL k) {
	int cnt[]= {0,0,0,0};
	for(int i=0; i<4; i++)while(k%pr[i]==0)k/=pr[i],cnt[i]++;
	if(k>1)return 0;
	return idx[cnt[0]][cnt[1]][cnt[2]][cnt[3]];
}

namespace notzero {
	pii f[20][maxs][2];
	bool vst[20][maxs][2];
	pii Dp(int Now,int s,bool zero,bool up) {
		if(Now==0)return pii(s==idx[0][0][0][0],0);
		if(!up&&vst[Now][s][zero])return f[Now][s][zero];
		if(!up)vst[Now][s][zero]=1;
		int lim=up?a[Now]:9;
		pii now(0,0);
		for(int i=!zero; i<=lim; i++) {
			pii next=Dp(Now-1,trans[s][i],zero&&i==0,up&&i==lim);
			now.first=(now.first+next.first)%mod;
			now.second=(now.second+next.second+i*Pow[Now-1]%mod*next.first%mod)%mod;
		}
		if(!up)f[Now][s][zero]=now;
		return now;
	}
}

namespace zero {
	pii f[20][2][2];
	bool vst[20][2][2];
	pii Dp(int Now,bool have,bool zero,bool up) {
		if(Now==0)return pii(have,0);
		if(!up&&vst[Now][have][zero])return f[Now][have][zero];
		if(!up)vst[Now][have][zero]=1;
		int lim=up?a[Now]:9;
		pii now(0,0);
		for(int i=0; i<=lim; i++) {
			pii next=Dp(Now-1,!zero&&(have||i==0),zero&&i==0,up&&i==lim);
			now.first=(now.first+next.first)%mod;
			now.second=(now.second+next.second+i*Pow[Now-1]%mod*next.first%mod)%mod;
		}
		if(!up)f[Now][have][zero]=now;
		return now;
	}
}

LL Solve(LL x,LL k) {
	if(k==0) {
		int cnt=0;
		while(x) {a[++cnt]=x%10;x/=10;}
		return zero::Dp(cnt,0,1,1).second;
	} else {
		int id=index(k),cnt=0;
		if(!id)return 0;
		while(x) {a[++cnt]=x%10;x/=10;}
		return notzero::Dp(cnt,id,1,1).second;
	}
}

int main() {
	init();
	int t=Get_Int();
	while(t--) {
		LL L=Get_Int(),R=Get_Int(),k=Get_Int();
		printf("%lld\n",(Solve(R,k)-Solve(L-1,k)+mod)%mod);
	}
	return 0;
}