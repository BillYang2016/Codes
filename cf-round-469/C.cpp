#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;

string s;
vector<int> zero,one,L[maxn];

int main() {
	ios::sync_with_stdio(false);
	cin>>s;
	for(int i=0; i<s.length(); i++)
		if(s[i]=='0') {
			if(one.empty()) {
				zero.push_back(i+1);
				L[i+1].push_back(i+1);
			} else {
				int x=one.back();one.pop_back();
				L[x].push_back(i+1);
				zero.push_back(x);
			}
		} else {
			if(zero.empty()) {puts("-1");return 0;}
			int x=zero.back();zero.pop_back();
			L[x].push_back(i+1);
			one.push_back(x);
		}
	if(!one.empty()) {puts("-1");return 0;}
	printf("%d\n",zero.size());
	for(int x:zero) {
		printf("%d ",L[x].size());
		for(int y:L[x])printf("%d ",y);
		putchar('\n');
	}
	return 0;
}