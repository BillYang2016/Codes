#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

double Get(double s) {
	if(s>=90)return 4;
	if(s>=60)return 1+(s-60)/10;
	return 0;
}

int main() {
	int t;
	scanf("%d",&t);
	double sum=0,sum2=0;
	for(int i=1; i<=t; i++) {
		int s,w;
		scanf("%d%d",&s,&w);
		sum+=Get(s)*w;
		sum2+=w;
	}
	printf("%.2lf\n",sum/sum2);
	return 0;
}