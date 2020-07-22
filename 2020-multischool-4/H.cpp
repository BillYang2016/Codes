#pragma GCC optimize(3)
#include<bits/stdc++.h>

using namespace std;

#define mp make_pair
typedef pair<int,int> pii;

const int maxn=200005;

vector<pii> ans;
int t,n,Maxcnt,cnt=0,Prime[maxn],vst[maxn],vst2[maxn],Min[maxn];
vector<int> vec[maxn];

void Prime_Sieve(int n) {
	for(int i=2; i<=n; i++) {
		if(!vst2[i])Prime[++cnt]=i;
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst2[i*Prime[j]]=1;
			if(i%Prime[j]==0)break;
		}
	}
}

int main() {
	Prime_Sieve(200000);
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(int i=1; i<=n; i++)vst[i]=0,Min[i]=0;
		ans.clear();
		for(int i=1; i<=cnt; i++) {
			if(Prime[i]>n)break;
			vec[i].clear();
			Maxcnt=i;
			for(int j=1; j*Prime[i]<=n; j++) {
				vec[i].push_back(j*Prime[i]);
				if(!Min[j*Prime[i]])Min[j*Prime[i]]=i;
			}
		}
		for(int i=Maxcnt; i>=1; i--) {
			vector<int> tmp;
			int tmpcnt=0;
			for(int x:vec[i])if(!vst[x])tmpcnt++,tmp.push_back(x);
			if(tmpcnt&1) {
				int id=0,minn=INT_MAX/2;
				vector<int> tmp2;
				for(int j=0; j<tmp.size(); j++)if(Min[tmp[j]]<minn) {
					minn=Min[tmp[j]];
					id=j;
				}
				for(int j=0; j<tmp.size(); j++)if(j!=id)tmp2.push_back(tmp[j]);
				for(int j=0; j<tmp2.size(); j+=2) {
					vst[tmp2[j]]=vst[tmp2[j+1]]=1;
					ans.push_back(mp(tmp2[j],tmp2[j+1]));
				}
			} else {
				for(int j=0; j<tmp.size(); j+=2) {
					vst[tmp[j]]=vst[tmp[j+1]]=1;
					ans.push_back(mp(tmp[j],tmp[j+1]));
				}
			}
		}
		printf("%d\n",(int)ans.size());
		for(pii x:ans)printf("%d %d\n",x.first,x.second);
	}
	return 0;
}