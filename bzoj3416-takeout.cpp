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

const int maxn=1000005;

int n,k,top=0,a[maxn],sum[maxn];
vector<vector<int> >ans;

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++) {
		char ch;
		scanf("%c",&ch);
		int x=ch=='c'?-k:1;
		a[++top]=i;
		sum[top]=sum[top-1]+x;
		while(top>=k+1&&sum[top]-sum[top-k-1]==0) {
			vector<int> tmp;
			for(int j=1; j<=k+1; j++)tmp.push_back(a[top--]);
			reverse(tmp.begin(),tmp.end());
			ans.push_back(tmp);
		}
	}
	reverse(ans.begin(),ans.end());
	for(auto x:ans) {
		for(int j=0; j<k+1; j++)printf("%d ",x[j]);
		putchar('\n');
	}
	return 0;
} 
