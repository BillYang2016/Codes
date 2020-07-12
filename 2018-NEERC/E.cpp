#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1005;

int n,buc[maxn],sum[maxn],ans[maxn];
bool vst[maxn];

struct node {
	int v,cnt;
	node(int a=0,int b=0):v(a),cnt(b) {}
	bool operator < (const node b) const {return v<b.v;}
};

int main() {
	n=Get_Int();
	bool flag=1;
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		if(y!=n)flag=0;
		buc[x]++;
	}
	for(int i=1; i<n; i++)sum[i]=sum[i-1]+buc[i];
	for(int i=1; i<n; i++)if(sum[i]>i)flag=0;
	if(flag==0) {puts("NO");return 0;}
	priority_queue<node> Q;
	for(int i=1; i<n; i++)if(buc[i])Q.push(node(i,buc[i]));
	int pos=1;
	ans[1]=n;
	while(!Q.empty()) {
		node Now=Q.top();
		Q.pop();
		pos+=Now.cnt;
		ans[pos]=Now.v;
		vst[Now.v]=1;
	}
	int Now=1,last=n;
	for(int i=n-1; i>=1; i--)if(ans[i]) {
		for(int j=i+1; j<last; j++) {
			while(Now<n&&vst[Now])Now++;
			ans[j]=Now++;
		}
		last=i;
	}
	puts("YES");
	for(int i=1; i<n; i++)printf("%d %d\n",ans[i],ans[i+1]);
	return 0;
}