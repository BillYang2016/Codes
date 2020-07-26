#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n;
bool Hash[35];

int main() {
	n=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		for(int j=30; j>=0; j--)if((v>>j)&1)Hash[j]=1;
	}
	int ans=0;
	for(int i=30; i>=0; i--)if(Hash[i])ans+=1<<i;
	printf("%d\n",ans);
	return 0;
}