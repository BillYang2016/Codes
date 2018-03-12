#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;

int n,m,top=0,ans1=0,tmp[maxn<<1],a[maxn][2],S[maxn<<2],ans[maxn<<2],f[maxn<<2];
vector<int> edges[maxn<<2];

void Dfs(int Now) {
	S[++top]=Now;
	if(Now<=m)for(int i=ans1-1; ; i++)if(S[top-i]>=m+Now) {ans[Now]=i;break;}
	for(int Next:edges[Now])Dfs(Next);
	top--;
}

int main() {
	n=Get_Int();
	Get_Int();
	for(int i=1; i<=n; i++)tmp[++m]=a[i][0]=Get_Int(),tmp[++m]=a[i][1]=Get_Int();
	sort(tmp+1,tmp+m+1);
	int tot=unique(tmp+1,tmp+m+1)-tmp-1;
	for(int i=1; i<=n; i++) {
		int x,y;
		x=a[i][0]=lower_bound(tmp+1,tmp+tot+1,a[i][0])-tmp;
		y=a[i][1]=lower_bound(tmp+1,tmp+tot+1,a[i][1])-tmp;
		if(x<y)f[x]=max(f[x],y),f[m+x]=max(f[m+x],m+y);
		else f[1]=max(f[1],y),f[x]=max(f[x],m+y),f[m+x]=max(f[m+x],2*m);
	}
	for(int i=1; i<=2*m; i++)f[i]=max(f[i],f[i-1]);
	for(int i=1; i<2*m; i++)edges[f[i]].push_back(i);
	for(int i=1; i<=m; i=f[i])ans1++;
	Dfs(m<<1);
	for(int i=1; i<=n; i++)printf("%d ",ans[a[i][0]]);
	return 0;
}