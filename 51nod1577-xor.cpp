#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=500005,K=29;

struct node {
	int val,id;
	node(int a=0,int b=0):val(a),id(b) {}
};

struct Linear_Bases {
	node b[K+1];
	Linear_Bases() {fill(b,b+K+1,0);}
	node& operator [] (const int x) {return b[x];}
	void add(node now) {
		for(int j=K; j>=0; j--)
			if(now.val>>j&1) {
				if(b[j].val) {
					if(now.id<b[j].id)swap(b[j],now);
					now.val^=b[j].val;
					continue;
				}
				b[j]=now;
				break;
			}
	}
} f[maxn];

int n,m,a[maxn];

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=n; i>=1; i--) {
		f[i]=f[i+1];
		f[i].add(node(a[i],i));
	}
	m=Get_Int();
	while(m--) {
		int l=Get_Int(),r=Get_Int(),k=Get_Int();
		for(int j=K; j>=0; j--) {
			if(!(k>>j&1))continue;
			if(!f[l][j].val||f[l][j].id>r)break;
			k^=f[l][j].val;
		}
		puts(k?"NO":"YES");
	}
	return 0;
}