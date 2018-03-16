#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int mod=20110520,hashmod=99599;

int n,m,bit[15],f[2][200005],a[105][105],status[2][200005],cnt[2],now,pre;
char mp[105][105];
vector<int> edges[hashmod];

void add(int &x,int v) {x+=v;if(x>=mod)x-=mod;}

void trans(int s,int sum) {
	int pos=s%hashmod;
	for(int i:edges[pos])if(status[now][i]==s) {add(f[now][i],sum);return;}
	status[now][++cnt[now]]=s;
	f[now][cnt[now]]=sum;
	edges[pos].push_back(cnt[now]);
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)scanf("%s",mp[i]+1);
	for(int i=1; i<=11; i++)bit[i]=(i-1)<<1;
	if(n<m) {
		char tmp[105][105];
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
				tmp[j][i]=mp[i][j];
		memcpy(mp,tmp,sizeof(tmp));
		swap(n,m);
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)a[i][j]=mp[i][j]=='*'?0:1;
	f[0][1]=cnt[0]=1;
	now=0,pre=1;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			swap(now,pre);
			cnt[now]=0;
			for(int k=0; k<hashmod; k++)edges[k].clear();
			for(int k=1; k<=cnt[pre]; k++) {
				int S=status[pre][k],p=(S>>bit[j])&3,q=(S>>bit[j+1])&3,val=f[pre][k];
				if(!a[i][j]) {if(!p&&!q)trans(S,val);continue;}
				if(!p&&!q) {
					if(a[i+1][j])trans(S^1<<bit[j],val);
					if(a[i][j+1])trans(S^1<<bit[j+1],val);
					if(a[i+1][j]&&a[i][j+1])trans(S^(1<<bit[j])<<1^(1<<bit[j+1])<<1,val);
				} else if(!q) {
					if(p==1) {
						if(a[i+1][j])trans(S^1<<bit[j]^(1<<bit[j])<<1,val);
						if(a[i][j+1])trans(S^1<<bit[j]^1<<bit[j+1],val);
					} else {
						trans(S^(1<<bit[j])<<1,val);
						if(a[i][j+1])trans(S^(1<<bit[j])<<1^(1<<bit[j+1])<<1,val);
					}
				} else if(!p) {
					if(q==1) {
						if(a[i+1][j])trans(S^1<<bit[j]^1<<bit[j+1],val);
						if(a[i][j+1])trans(S^1<<bit[j+1]^(1<<bit[j+1])<<1,val);
					} else {
						trans(S^(1<<bit[j+1])<<1,val);
						if(a[i+1][j])trans(S^(1<<bit[j])<<1^(1<<bit[j+1])<<1,val);
					}
				} else if(p+q==2)trans(S^1<<bit[j]^1<<bit[j+1],val);
			}
		}
		for(int j=1; j<=cnt[now]; j++)status[now][j]<<=2;
	}
	printf("%d\n",cnt[now]?f[now][1]:0);
	return 0;
}