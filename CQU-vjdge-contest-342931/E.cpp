#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

// ???

vector<int> ans;
int n;

int main() {
	while(~scanf("%d",&n)) {
		ans.clear();
		for(int i=1; i<=n; i++)
			if(Get_Int()==i)ans.push_back(i);
		if(ans.size()==0)puts("No Mistake");
		else for(int x:ans)
				if(x==ans.back())printf("%d\n",x);
				else printf("%d ",x);
	}
	return 0;
}