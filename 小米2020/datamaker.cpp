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
	freopen("data.txt","w",stdout);
	int n=100000,m=100000;
	cout<<n<<" "<<m<<endl;
	for(int i=1; i<=n; i++)cout<<rand()%100+1<<" "<<rand()<<endl;
	return 0;
}