#include<bits/stdc++.h>

using namespace std;

int t,n,type0[2000005];
string s;

int main() {
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--) {
		cin>>n>>s;
		type0[n+1]=0;
		for(int i=n; i>=1; i--)type0[i]=type0[i+1]+s[i-1]=='0';
		int sum=0,tmp=0;
		for(int i=1; i<=n; i++) {
			char x=s[i-1];
			if(x=='0') {
				if(tmp>0)sum++,tmp--;
			} else if(x=='1') {
				if(type0[i]>=tmp)tmp++;
				else sum++,tmp--;
			} else if(x=='2')sum++;
			else if(x=='3')sum++;
		}
		printf("%d\n",sum);
	}
	return 0;
}