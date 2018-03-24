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

const int maxn=35,maxs=5005;

struct pii {
	int a,b,c;
	pii(int a=0,int b=0,int c=0):a(a),b(b),c(c) {}
} state[maxs];

int n,m,cnt=0,id[maxn][maxn][maxn];
LL f[2][maxs][2][4];
char mp[maxn][maxn];

void Clear(LL f[][2][4],int id) {for(int s=1; s<=cnt; s++)for(int k=0; k<4; k++)f[s][id][k]=0;}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)scanf("%s",mp[i]+1);
	for(int i=0; i<=m; i++)
		for(int j=i?i+1:0; j<=m; j++)
			for(int k=j?j+1:0; k<=m; k++) {
				state[++cnt]=pii(i,j,k);
				id[i][j][k]=id[i][k][j]=id[j][i][k]=id[j][k][i]=id[k][i][j]=id[k][j][i]=cnt;
			}
	f[0][1][0][0]=1;
	int now=0,pre=1;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			swap(now,pre);
			Clear(f[now],0),Clear(f[now],1);
			for(int s=1; s<=cnt; s++)
				for(int k=0; k<4; k++) {
					int a=state[s].a,b=state[s].b,c=state[s].c;
					if(f[pre][s][0][k]) {
						if(mp[i][j]=='#') {
							if(a!=j&&b!=j&&c!=j)f[now][s][0][k]+=f[pre][s][0][k];
							continue;
						}
						f[now][s][0][k]+=f[pre][s][0][k];
						if(a==j)f[now][id[0][b][c]][1][k]+=f[pre][s][0][k];
						else if(b==j)f[now][id[a][0][c]][1][k]+=f[pre][s][0][k];
						else if(c==j)f[now][id[a][b][0]][1][k]+=f[pre][s][0][k];
						else if(k<3)f[now][id[j][b][c]][0][k+1]+=f[pre][s][0][k]; //新插头
					}
					if(f[pre][s][1][k]&&mp[i][j]=='.') {
						if(a==j||b==j||c==j)continue;
						f[now][s][0][k]+=f[pre][s][1][k]; //结束插头
						f[now][s][1][k]+=f[pre][s][1][k];
					}
				}
		}
		Clear(f[now],1);
	}
	printf("%lld\n",f[now][1][0][3]);
	return 0;
}