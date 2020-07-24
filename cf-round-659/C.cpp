#include<bits/stdc++.h>

using namespace std;

const int maxn=100005;

int n,a[maxn],b[maxn],Hash[25][25];
string s1,s2;

int main() {
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--) {
		cin>>n>>s1>>s2;
		s1=' '+s1,s2=' '+s2;
		for(int i=1; i<=n; i++) {
			a[i]=s1[i]-'a';
			b[i]=s2[i]-'a';
		}
		bool flag=1;
		for(int i=1; i<=n; i++)if(a[i]>b[i]) {flag=0;break;}
		if(flag==0) {puts("-1");continue;}
		for(int i=0; i<20; i++)
			for(int j=0; j<20; j++)Hash[i][j]=0;
		for(int i=1; i<=n; i++)if(b[i]>a[i])Hash[a[i]][b[i]-a[i]]++;
		int ans=0;
		for(int i=0; i<20; i++) {
			int Min=100;
			for(int j=0; j<20; j++)if(Hash[i][j]) {Min=j;break;}
			if(Min==100)continue;
			for(int j=Min+1; j<20; j++)Hash[Min+i][j-Min]+=Hash[i][j];
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}