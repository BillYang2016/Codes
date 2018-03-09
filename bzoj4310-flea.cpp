#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,K=17;

namespace Suffix_Array {
	int sa[maxn],rk[maxn],fir[maxn],sec[maxn],buc[maxn],tmp[maxn],height[maxn];

	void fill_buc(int n,int *a) {
		fill(buc,buc+n+1,0);
		for(int i=1; i<=n; i++)buc[a[i]]++;
		for(int i=1; i<=n; i++)buc[i]+=buc[i-1];
	}

	void build(int n,int *a) {
		fill_buc(n,a);
		for(int i=1; i<=n; i++)rk[i]=buc[a[i]-1]+1;
		for(int t=1; t<=n; t<<=1) {
			for(int i=1; i<=n; i++) {
				fir[i]=rk[i];
				sec[i]=i+t>n?0:rk[i+t];
			}
			fill_buc(n,sec);
			for(int i=1; i<=n; i++)tmp[n-(--buc[sec[i]])]=i;
			fill_buc(n,fir);
			for(int i=1; i<=n; i++)sa[buc[fir[tmp[i]]]--]=tmp[i];
			bool unique=1;
			for(int j=1,last=0; j<=n; j++) {
				int i=sa[j];
				if(!last)rk[i]=1;
				else if(fir[i]==fir[last]&&sec[i]==sec[last])rk[i]=rk[last],unique=0;
				else rk[i]=rk[last]+1;
				last=i;
			}
			if(unique)break;
		}
		int k=0;
		for(int i=1; i<=n; i++) {
			if(rk[i]==1)k=0;
			else {
				if(k>0)k--;
				int j=sa[rk[i]-1];
				while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k])k++;
			}
			height[rk[i]]=k;
		}
	}
}

using namespace Suffix_Array;

int n,k,Log[maxn],f[maxn][K],a[maxn],b[maxn],lpos,rpos;
LL sum=0;
char s[maxn];

int LCP(int x,int y) {
	if(x==y)return n-x+1;
	x=rk[x],y=rk[y];
	if(x>y)swap(x,y);
	x++;
	int t=Log[y-x+1];
	return min(f[x][t],f[y-(1<<t)+1][t]);
}

bool Compare(int l1,int r1,int l2,int r2) { //s1<=s2
	int len1=r1-l1+1,len2=r2-l2+1,lcp=LCP(l1,l2);
	if(len1<=len2&&lcp>=len1)return 1;
	if(len1>len2&&lcp>=len2)return 0;
	if(lcp>=len1&&lcp>=len2)return len1<=len2;
	return s[l1+lcp]<=s[l2+lcp];
}

bool Check() {
	int cnt=1,last=n;
	for(int i=n; i>=1; i--) {
		if(s[i]>s[lpos])return 0;
		if(!Compare(i,last,lpos,rpos))cnt++,last=i;
		if(cnt>k)return 0;
	}
	return 1;
}

void Getkth(LL k) {
	LL tmp=sum;
	for(int i=1; i<=n; i++) {
		int now=n-sa[i]-height[i]+1;
		if(now>=k) {lpos=sa[i],rpos=lpos+height[i]+k-1;;break;}
		k-=now;
	}
}

int main() {
	k=Get_Int();
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1; i<=n; i++)a[i]=b[i]=s[i]-'a'+1;
	sort(a+1,a+n+1);
	int tot=unique(a+1,a+n+1)-a-1;
	for(int i=1; i<=n; i++)b[i]=lower_bound(a+1,a+tot+1,b[i])-a;
	build(n,b);
	Log[1]=0;
	for(int i=2; i<=n; i++)Log[i]=Log[i>>1]+1;
	for(int i=1; i<=n; i++)f[i][0]=height[i];
	for(int j=1; j<K; j++)
		for(int i=1; i+(1<<(j-1))<=n; i++)f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	for(int i=1; i<=n; i++)sum+=n-sa[i]-height[i]+1;
	LL Left=1,Right=sum;
	while(Left<=Right) {
		LL mid=(Left+Right)>>1;
		Getkth(mid);
		if(Check())Right=mid-1;
		else Left=mid+1;
	}
	Getkth(Left);
	for(int i=lpos; i<=rpos; i++)putchar(s[i]);
	return 0;
}