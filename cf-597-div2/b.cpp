#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int t,n,a,b,c,f[105];
string s;

int main() {
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--) {
		cin>>n>>a>>b>>c>>s;
		s=' '+s;
		for(int i=1; i<=n; i++) {
			if(s[i]=='R')s[i]='P';
			else if(s[i]=='S')s[i]='R';
			else s[i]='S';
		}
		memset(f,0,sizeof(f));
		int ans=0;
		for(int i=1; i<=n; i++) {
			if(s[i]=='R'&&a) {
				a--;
				f[i]=1;
				ans++;
			}
			if(s[i]=='P'&&b) {
				b--;
				f[i]=1;
				ans++;
			}
			if(s[i]=='S'&&c) {
				c--;
				f[i]=1;
				ans++;
			}
		}
		if(ans>=ceil(double(n)/2)) {
			puts("YES");
			for(int i=1; i<=n; i++)
				if(f[i])putchar(s[i]);
				else {
					if(a)a--,putchar('R');
					else if(b)b--,putchar('P');
					else c--,putchar('S');
				}
			putchar('\n');
		} else puts("NO");
	}
	return 0;
}