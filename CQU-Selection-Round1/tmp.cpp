#include<bits/stdc++.h>

using namespace std;

int main() {
	int ans=0;
	for(int i=1; i<=4000; i++) {
		int cnt=0;
		for(int j=1; j<=i; j++)if(i%j==0)cnt++;
		ans=max(ans,cnt);
	}
	printf("%d\n",ans);
	return 0;
}