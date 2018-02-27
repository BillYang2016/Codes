#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>

using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=1005;

int n,m,k;
bool ans[maxn][maxn],map[maxn][maxn];
vector<int> edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

namespace Solve3 {
	void solve() { //O(m^2)
		for(int Now=1; Now<=n; Now++)
			for(int Next1:edges[Now])
				for(int Next2:edges[Now])
					if(Next1!=Next2)ans[Next1][Next2]=ans[Next2][Next1]=1;
	}
}

namespace Solve4 {
	void solve() { //O(m^2)
		for(int Now1=1; Now1<=n; Now1++)
			for(int Now2=Now1+1; Now2<=n; Now2++)
				for(int Next1:edges[Now1])if(Next1!=Now2)
					for(int Next2:edges[Now2])if(Next1!=Next2&&Next2!=Now1&&map[Next1][Next2])
						ans[Now1][Now2]=ans[Now2][Now1]=1;
	}
}

namespace Solve5 {
	int cnt[maxn];
	void solve() { //O(m^2)
		for(int Now1=1; Now1<=n; Now1++)
			for(int Now2=Now1+1; Now2<=n; Now2++) {
				int sum=0;
				for(int mid:edges[Now1])if(mid!=Now2&&map[mid][Now2])cnt[mid]++,sum++;
				for(int Next1:edges[Now1])if(Next1!=Now2)
					for(int Next2:edges[Now2])if(Next2!=Now1&&Next1!=Next2)ans[Next1][Next2]=(ans[Next2][Next1]|=(sum-cnt[Next1]-cnt[Next2]>0));
				for(int mid:edges[Now1])if(mid!=Now2&&map[mid][Now2])cnt[mid]--;
			}
	}
}

namespace Solve6 {
	int cnt[maxn];
	void solve() { //O(m^2)
		for(int Now1=1; Now1<=n; Now1++)
			for(int Now2=Now1+1; Now2<=n; Now2++) {
				int sum=0;
				for(int mid1:edges[Now1])if(mid1!=Now2)
					for(int mid2:edges[Now2])if(mid2!=Now1&&mid1!=mid2&&map[mid1][mid2])cnt[mid1]++,cnt[mid2]++,sum++;
				for(int Next1:edges[Now1])if(Next1!=Now2)
					for(int Next2:edges[Now2])if(Next2!=Now1&&Next1!=Next2)ans[Next1][Next2]=(ans[Next2][Next1]|=(sum-cnt[Next1]-cnt[Next2]+map[Next1][Next2]>0));
				for(int mid1:edges[Now1])if(mid1!=Now2)
					for(int mid2:edges[Now2])if(mid2!=Now1&&mid1!=mid2&&map[mid1][mid2])cnt[mid1]--,cnt[mid2]--;
			}
	}
}

namespace Solve7 {
	vector<int> s[maxn][maxn];
	int step=0,cnt[maxn],cnt1[maxn][maxn],cnt2[maxn][maxn],vst1[maxn][maxn],vst2[maxn][maxn];
	void solve() {
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				s[i][j].clear(),vst1[i][j]=vst2[i][j]=0;
		step=0;
		for(int mid=1; mid<=n; mid++)
			for(int Next1:edges[mid])
				for(int Next2:edges[mid])
					if(Next1!=Next2)s[Next1][Next2].push_back(mid);
		for(int Now1=1; Now1<=n; Now1++)
			for(int Now2=Now1+1; Now2<=n; Now2++) {
				fill(cnt+1,cnt+n+1,0);
				int sum=0;
				step++;
				for(int mid1:edges[Now1])if(mid1!=Now2)
					for(int mid2:edges[Now2])if(mid2!=Now1&&mid1!=mid2)
						for(int mid:s[mid1][mid2])if(mid!=Now1&&mid!=Now2) {
							if(vst1[mid1][mid2]==step)cnt1[mid1][mid2]++;
							else vst1[mid1][mid2]=step,cnt1[mid1][mid2]=1;
							if(vst2[mid1][mid]==step)cnt2[mid1][mid]++;
							else vst2[mid1][mid]=step,cnt2[mid1][mid]=1;
							if(vst2[mid2][mid]==step)cnt2[mid2][mid]++;
							else vst2[mid2][mid]=step,cnt2[mid2][mid]=1;
							cnt[mid1]++,cnt[mid2]++,cnt[mid]++;
							sum++;
						}
				for(int Next1:edges[Now1])if(Next1!=Now2)
					for(int Next2:edges[Now2])if(Next2!=Now1&&Next1!=Next2)
						ans[Next1][Next2]=(ans[Next2][Next1]|=(sum-cnt[Next1]-cnt[Next2]+(vst1[Next1][Next2]==step?cnt1[Next1][Next2]:0)+(vst2[Next1][Next2]==step?cnt2[Next1][Next2]:0)+(vst2[Next2][Next1]==step?cnt2[Next2][Next1]:0)>0));
			}
	}
}

int main() {
	int t=Get_Int();
	while(t--) {
		for(int i=1; i<=n; i++) {
			memset(map[i],0,sizeof(map[i]));
			memset(ans[i],0,sizeof(ans[i]));
			edges[i].clear();
		}
		n=Get_Int();
		m=Get_Int();
		k=Get_Int();
		for(int i=1; i<=m; i++) {
			int x=Get_Int(),y=Get_Int();
			if(!map[x][y])AddEdge(x,y),AddEdge(y,x);
			map[x][y]=map[y][x]=1;
		}
		if(k==2)memcpy(ans,map,sizeof(map));
		else if(k==3)Solve3::solve();
		else if(k==4)Solve4::solve();
		else if(k==5)Solve5::solve();
		else if(k==6)Solve6::solve();
		else Solve7::solve();
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++)putchar(ans[i][j]?'Y':'N');
			putchar('\n');
		}
	}
	return 0;
}