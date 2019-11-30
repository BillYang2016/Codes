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

int n,L[maxn],R[maxn],father[maxn],f[maxn];

bool Check(int x,int y) {return (L[x]<=L[y]&&R[x]>=L[y]&&R[x]<=R[y]);}

int Get(int x) {return father[x]==x?x:father[x]=Get(father[x]);}

void Union(int x,int y) {
	int fx=Get(x),fy=Get(y);
	if(fx!=fy) {
		father[fx]=fy;
		f[fy]=max(f[fy],f[fx]);
	}
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		L[i]=Get_Int();
		R[i]=Get_Int();
		f[i]=R[i];
		father[i]=i;
	}
	for(int i=1; i<=n; i++)
		for(int j=i+1; j<=n; j++)
			if(Check(i,j)||Check(j,i))Union(i,j);
	for(int i=1; i<=n; i++)printf("%d\n",f[Get(i)]);
	return 0;
}