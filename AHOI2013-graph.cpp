#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,maxm=200005;

struct Query {int num,del[5];} q[maxm];
struct Edge {int from,to;} edge[maxm];
struct Stack {
	int x,y,fx,fy;
	Stack(int x=0,int y=0,int fx=0,int fy=0):x(x),y(y),fx(fx),fy(fy) {}
} S[maxn];

int father[maxn],top=0;
bool vst[maxm],ans[maxm];

int Get_Father(int x) {return father[x]<0?x:Get_Father(father[x]);}

void Mark(int l,int r,int v) {
	for(int i=l; i<=r; i++)
		for(int j=1; j<=q[i].num; j++)vst[q[i].del[j]]=v;
}

void Merge(int Left,int Right) {
	for(int i=Left; i<=Right; i++)
		for(int j=1; j<=q[i].num; j++) {
			int id=q[i].del[j];
			if(vst[id])continue;
			int fx=Get_Father(edge[id].from),fy=Get_Father(edge[id].to);
			if(fx==fy)continue;
			if(father[fx]>father[fy])swap(fx,fy);
			S[++top]=Stack(fx,fy,father[fx],father[fy]);
			father[fx]+=father[fy];
			father[fy]=fx;
		}
}

void Return(int pre) {
	while(top>pre) {
		father[S[top].x]=S[top].fx;
		father[S[top].y]=S[top].fy;
		top--;
	}
}

bool Check(int x) {
	for(int i=1; i<=q[x].num; i++) {
		int id=q[x].del[i];
		int fx=Get_Father(edge[id].from),fy=Get_Father(edge[id].to);
		if(fx!=fy)return 0;
	}
	return 1;
}

void CDQBinary(int Left,int Right) {
	if(Left==Right) {ans[Left]=Check(Left);return;}
	int mid=(Left+Right)>>1,tmp=top;
	Mark(Left,mid,1),Merge(mid+1,Right),Mark(Left,mid,0);
	CDQBinary(Left,mid),Return(tmp); //向左逼近
	Mark(mid+1,Right,1),Merge(Left,mid),Mark(mid+1,Right,0);
	CDQBinary(mid+1,Right),Return(tmp); //向右逼近
}

int n,m,Q;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		edge[i].from=Get_Int();
		edge[i].to=Get_Int();
	}
	for(int i=1; i<=n; i++)father[i]=-1;
	Q=Get_Int();
	for(int i=1; i<=Q; i++) {
		q[i].num=Get_Int();
		for(int j=1; j<=q[i].num; j++)q[i].del[j]=Get_Int(),vst[q[i].del[j]]=1;
	}
	for(int i=1; i<=m; i++) {
		if(vst[i])continue;
		int fx=Get_Father(edge[i].from),fy=Get_Father(edge[i].to);
		if(fx==fy)continue;
		if(father[fx]>father[fy])swap(fx,fy);
		father[fx]+=father[fy];
		father[fy]=fx;
	}
	Mark(1,Q,0);
	CDQBinary(1,Q);
	for(int i=1; i<=Q; i++)puts(ans[i]?"Connected":"Disconnected");
	return 0;
}