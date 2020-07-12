#include<bits/stdc++.h>

using namespace std;

const int maxn=1000005;

char s[maxn];
int sum[maxn];

bool isvowel(char x) {return x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='y';}

int main() {
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1; i<=n; i++)sum[i]=sum[i-1]+isvowel(s[i]);
	double ans=0,cnt=0;
	for(int i=1; i<=n; i++) {
		cnt+=sum[n-i+1]-sum[i-1];
		ans+=cnt/i;
	}
	printf("%.8lf\n",ans/(1ll*n*(n+1)/2));
	return 0;
}