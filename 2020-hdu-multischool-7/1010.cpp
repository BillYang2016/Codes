#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int dx[]= {1,1,1,0,0,-1,-1,-1}, dy[]= {1,0,-1,1,-1,1,0,-1};

bool vst[1005][1005],flag;
int cnt=0,n=200;

bool Check(int x,int y) {
	if(x<=0||y<=0||x>n||y>n)return false;
	return __gcd(x,y)>1;
}

void Dfs(int x,int y) {
	vst[x][y]=1;
	cnt++;
	if(x==y)flag=1;
	for(int i=0; i<8; i++) {
		if(Check(x+dx[i],y+dy[i])&&!vst[x+dx[i]][y+dy[i]])Dfs(x+dx[i],y+dy[i]);
	}
}

int main() {
	int Max=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) {
			memset(vst,0,sizeof(vst));
			cnt=flag=0;
			Dfs(i,j);
			//if(!flag)printf("%d %d %d %d\n",i,j,cnt,flag);
			if(!flag)Max=max(Max,cnt);
		}
	printf("%d\n",Max);
	return 0;
}