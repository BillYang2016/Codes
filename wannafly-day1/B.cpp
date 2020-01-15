#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1005;

int n,m,a[maxn],b[maxn];
string s[maxn];

int Tonum(char x) {return isupper(x)?x-'A'+26:x-'a';}

char Tochar(int x) {return x<26?x+'a':x-26+'A';}

string Decode(string x,string y) {
	int lenx=x.length(),leny=y.length();
	for(int i=0,j=0; i<leny; i++,j++) {
		if(j>=lenx)j=0;
		y[i]=Tochar((Tonum(y[i])-Tonum(x[j])+52)%52);
	}
	return y;
}

int main() {
	cin>>n>>m;
	for(int i=1; i<=m; i++)cin>>a[i]>>b[i];
	for(int i=1; i<=n; i++)cin>>s[i];
	for(int i=m; i>=1; i--)s[b[i]]=Decode(s[a[i]],s[b[i]]);
	for(int i=1; i<=n; i++)cout<<s[i]<<endl;
	return 0;
}