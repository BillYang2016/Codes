#include<bits/stdc++.h>

using namespace std;

int n,m;

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&m);
		int ans=INT_MAX/2;
		for(int i=1; i<=n; i++) {
			int x,y;
			scanf("%d%d",&x,&y);
			int tmp=m/x;
			if(m%x)tmp++;
			ans=min(ans,tmp*y);
		}
		printf("%d\n",ans);
	}
	return 0;
}