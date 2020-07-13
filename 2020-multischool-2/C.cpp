#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
#define mp make_pair

const int maxn=200005;

vector<pii> ans;
vector<int> edges[maxn];
int n;

pii TreeDp(int Now,int fa) {
	if(edges[Now].size()==1&&fa!=-1)return mp(Now,-1);
	vector<int> tmp;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		pii tmpp=TreeDp(Next,Now);
		if(tmp.size()>=2) {
			ans.push_back(mp(tmp.back(),tmpp.first));
			tmp.pop_back();
		} else tmp.push_back(tmpp.first);
		if(tmp.size()>=2&&tmpp.second!=-1) {
			swap(tmp.back(),tmp[0]);
			ans.push_back(mp(tmp.back(),tmpp.second));
			tmp.pop_back();
		} else if(tmp.size()<2&&tmpp.second!=-1)tmp.push_back(tmpp.second);
	}
	if(fa==-1) {
		if(tmp.size()==2)ans.push_back(mp(tmp[0],tmp[1]));
		else ans.push_back(mp(tmp[0],Now));
	}
	if(tmp.size()==2)return mp(tmp[0],tmp[1]);
	else return mp(tmp[0],-1);
}

int main() {
	scanf("%d",&n);
	if(n==1) {
		puts("0");
		return 0;
	} else if(n==2) {
		int x,y;
		scanf("%d%d",&x,&y);
		printf("1\n%d %d\n",x,y);
		return 0;
	}
	for(int i=1; i<n; i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	for(int i=1; i<=n; i++)if(edges[i].size()>1) {
		TreeDp(i,-1);
		break;
	}
	printf("%d\n",ans.size());
	for(pii x:ans)printf("%d %d\n",x.first,x.second);
	return 0;
}