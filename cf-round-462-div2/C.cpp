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

const int maxn=2005;

int n,sumL[maxn],sumR[maxn],a[maxn],ans=0;
vector<int> New;

struct node {
	int v,pos;
} c[maxn];

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	int sum=1;
	for(int i=2; i<=n; i++)
		if(a[i]==a[i-1])sum++;
		else {
			New.push_back(sum);
			sum=1;
		}
	New.push_back(sum);
	sumL[0]=a[1]==1?New[0]:0;
	for(int i=1; i<New.size(); i++)
		if((i&1)^(a[1]==1))sumL[i]=sumL[i-1]+New[i];
		else sumL[i]=sumL[i-1];
	sumR[New.size()-1]=a[n]==2?New.back():0;
	for(int i=New.size()-2; i>=0; i--)
		if(((New.size()-i)&1)^(a[n]==2))sumR[i]=sumR[i+1];
		else sumR[i]=sumR[i+1]+New[i];
	int cnt=0;
	for(int i=a[1]==1?1:0; i<New.size(); i+=2) {
		if(i==New.size()-1)break;
		c[++cnt].v=New[i]+New[i+1];
		c[cnt].pos=i-1;
	}
	for(int i=1; i<=cnt; i++)ans=max(ans,c[i].v+sumL[c[i].pos]+sumR[c[i].pos+3]);
	for(int i=0; i<New.size(); i++)ans=max(ans,sumL[i]+sumR[i+1]);
	printf("%d\n",max(ans,max(sumL[New.size()-1],sumR[0])));
	return 0;
}