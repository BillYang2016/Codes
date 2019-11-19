#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

#define mp make_pair
typedef pair<int,int> pii;

int t,n,a[100005];
vector<pii> vec;

int main() {
	t=Get_Int();
	while(t--) {
		n=Get_Int();
		bool flag=1;
		vec.clear();
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		for(int i=1; i<=n; i++) {
			a[i]=Get_Int()-a[i];
			if(a[i]<0)flag=0;
			else if(a[i]>0)vec.push_back(mp(i,a[i]));
		}
		if(!flag) {puts("NO");continue;}
		if(vec.size()<=1) {puts("YES");continue;}
		int delta=vec[0].second,pos=vec[0].first-1;
		for(pii x:vec) {
			if(x.first!=pos+1||x.second!=delta) {puts("NO");flag=0;break;}
			pos++;
		}
		if(flag)puts("YES");
	}
	return 0;
}