#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=205;

struct Point {
	int x,y;
	bool operator < (const Point &b) const {return x<b.x||(x==b.x&&y<b.y);}
} Begin[maxn],Final[maxn];

int n,m,k,Maxx,Maxy;

int main() {
	n=Get_Int();
	m=Get_Int();
	k=Get_Int();
	for(int i=1; i<=k; i++) {
		Begin[i].x=Get_Int(),Begin[i].y=Get_Int();
		Maxx=max(Maxx,Begin[i].x),Maxy=max(Maxy,Begin[i].y);
	}
	for(int i=1; i<=k; i++)Final[i].x=Get_Int(),Final[i].y=Get_Int();
	sort(Final+1,Final+k+1);
	vector<char> ans;
	for(int i=1; i<Maxx; i++)ans.push_back('U');
	for(int i=1; i<Maxy; i++)ans.push_back('L');
	int nowx=1,nowy=1;
	for(int i=1; i<=k; i++) {
		for(int j=1; j<=nowx-Final[i].x; j++)ans.push_back('U');
		for(int j=1; j<=nowy-Final[i].y; j++)ans.push_back('L');
		for(int j=1; j<=Final[i].x-nowx; j++)ans.push_back('D');
		for(int j=1; j<=Final[i].y-nowy; j++)ans.push_back('R');
		nowx=Final[i].x,nowy=Final[i].y;
	}
	printf("%d\n",ans.size());
	for(char x:ans)putchar(x);
	return 0;
}