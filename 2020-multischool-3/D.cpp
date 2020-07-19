#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
#define mp make_pair

int f[55][205];
pii from[55][205];

bool Check(int n,int m) {
	if(m==(n+1)*2) {
		from[n][m]=mp(n,m);
		return true;
	}
	for(int i=2; i<=n; i++)  {
		if(n%i)continue;
		int j=n/i;
		if((i+j)*2==m) {
			from[n][m]=mp(n,m);
			return true;
		}
	}
	return false;
}

bool Check2(int n,int m) {
	return m==n*2;
}

pii Output(int n,int m,int cnt) {
	if(m==(n+1)*2) {
		for(int i=1; i<=n; i++)printf("%d %d\n",cnt*100+i,cnt*100);
		return mp(cnt*100+n,cnt*100);
	}
	for(int i=2; i<=n; i++)  {
		if(n%i)continue;
		int j=n/i;
		if((i+j)*2==m) {
			for(int x=1; x<=i; x++)
				for(int y=1; y<=j; y++)printf("%d %d\n",cnt*100+x,cnt*100+y);
			return mp(cnt*100+i,cnt*100+j);
		}
	}
	return mp(0,0);
}

int Dfs(int n,int m) {
	if(n==0)return m==0;
	if(n==1)return m==4;
	if(~f[n][m])return f[n][m];
	if(n==2) {
		if(m==8) {
			from[n][m]=mp(1,4);
			return f[n][m]=1;
		} else if(m==6) {
			from[n][m]=mp(2,6);
			return f[n][m]=1;
		} else return f[n][m]=0;
	}
	if(Check(n,m))return f[n][m]=1;
	for(int i=1; i<=n/2; i++)
		for(int j=1; j<m; j++) {
			if(Check(i,j)&&Check2(n-i,m-j)) {
				from[n][m]=mp(i,j);
				return f[n][m]=1;
			}
			if(Dfs(i,j)&&Dfs(n-i,m-j)) {
				from[n][m]=mp(i,j);
				return f[n][m]=1;
			}
		}
	return f[n][m]=0;
}

int t,n,m,cnt=0;

void Output(int n,int m) {
	if(n==1) {
		cnt++;
		printf("%d %d\n",cnt*100,cnt*100);
		return;
	}
	pii pi=from[n][m];
	int resn=n-pi.first,resm=m-pi.second;
	if(resn==0&&resm==0) {
		cnt++;
		Output(n,m,cnt);
		return;
	}
	if(Check(pi.first,pi.second)&&Check2(resn,resm)) {
		pii now=Output(pi.first,pi.second,++cnt);
		for(int i=1; i<=resn; i++)printf("%d %d\n",now.first+i,now.second);
		return;
	}
	else {
		Output(pi.first,pi.second);
		Output(resn,resm);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin>>t;
	for(int i=1; i<=50; i++)for(int j=1; j<=200; j++)f[i][j]=-1;
	while(t--) {
		cnt=0;
		cin>>n>>m;
		int flag=Dfs(n,m);
		if(flag) {
			puts("YES");
			Output(n,m);
		} else puts("NO");
	}
	return 0;
}