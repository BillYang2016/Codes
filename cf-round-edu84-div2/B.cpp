#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

vector<int> a[maxn];
bool vst[maxn],Princess[maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		int n=Get_Int();
		for(int i=1; i<=n; i++) {
			int size=Get_Int();
			a[i].clear();
			vst[i]=Princess[i]=0;
			for(int j=1; j<=size; j++)a[i].push_back(Get_Int());
		}
		for(int i=1; i<=n; i++) {
			int bj=0;
			for(int x:a[i])if(!vst[x]) {
				vst[x]=1;
				bj=1;
				break;
			}
			if(!bj)Princess[i]=1;
		}
		int bj1=-1,bj2=-1;
		for(int i=1; i<=n; i++) {
			if(Princess[i])bj1=i;
			if(!vst[i])bj2=i;
		}
		if(~bj1&&~bj2) {puts("IMPROVE");printf("%d %d\n",bj1,bj2);}
		else puts("OPTIMAL");
	}
	return 0;
}