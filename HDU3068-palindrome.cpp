#include<bits/stdc++.h>

using namespace std;

const int maxn=110005*2;

char tmp[maxn];
int n,f[maxn];
string s;

int main() {
	while(~scanf("%s",tmp)) {
		int len=strlen(tmp);
		s.clear();
		s.push_back('#');
		for(int i=0; i<len; i++)s.push_back(tmp[i]),s.push_back('#');
		n=s.length();
		int Max=0,id=0,ans=0;
		for(int i=1; i<=n-2; i++) {
			f[i]=Max>i?min(f[2*id-i],Max-i):1;
			while(i-f[i]>=0&&i+f[i]<n&&s[i-f[i]]==s[i+f[i]])f[i]++;
			if(f[i]+i>Max) {Max=f[i]+i;id=i;}
			ans=max(ans,f[i]-1);
		}
		printf("%d\n",ans);
	}
	return 0;
}