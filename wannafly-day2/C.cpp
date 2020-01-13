#include <bits/stdc++.h>
using namespace std;
long long a[100005];
int main() {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	long long xorsum = 0;
	for (int i=1;i<=n;i++) {
		xorsum ^= a[i];
		
		if (xorsum == 0) printf("0\n");
		else {
			int cnt = 0;
			for (int j=1;j<=i;j++) if ((xorsum ^ a[j]) < a[j]) cnt ++;
			printf("%d\n",cnt);
		}
	}
	return 0;
}