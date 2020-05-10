#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1000005;

int buc[maxn],ans[maxn];

int main() {
	for(int i=0; i<1000000; i++) {
		int sum1=i/100000+(i/10000)%10+(i/1000)%10,sum2=(i/100)%10+(i/10)%10+i%10;
		int delta=abs(sum1-sum2);
		buc[delta]++;
		for(int j=0; j<delta; j++)ans[i]+=buc[j];
	}
	int t=Get_Int();
	while(t--)printf("%d\n",ans[Get_Int()]);
	return 0;
}