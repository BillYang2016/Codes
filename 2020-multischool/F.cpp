#include<bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	string a,b;
	while(cin>>a>>b) {
		int lena=a.length(),lenb=b.length(),posa=0,posb=0;
		int gcd=__gcd(lena,lenb);
		long long lcm=lena/gcd*lenb;
		bool flag=0;
		for(int i=0; i<gcd; i++) {
			char x=a[i];
			for(int j=0; ; j++) {
				if(1ll*j*gcd+i>=lena)break;
				if(1ll*j*gcd+i>=lenb)break;
				if(x!=b[j*gcd+i]||x!=a[j*gcd+i]) {
					flag=1;
					break;
				}
			}
			if(flag)break;
		}
		if(flag==0) {
			puts("=");
		} else {
			for(int i=0; i<lcm; i++) {
				if(a[posa]<b[posb]) {
					puts("<");
					break;
				} else if(a[posa]>b[posb]) {
					puts(">");
					break;
				}
				posa++;
				posb++;
				if(posa==lena)posa=0;
				if(posb==lenb)posb=0;
			}
		}
	}
	return 0;
}