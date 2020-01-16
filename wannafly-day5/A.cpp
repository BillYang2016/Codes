#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n,k;

int main() {
	n=Get_Int();
	k=Get_Int();
	if(k<=2) {
		int ans=0;
		for(int i=1; i<=k; i++) {
			int m=Get_Int();
			for(int j=1; j<=m; j++)Get_Int();
			ans=max(m,ans);
		}
		printf("%d\n",ans);
	} else {
		set<int> S1,S2,S3,S12,S23,S13,S123;
		int m=Get_Int();
		for(int i=1; i<=m; i++)S1.insert(Get_Int());
		m=Get_Int();
		for(int i=1; i<=m; i++)S2.insert(Get_Int());
		m=Get_Int();
		for(int i=1; i<=m; i++)S3.insert(Get_Int());
		set_intersection(S1.begin(),S1.end(),S2.begin(),S2.end(),inserter(S12,S12.begin()));
		set_intersection(S2.begin(),S2.end(),S3.begin(),S3.end(),inserter(S23,S23.begin()));
		set_intersection(S1.begin(),S1.end(),S3.begin(),S3.end(),inserter(S13,S13.begin()));
		set_intersection(S12.begin(),S12.end(),S3.begin(),S3.end(),inserter(S123,S123.begin()));
		int s123=S123.size();
		int s12=S12.size()-s123,s23=S23.size()-s123,s13=S13.size()-s123;
		int s1=S1.size()-s12-s13-s123,s2=S2.size()-s12-s23-s123,s3=S3.size()-s13-s23-s123;
		printf("%d\n",s12+s23+s13+s123+max(0,max(s1-s23,max(s2-s13,s3-s12))));
	}
	return 0;
}