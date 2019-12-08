#include<bits/stdc++.h>

using namespace std;

const int maxn=100005;

int n,ans=0;
bool vst[maxn],flag=0;
string s;

int main() {
	ios::sync_with_stdio(false);
	cin>>n>>s;
	s=' '+s;
	for(int i=1; i<n; i++)if(s[i]=='A'&&s[i+1]=='C') {ans++;vst[i]=vst[i+1]=1;}
	for(int i=1; i<n; i++)if(((s[i]=='A'&&s[i+1]=='A')||(s[i]=='C'&&s[i+1]=='C'))&&!vst[i]&&!vst[i+1])flag=1;
	printf("%d\n",ans+flag);
	return 0;
}