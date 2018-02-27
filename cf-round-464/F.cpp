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
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=100005,maxk=105;

int n,k,f[2][maxn],l[maxk],r[maxk];

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<=k; i++)l[i]=Get_Int(),r[i]=Get_Int();
	f[0][0]=0;
	for(int i=1; i<=n; i++)f[0][i]=INT_MAX/2;
	deque<int> Q;
	int now=0,pre=1;
	for(int i=1; i<=k; i++) {
		swap(now,pre);
		for(int j=0; j<=n; j++)f[now][j]=f[pre][j];
		Q=deque<int>();
		Q.push_back(0);
		for(int j=1; j<=min(n,r[i]); j++) {
			while(!Q.empty()&&Q.front()<j-(r[i]-l[i]))Q.pop_front();
			if(!Q.empty())f[now][j]=min(f[now][j],f[pre][Q.front()]+2);
			if(j<=n) {
				while(!Q.empty()&&f[pre][j]<=f[pre][Q.back()])Q.pop_back();
				Q.push_back(j);
			}
		}
		Q=deque<int>();
		Q.push_back(0);
		for(int j=r[i]; j>=0; j--) {
			while(!Q.empty()&&Q.front()<l[i]-j)Q.pop_front();
			if(j<=n&&!Q.empty())f[now][j]=min(f[now][j],f[pre][Q.front()]+1);
			if(r[i]-j+1<=n) {
				while(!Q.empty()&&f[pre][r[i]-j+1]<=f[pre][Q.back()])Q.pop_back();
				Q.push_back(r[i]-j+1);
			}
		}
	}
	if(f[k&1][n]==INT_MAX/2)puts("Hungry");
	else printf("Full\n%d\n",f[k&1][n]);
	return 0;
}