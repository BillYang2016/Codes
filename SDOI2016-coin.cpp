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
#include<set>

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

int t,n,maxq,SG[25][25];
bool vst[105];

void Cal_SG() {
	for(int a=0; a<16; a++)
		for(int b=0; b<11; b++) {
			memset(vst,0,sizeof(vst));
			for(int p=1; p<=a; p++) {
				int sum=0;
				for(int q=1; q<=maxq&&p*q<=a; q++)sum^=SG[a-p*q][b],vst[sum]=1;
			}
			for(int p=1; p<=b; p++) {
				int sum=0;
				for(int q=1; q<=maxq&&p*q<=b; q++)sum^=SG[a][b-p*q],vst[sum]=1;
			}
			for(SG[a][b]=0; vst[SG[a][b]]; SG[a][b]++);
		}
}

int main() {
	t=Get_Int();
	while(t--) {
		n=Get_Int();
		maxq=Get_Int();
		Cal_SG();
		int ans=0;
		for(int i=1; i<=n; i++) {
			bool x=Get_Int();
			if(!x) {
				int sum2=0,sum3=0;
				for(int j=i; j%2==0; j/=2)sum2++;
				for(int j=i; j%3==0; j/=3)sum3++;
				ans^=SG[sum2][sum3];
			}
		}
		puts(ans?"win":"lose");
	}
	return 0;
}