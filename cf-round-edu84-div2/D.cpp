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

int p[maxn],c[maxn];
bool vst[maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		int n=Get_Int();
		for(int i=1; i<=n; i++)p[i]=Get_Int(),vst[i]=0;
		for(int i=1; i<=n; i++)c[i]=Get_Int();
		int ans=n;
		for(int i=1; i<=n; i++) {
			if(vst[i])continue;
			vector<int> cycle;
			int now=i;
			while(!vst[now]) {
				vst[now]=1;
				cycle.push_back(now);
				now=p[now];
			}
			int size=cycle.size();
			for(int j=1; j<=size; j++) {
				if(size%j)continue;
				for(int st=1; st<=j; st++) {
					bool flag=1;
					for(int now=st; now+j<=size; now+=j)if(c[cycle[now-1]]!=c[cycle[now+j-1]]) {flag=0;break;}
					if(flag) {ans=min(ans,j);break;}
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}