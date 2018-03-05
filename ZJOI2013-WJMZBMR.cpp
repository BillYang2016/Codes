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

const int maxn=50005;

int tmp[maxn*5];

void read(int *s) {
	char ch=getchar();
	int len=0;
	while(ch!='\n')tmp[++len]=ch,ch=getchar();
	for(int i=1; i<=len; i++) {
		int sum=0;
		while(i<=len&&isalpha(tmp[i]))sum=sum*27+tmp[i]-'a'+1,i++;
		s[++s[0]]=sum;
	}
}

int s[maxn],a[maxn],b[maxn],c[maxn],sum=0,ans=INT_MAX/2;

int main() {
	read(s),read(a),read(b),read(c);
	int l=1,r=s[0];
	for(int i=1; i<=a[0]; i++,l++)while(l<=s[0]&&a[i]!=s[l])l++,sum++;
	for(int i=c[0]; i>=1; i--,r--)while(r>=1&&c[i]!=s[r])r--,sum++;
	for(int i=l; i<=r; i++)
		if(s[i]==b[1]) {
			int now=2;
			if(now==b[0]+1) {ans=0;continue;}
			for(int j=i+1; j<=r; j++)
				if(s[j]==b[now]) {
					now++;
					if(now==b[0]+1) {ans=min(ans,j-i+1-b[0]);break;}
				}
		}
	printf("%d\n",ans+sum);
	return 0;
}