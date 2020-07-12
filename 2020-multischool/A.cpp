#include<bits/stdc++.h>

using namespace std;

const int maxn=200005;

namespace Suffix_Array {
	int sa[maxn],rk[maxn],fir[maxn],sec[maxn],buc[maxn],tmp[maxn],height[maxn];

	void fill_buc(int n,int *a) {
		fill(buc,buc+n+1,0);
		for(int i=1; i<=n; i++)buc[a[i]]++;
		for(int i=1; i<=n; i++)buc[i]+=buc[i-1];
	}

	void build(int n,int *a) {
		fill_buc(n,a);
		for(int i=1; i<=n; i++)rk[i]=buc[a[i]-1]+1; //calculate single alpha rank
		for(int t=1; t<=n; t<<=1) {
			for(int i=1; i<=n; i++) {
				fir[i]=rk[i]; //first key
				sec[i]=(i+t)>n?0:rk[i+t]; //second key
			}
			fill_buc(n,sec); //second key
			for(int i=1; i<=n; i++)tmp[n-(--buc[sec[i]])]=i; //tmp[i] record ith second key's position
			fill_buc(n,fir); //first key
			for(int i=1; i<=n; i++)sa[buc[fir[tmp[i]]]--]=tmp[i];
			bool unique=1;
			for(int j=1,last=0; j<=n; j++) {
				int i=sa[j];
				if(!last)rk[i]=1;
				else if(fir[i]==fir[last]&&sec[i]==sec[last])rk[i]=rk[last],unique=0;
				else rk[i]=rk[last]+1;
				last=i;
			}
			if(unique)break; //already unique
		}
	}
}

using namespace Suffix_Array;

int n,b[maxn];
string s;

struct node {
	int x,y;
	node(int _x=0,int _y=0):x(_x),y(_y) {}
	bool operator < (const node& b) const {
		if(y-x==b.y-b.x)return rk[y+1]<rk[b.y+1]; //前半部分长度相等
		else return y-x<b.y-b.x;
	}
} a[maxn];

int main() {
	while(cin>>n>>s) {
		s=' '+s;
		int x=0,y=0;
		for(int i=1; i<=n; i++)
			if(s[i]=='a') {
				if(x)b[i]=i-x;
				else b[i]=0;
				x=i;
			} else {
				if(y)b[i]=i-y;
				else b[i]=0;
				y=i;
			}
		for(int i=1; i<=n; i++)b[i]++; //腾出空位离散化
		build(n,b);
		x=y=n+1;
		for(int i=n; i>=1; i--)
			if(s[i]=='a') {
				a[i]=node(i,y);
				x=i;
			} else {
				a[i]=node(i,x);
				y=i;
			}
		rk[n+1]=-1,rk[n+2]=-2;
		sort(a+1,a+n+1);
		for(int i=1; i<=n; i++)printf("%d ",a[i].x);
		putchar('\n');
	}
	return 0;
}