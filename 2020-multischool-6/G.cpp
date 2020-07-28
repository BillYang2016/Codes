#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=205;

int n,k,Up[maxn][maxn],Left[maxn][maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		k=Get_Int();
		if(2*(n+1)*n%k||n==1||k==1) {
			puts("-1");
			continue;
		}
		int now=0;
		for(int i=1; i<=n+1; i++) {
			for(int j=1; j<=n; j++) {
				now++;
				if(now>k)now=1;
				Up[i][j]=now;
			}
			if(i<=n) {
				for(int j=1; j<=n+1; j++) {
					now++;
					if(now>k)now=1;
					Left[i][j]=now;
				}
			}
		}
		for(int i=1; i<=n+1; i++) {
			for(int j=1; j<=n; j++)printf("%d ",Up[i][j]);
			putchar('\n');
		}
		for(int i=1; i<=n+1; i++) {
			for(int j=1; j<=n; j++)printf("%d ",Left[j][i]);
			putchar('\n');
		}
	}
	return 0;
}