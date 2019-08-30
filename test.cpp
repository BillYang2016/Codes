#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int main() {
	freopen("test.txt","w",stdout);
	srand(time(NULL));
	int t=1000000000,n=4,cnt=0,a[105];
	while(t--) {
		for(int i=1; i<=n; i++)a[i]=rand()%2;
		if(a[1]==a[2]&&a[2]==a[3]&&a[3]==a[4])cnt++;
	}
	printf("%d\n",cnt);
	return 0;
}