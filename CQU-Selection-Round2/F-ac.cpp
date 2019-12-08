#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int mod=1e9+7;

int n,K,a,b,f[55][55][2];
LL g[55][55][2],C[55][55];
bool vst[55][55][2];

struct QueNode {
	int x,y,l;
	QueNode(int xx=0,int yy=0,int ll=0):x(xx),y(yy),l(ll) {}
};

queue<QueNode> Q;

void Dp() {
	f[0][0][0]=0;
	g[0][0][0]=1;
	vst[0][0][0]=1;
	Q.push(QueNode(0,0,0));
	while(!Q.empty()) {
		QueNode Now=Q.front();
		Q.pop();
		int x=Now.x,y=Now.y;
		if(Now.l==0) {
			for(int i=x; i<=a; i++)
				for(int j=y; j<=b; j++) {
					if((i-x==0&&j-y==0)||(i-x)*50+(j-y)*100>K)continue;
					if(f[i][j][1]>f[x][y][0]+1) {
						f[i][j][1]=f[x][y][0]+1;
						g[i][j][1]=C[a-x][a-i]*C[b-y][b-j]%mod*g[x][y][0]%mod;
						if(!vst[i][j][1]) {
							vst[i][j][1]=1;
							Q.push(QueNode(i,j,1));
						}
					} else if(f[i][j][1]==f[x][y][0]+1)g[i][j][1]=(g[i][j][1]+C[a-x][a-i]*C[b-y][b-j]%mod*g[x][y][0]%mod)%mod;
				}
		} else {
			for(int i=0; i<=x; i++)
				for(int j=0; j<=y; j++) {
					if((x-i==0&&y-j==0)||(i-x)*50+(j-y)*100>K)continue;
					if(f[i][j][0]>f[x][y][1]+1) {
						f[i][j][0]=f[x][y][1]+1;
						g[i][j][0]=C[x][i]*C[y][j]%mod*g[x][y][1]%mod;
						if(!vst[i][j][0]) {
							vst[i][j][0]=1;
							Q.push(QueNode(i,j,0));
						}
					} else if(f[i][j][0]==f[x][y][1]+1)g[i][j][0]=(g[i][j][0]+C[x][i]*C[y][j]%mod*g[x][y][1]%mod)%mod;
				}
		}
	}
}

int main() {
	n=Get_Int();
	K=Get_Int();
	for(int i=1; i<=n; i++)Get_Int()==50?a++:b++;
	for(int i=0; i<=a; i++)
		for(int j=0; j<=b; j++)f[i][j][0]=f[i][j][1]=INT_MAX/2;
	C[0][0]=1;
	for(int i=1; i<=n; i++) {
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	Dp();
	if(f[a][b][1]<INT_MAX/2)printf("%d\n%lld\n",f[a][b][1],g[a][b][1]);
	else puts("-1\n0");
	return 0;
}