#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=105;

int n,a[maxn],f[maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		for(int i=1; i<=n; i++)f[i]=Get_Int();
		int Left=1,val=0;
		while(Left<n) {
			while(Left<=n&&!f[Left])Left++;
			f[Left]=1;
			int cnt=val;
			for(int i=Left; i<=n; i++)cnt+=f[i]==1;
			val=cnt;
			for(int i=Left; i<=n; i++)if(f[i]==1)a[i]=cnt--;
			for(int i=Left; i<=n; i++)if(f[i]>0)f[i]--;
		}
		for(int i=1; i<n; i++)printf("%d ",a[i]);
		printf("%d\n",a[n]);
	}
	return 0;
}