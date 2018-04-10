#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,K=31;

struct Linear_Bases {
	int b[K+1];
	Linear_Bases() {fill(b,b+K+1,0);}
	void add(int num) {
		for(int j=K; j>=0; j--)if(num>>j&1) {
			if(b[j]) {num^=b[j];continue;}
			b[j]=num;
			for(int k=j-1; k>=0; k--)if(b[j]>>k&1)b[j]^=b[k];
			for(int k=j+1; k<=K; k++)if(b[k]>>j&1)b[k]^=b[j];
			break;
		}
	}
} lb;

int main() {
	int n=Get_Int();
	for(int i=1; i<=n; i++)lb.add(Get_Int());
	int ans=0;
	for(int i=K; i>=0; i--)ans^=lb.b[i];
	printf("%d ",ans);
	for(int i=0; i<=K; i++)if(lb.b[i]) {ans^=lb.b[i];break;}
	printf("%d\n",ans);
	return 0;
}