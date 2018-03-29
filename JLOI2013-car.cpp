#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=500005;

struct Car {
	int x,v,id;
	bool operator < (const Car &b) const {return v<b.v||(v==b.v&&x>b.x);} 
} a[maxn];
int n,top=0,S[maxn];
bool vst[maxn];
vector<int> ans;

double gettime(int x,int y) {
	if(a[x].v==a[y].v)return 1e10;
	return (double)(a[x].x-a[y].x)/(a[y].v-a[x].v);
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i].x=Get_Int();
	for(int i=1; i<=n; i++)a[i].v=Get_Int();
	for(int i=1; i<=n; i++)a[i].id=i;
	sort(a+1,a+n+1);
	for(int i=1; i<=n; i++) {
		if(a[i].v==a[i-1].v&&a[i].x<a[i-1].x)continue;
		while(top>1&&gettime(S[top-1],S[top])>gettime(S[top],i))top--;
		S[++top]=i;
	}
	for(int i=2; i<=top; i++)if(gettime(S[i-1],S[i])<0)vst[i-1]=1;
	for(int i=1; i<=top; i++)if(!vst[i])ans.push_back(a[S[i]].id);
	sort(ans.begin(),ans.end());
	printf("%d\n",ans.size());
	for(int x:ans)printf("%d ",x);
	return 0;
}