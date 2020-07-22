#include<bits/stdc++.h>

using namespace std;

int f[1005][1005];

int Dp(int a,int b) {
	if(a==0||b==0)return 0;
	if(a==1&&b==1)return 1;
	if(f[a][b])return f[a][b];
	int x=max(Dp(a-1,b),Dp(a,b-1));
	f[a][b]=x+(__gcd(a,b)==1);
	return f[a][b];
}

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",Dp(a,b));
	}
	return 0;
}