#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=30005;

int vst[maxn],Prime[maxn],cnt=0;

void Prime_Sieve(int n) {
	for(int i=2; i<=n; i++) {
		if(!vst[i])Prime[++cnt]=i;
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0)break;
		}
	}
}

int n,m1,m2,cnt_m1[maxn];

int main() {
	n=Get_Int();
	m1=Get_Int();
	m2=Get_Int();
	Prime_Sieve(30000);
	for(int i=1; i<=cnt&&Prime[i]<=m1; i++) {
		int x=m1;
		while(x%Prime[i]==0) {
			x/=Prime[i];
			cnt_m1[i]++;
		}
		cnt_m1[i]*=m2;
	}
	int ans=INT_MAX/2;
	for(int t=1; t<=n; t++) {
		LL s=Get_Int();
		int now=-1;
		for(int i=1; i<=cnt; i++) {
			int x=s,cnt_s=0;
			while(x%Prime[i]==0) {
				x/=Prime[i];
				cnt_s++;
			}
			if(cnt_s==0&&cnt_m1[i]) {now=-1;break;}
			else if(cnt_s)now=max(now,int(ceil(1.0*cnt_m1[i]/cnt_s)));
		}
		if(~now)ans=min(ans,now);
	}
	if(ans!=INT_MAX/2)printf("%d\n",ans);
	else puts("-1");
	return 0;
}