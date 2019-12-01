#include <bits/stdc++.h>
using namespace std;
int f[405][405];
int a[405],b[405],h[405];
int main() {
	int n,w;
	scanf("%d%d",&n,&w);
	for (int i=1;i<=n;i++) scanf("%d%d%d",&a[i],&b[i],&h[i]);
	memset(f,0x7f,sizeof(f));c
	for (int len=1;len<=n;len++) {
		for (int i=1;i+len-1<=n;i++) {
			int j = i + len - 1;
			for (int k=i;k<=j;k++) {
				int l_cost = k-1>=i?f[i][k-1]:0;
				int r_cost = k+1<=j?f[k+1][j]:0;
				int t = (h[k] + w - 1) / w;
				f[i][j] = min(f[i][j],l_cost+r_cost+t*(a[k]+b[i-1]+b[j+1]));
			}
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
}
