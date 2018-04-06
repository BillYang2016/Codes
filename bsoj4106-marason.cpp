#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const int maxn=55;

int n,m,s1,s2,g1,g2,mp[maxn][maxn],Min[maxn],Max[maxn];
bool Au[maxn],Ag[maxn],Cu[maxn];
LL f[maxn][maxn],ans=0;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)mp[i][j]=i==j?0:INT_MAX/2;
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		mp[x][y]=mp[y][x]=min(mp[x][y],v);
	}
	g1=Get_Int(),g2=Get_Int(),s1=Get_Int(),s2=Get_Int();
	for(int k=1; k<=n; k++)
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
	for(int i=1; i<=n; i++) {
		Min[i]=INT_MAX,Max[i]=INT_MIN;
		for(int j=1; j<=n; j++)if(i!=j)Min[i]=min(Min[i],mp[i][j]),Max[i]=max(Max[i],mp[i][j]);
		Min[i]=Min[i]*100+i,Max[i]=Max[i]*100+i;
	}
	for(int L=1; L<=n; L++) 
		for(int R=1; R<=n; R++) {
			if(L==R)continue;
			if(Min[L]>Max[R])continue;
			memset(Au,0,sizeof(Au)),memset(Ag,0,sizeof(Ag)),memset(Cu,0,sizeof(Cu));
			for(int i=1; i<=n; i++) {
				if(i==L||i==R)continue;
				if(Min[i]<=Min[L])Au[i]=1;
				if(Max[i]>=Max[R])Cu[i]=1;
				for(int j=1; j<=n; j++) {
					if(i==j)continue;
					if(mp[i][j]*100+i>Min[L]&&mp[i][j]*100+i<Max[R]) {Ag[i]=1;break;}
				}
			}
			Au[L]=Cu[R]=1,Ag[L]=Cu[L]=Au[R]=Ag[R]=0;
			memset(f,0,sizeof(f));
			f[0][0]=1;
			for(int i=1; i<=n; i++)
				for(int j=i; j>=0; j--)
					for(int k=i-j; k>=0; k--) {
						if(!Cu[i])f[j][k]=0;
						if(Au[i]&&j)f[j][k]+=f[j-1][k];
						if(Ag[i]&&k)f[j][k]+=f[j][k-1];
					}
			for(int j=g1; j<=g2; j++)
				for(int k=s1; k<=s2; k++)ans+=f[j][k];
		}
	printf("%lld\n",ans);
	return 0;
}