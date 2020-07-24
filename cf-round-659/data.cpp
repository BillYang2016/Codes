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
	srand(time(NULL));
	cout<<1<<endl;
	int n=rand()%100+1,k=rand()%100+1,l=rand()%100+1;
	cout<<n<<" "<<k<<" "<<l<<endl;
	for(int i=1; i<=n; i++)cout<<rand()%100+1<<" ";
	return 0;
}