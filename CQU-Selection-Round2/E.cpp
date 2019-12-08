#include<bits/stdc++.h>

using namespace std;

int n,m,cnt[20][20],f[1<<20],g[1<<20][20];
string s;

#define lowbit(i) (i&(-i))

int main() {
	ios::sync_with_stdio(false);
	cin>>n>>m>>s;
	for(int i=0; i<n-1; i++) {
		cnt[s[i]-'a'][s[i+1]-'a']++;
		cnt[s[i+1]-'a'][s[i]-'a']++;
	}
	for(int S=1; S<(1<<m); S++)
		for(int i=0; i<m; i++)if(!((S>>i)&1))g[S][i]=g[S^lowbit(S)][i]+cnt[(int)log2(lowbit(S))][i];
	for(int S=1; S<(1<<m); S++) {
		f[S]=INT_MAX/2;
		int sum=0;
		for(int i=0; i<m; i++)if(!((S>>i)&1))sum+=g[S][i];
		for(int i=0; i<m; i++)if((S>>i)&1)f[S]=min(f[S],f[S^(1<<i)]+sum);
	}
	printf("%d\n",f[(1<<m)-1]);
	return 0;
}