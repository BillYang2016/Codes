#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
#define mp make_pair

const int maxn=505;

int n,a[maxn][maxn];
bool vst[maxn][maxn];

void newpeople(int x,int y,vector<pii> &work) {
	int Max=0,maxx=0,maxy=0;
	for(int dx=-3; dx<=3; dx++)
		for(int dy=abs(dx)-3; dy<=3-abs(dx); dy++) {
			int nowx=x+dx,nowy=y+dy;
			if(nowx<1||nowx>n||nowy<1||nowy>n)continue;
			if(vst[nowx][nowy])continue;
			if(a[nowx][nowy]>Max) {
				Max=a[nowx][nowy];
				maxx=nowx;
				maxy=nowy;
			}
		}
	work.push_back(mp(maxx,maxy));
	vst[maxx][maxy]=1;
}

int Cal(int x,int y) {
	for(int dx=-3; dx<=3; dx++)
		for(int dy=abs(dx)-3; dy<=3-abs(dx); dy++) {
			int nowx=x+dx,nowy=y+dy;
			if(nowx<1||nowx>n||nowy<1||nowy>n)continue;
			vst[nowx][nowy]=0;
		}
	int people=1,food=0,cnt=0;
	vector<pii> work;
	work.push_back(mp(x,y));
	vst[x][y]=1;
	while(people<9) {
		for(pii now:work)food+=a[now.first][now.second];
		if(food>=8*people*people) {
			newpeople(x,y,work);
			people++;
		}
		cnt++;
	}
	return cnt;
}

int Dist(int x1,int y1,int x2,int y2) {
	int delta=abs(x1-x2)+abs(y1-y2);
	int ans=delta/2;
	if(delta%2)ans++;
	return ans;
}

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int x,y;
		scanf("%d%d%d",&n,&x,&y);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)scanf("%d",&a[i][j]);
		int ans=INT_MAX/2;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)ans=min(ans,Dist(i,j,x,y)+Cal(i,j));
		printf("%d\n",ans);
	}
	return 0;
}