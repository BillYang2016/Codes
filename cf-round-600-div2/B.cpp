#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n,flag=1,Hash[1000005],sum=0;
vector<int> a,ans;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		int x=Get_Int();
		if(x>0) {
			if(Hash[x]) {flag=0;break;}
			Hash[x]++;
			a.push_back(x);
		} else {
			if(Hash[-x]!=1) {flag=0;break;}
			Hash[-x]++;
		}
		sum+=x;
		if(sum==0) {
			ans.push_back(a.size()*2);
			for(int x:a)Hash[x]=0;
			a.clear();
		}
	}
	if(sum||!flag)puts("-1");
	else {
		printf("%d\n",ans.size());
		for(int x:ans)printf("%d ",x);
		putchar('\n');
	}
	return 0;
}