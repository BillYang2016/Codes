#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int main() {
	ios::sync_with_stdio(false);
	int t;
	string s;
	cin>>t;
	while(t--) {
		cin>>s;
		int len=s.length();
		bool flag=1;
		for(int i=0; i<len-1; i++)if(s[i]!=s[i+1]) {flag=0;break;}
		if(flag)cout<<s<<endl;
		else {
			for(int i=0; i<len; i++) {
				cout<<s[i];
				if(i+1<=len-1&&s[i]==s[i+1])cout<<(s[i]=='0'?'1':'0');
			}
			cout<<endl;
		}
	}
	return 0;
}