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

int n,a[maxn],tmp[maxn];

void Merge_Sort(int Left,int Right) {
	if(Left==Right)return;
	int mid=(Left+Right)>>1;
	Merge_Sort(Left,mid);
	Merge_Sort(mid+1,Right);
	int l=Left,r=mid+1,cnt=0;
	while(l<=mid&&r<=Right) {
		if(a[l]<a[r])tmp[++cnt]=a[l++];
		else tmp[++cnt]=a[r++];
	}
	while(l<=mid)tmp[++cnt]=a[l++];
	while(r<=Right)tmp[++cnt]=a[r++];
	for(int i=1; i<=cnt; i++)a[Left+i-1]=tmp[i];
}

int main() {
	cin>>n;
	for(int i=1; i<=n; i++)cin>>a[i];
	Merge_Sort(1,n);
	for(int i=1; i<=n; i++)cout<<a[i]<<" ";
	return 0;
}