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

int n,vst[maxn],cnt[5];
string s;

bool Check(int mid) {
	fill(vst+1,vst+n+1,0);
	memset(cnt,0,sizeof(cnt));
	int cnt2=0,cnt0=0;
	for(int i=1; i<=n; i++)if(s[i]=='2') {
		vst[i]=1;
		cnt2++;
		if(cnt2==mid)break;
	}
	for(int i=n; i>=1; i--)if(s[i]=='0') {
		vst[i]=2;
		cnt0++;
		if(cnt0==mid)break;
	}
	for(int i=1; i<=n; i++) {
		if(s[i]=='2') {
			if(vst[i]==1)cnt[1]++;
			else if(cnt[2])cnt[3]++,cnt[2]--;
		} else if(s[i]=='0') {
			if(vst[i]!=2&&cnt[1])cnt[1]--,cnt[2]++;
			else if(vst[i]==2&&cnt[3])cnt[3]--,cnt[4]++;
		}
	}
	return cnt[4]==mid;
}

int main() {
	while(cin>>n) {
		cin>>s;
		s=' '+s;
		int Left=1,Right=n;
		while(Left<=Right) {
			int mid=(Left+Right)>>1;
			if(Check(mid))Left=mid+1;
			else Right=mid-1;
		}
		printf("%d\n",Right);
	}
	return 0;
}