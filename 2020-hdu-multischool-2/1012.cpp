#include<bits/stdc++.h>

using namespace std;

const int maxn=100005;

int n,m,f[25][25],g[maxn][26];
string a,b;

int main() {
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--) {
		cin>>a>>b;
		n=a.length();
		m=b.length();
		a=' '+a,b=' '+b;
		for(int j=0; j<26; j++)g[n+1][j]=n+1;
		for(int i=n; i>=1; i--) {
			for(int j=0; j<26; j++)g[i][j]=g[i+1][j];
			g[i][a[i]-'a']=i;
		}
		int q;
		cin>>q;
		while(q--) {
			int l,r,ans=0;
			cin>>l>>r;
			for(int i=0; i<=m; i++)
				for(int j=0; j<=m; j++)f[i][j]=n+1;
			f[0][0]=l-1;
			for(int i=1; i<=m; i++)
				for(int j=0; j<=i; j++) {
					f[i][j]=f[i-1][j];
					if(j&&f[i-1][j-1]<r)f[i][j]=min(f[i][j],g[f[i-1][j-1]+1][b[i]-'a']);
					if(f[i][j]<=r)ans=max(ans,j);
				}
			printf("%d\n",r-l+1+m-2*ans);
		}
	}
	return 0;
}