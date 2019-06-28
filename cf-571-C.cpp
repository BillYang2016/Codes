#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

string a,b;

int main() {
	cin>>a>>b;
	int n=a.length(),m=b.length(),tmp=0,sum=0,ans=0;
	for(int i=0; i<m; i++)tmp^=b[i]-'0',sum^=a[i]-'0';
	for(int i=m-1; i<n; i++) {
		if(sum==tmp)ans++;
		if(i<n-1)sum^=a[i+1]-'0';
		sum^=a[i-m+1]-'0';
	}
	cout<<ans;
	return 0;
}

