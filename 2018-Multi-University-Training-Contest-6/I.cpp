#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

struct Node {
	int point;
	bool type;
} a[maxn];

int n,vst[maxn],ans=0;
bool Color[maxn];

void Dfs(int Now) {
	vst[Now]=-1;
	int &Next=a[Now].point;
	if(a[Now].type)vst[Now]=Next;
	else {
		if(!vst[Next])Dfs(Next);
		vst[Now]=vst[Next];
		if(vst[Now]==Now||Color[Next])Color[Now]=1,ans++;
	}
}

void Clear() {
	ans=0;
	memset(vst,0,sizeof(vst));
	memset(Color,0,sizeof(Color));
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		Clear();
		for(int i=1; i<=n; i++) {
			a[i].point=Get_Int();
			char ch=0;
			while(!isalpha(ch))ch=getchar();
			a[i].type=ch=='w';
		}
		for(int i=1; i<=n; i++)if(!vst[i])Dfs(i);
		printf("0 %d\n",ans);
	}
	return 0;
}