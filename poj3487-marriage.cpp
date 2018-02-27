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
#include<map>
using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

int t,n,pref[55][55],Rank[55][55],Next[55],Husband[55],Wife[55];
map<char,int>Mman,Mwoman;
char ManName[55],WomanName[55];
queue<int>Q;

int main() {
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--) {
		cin>>n;
		Mman.clear();
		Mwoman.clear();
		Q=queue<int>();
		for(int i=1; i<=n; i++)cin>>ManName[i],Mman[ManName[i]]=i;
		for(int i=1; i<=n; i++)cin>>WomanName[i],Mwoman[WomanName[i]]=i;
		for(int i=1; i<=n; i++) {
			char Now,tmp;
			int now;
			cin>>Now>>tmp;
			now=Mman[Now];
			for(int j=1; j<=n; j++) {
				char x;
				cin>>x;
				pref[now][j]=Mwoman[x];
			}
			Next[now]=1;
			Wife[now]=0;
			Q.push(now);
		}
		for(int i=1; i<=n; i++) {
			char Now,tmp;
			int now;
			cin>>Now>>tmp;
			now=Mwoman[Now];
			for(int j=1; j<=n; j++) {
				char x;
				cin>>x;
				Rank[now][Mman[x]]=j;
			}
			Husband[now]=0;
		}
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop();
			int Object=pref[Now][Next[Now]++]; //对象
			if(!Husband[Object]) { //没有未婚夫
				Husband[Object]=Now;
				Wife[Now]=Object;
			} else {
				int Enemy=Husband[Object];
				if(Rank[Object][Enemy]>Rank[Object][Now]) { //排名比原来高
					Husband[Object]=Now;
					Wife[Now]=Object;
					Wife[Enemy]=0;
					Q.push(Enemy);
				} else Q.push(Now); //再来
			}
		}
		for(int i=1; i<=n; i++)cout<<ManName[i]<<" "<<WomanName[Wife[i]]<<endl;
		if(t)puts("");
	}
	return 0;
}