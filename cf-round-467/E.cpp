#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=2005;

int n,sum[26];
string A,B;
vector<int> ans;

int main() {
	ios::sync_with_stdio(false);
	cin>>n>>A>>B;
	for(int i=0; i<n; i++)sum[A[i]-'a']++,sum[B[i]-'a']--;
	for(int i=0; i<26; i++)if(sum[i]) {puts("-1");return 0;}
	for(int i=0; i<n; i++)
		for(int j=i; j<n; j++)
			if(A[j]==B[n-1-i]) {
				string L=A.substr(0,j),ch=A.substr(j,1),R=A.substr(j+1);
				reverse(R.begin(),R.end());
				A=ch+L+R;
				ans.push_back(n),ans.push_back(j),ans.push_back(1);
				break;
			}
	printf("%d\n",ans.size());
	for(int x:ans)printf("%d ",x);
	return 0;
}