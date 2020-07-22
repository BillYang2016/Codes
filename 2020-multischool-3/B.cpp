#include<bits/stdc++.h>

using namespace std;

string s;
int n,q;

int main() {
	ios::sync_with_stdio(false);
	cin>>s>>q;
	n=s.length();
	int pos=0;
	for(int i=1; i<=q; i++) {
		char opt;
		int x;
		cin>>opt>>x;
		if(opt=='A')printf("%c\n",s[(pos+x-1)%n]);
		else pos=((pos+x)%n+n)%n;
	}
	return 0;
}