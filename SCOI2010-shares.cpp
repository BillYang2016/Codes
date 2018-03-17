#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=2005;

struct Share {
	int buyp,selp,buylim,sellim;
} a[maxn];

int n,m,w,f[maxn][maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	w=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i].buyp=Get_Int();
		a[i].selp=Get_Int();
		a[i].buylim=Get_Int();
		a[i].sellim=Get_Int();
	}
	memset(f,-0x3f,sizeof(f));
	f[0][0]=0;
	deque<int> Q;
	for(int i=1; i<=n; i++) {
		for(int j=0; j<=a[i].buylim; j++)f[i][j]=-j*a[i].buyp; //0->i
		for(int j=0; j<=m; j++)f[i][j]=max(f[i][j],f[i-1][j]);
		if(i<=w)continue;
		Q=deque<int>();
		for(int j=0; j<=m; j++) {
			while(!Q.empty()&&Q.front()<j-a[i].buylim)Q.pop_front();
			while(!Q.empty()&&f[i-w-1][Q.back()]+Q.back()*a[i].buyp<=f[i-w-1][j]+j*a[i].buyp)Q.pop_back();
			Q.push_back(j);
			int k=Q.front();
			f[i][j]=max(f[i][j],f[i-w-1][k]-(j-k)*a[i].buyp);
		}
		Q=deque<int>();
		for(int j=m; j>=0; j--) {
			while(!Q.empty()&&Q.front()>j+a[i].sellim)Q.pop_front();
			while(!Q.empty()&&f[i-w-1][Q.back()]+Q.back()*a[i].selp<=f[i-w-1][j]+j*a[i].selp)Q.pop_back();
			Q.push_back(j);
			int k=Q.front();
			f[i][j]=max(f[i][j],f[i-w-1][k]+(k-j)*a[i].selp);
		}
	}
	int ans=0;
	for(int i=0; i<=m; i++)ans=max(ans,f[n][i]);
	printf("%d\n",ans);
	return 0;
}