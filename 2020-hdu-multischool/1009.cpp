#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=50005;

bool del[maxn];

struct line {
	int p,a;
	bool del;
	line() {p=a=del=0;}
	bool operator < (const line& b) const {return a>b.a;}
	bool operator == (const line& b) const {return a==b.a&&p==b.p;}
} a[maxn],S[maxn];

bool Check(line a,line b,line c) {
	if(a.a==b.a)return b.p>a.p;
	if(b.p-a.p>0)return true;
	/*
	double x=(b.p-a.p)/(a.a-b.a);
	if(x<0)return true;
	if(a.p+a.a*x<c.p+c.a*x)return true;
	*/
	if(c.p==0&&c.a==0)return false;
	//if(a.p*(a.a-b.a)+a.a*(b.p-a.p)<c.p*(a.a-b.a)+c.a*(b.p-a.p))return true;
	if((__int128)a.p*(a.a-b.a)+(__int128)a.a*(b.p-a.p)<(__int128)c.p*(a.a-b.a)+(__int128)c.a*(b.p-a.p))return true;
	return false;
}

int main() {
	int t=Get_Int();
	while(t--) {
		int n=Get_Int();
		for(int i=1; i<=n; i++) {
			a[i].p=Get_Int();
			a[i].a=Get_Int();
			a[i].del=0;
		}
		sort(a+1,a+n+1);
		for(int i=1; i<n; i++)if(a[i]==a[i+1])a[i].del=a[i+1].del=1;
		int top=0;
		for(int i=1; i<=n; i++) {
			while(top>0&&Check(S[top],a[i],S[top-1]))top--;
			S[++top]=a[i];
		}
		int ans=0;
		for(int i=1; i<=top; i++)if(!S[i].del)ans++;
		printf("%d\n",ans);
	}
	return 0;
}