#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int SG(int x) {

}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		int ans=0;
		for(int i=1; i<=n; i++)ans=ans^SG(Get_Int());
		puts(ans?"W":"L");
	}
	return 0;
}