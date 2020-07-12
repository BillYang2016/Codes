#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=105;

struct Student {
	int day,num;
	double temp;
	bool operator < (const Student &b) const {
		int aday=20200418-day,bday=20200418-b.day;
		return aday<bday||(aday==bday&&temp>b.temp)||(aday==bday&&temp==b.temp&&num<b.num);
	}
} a[maxn];

int n;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i].day=Get_Int();
		a[i].num=Get_Int();
		scanf("%lf",&a[i].temp);
		if(a[i].temp<38.0) {i--;n--;}
	}
	sort(a+1,a+n+1);
	printf("%d\n",n);
	for(int i=1; i<=n; i++)printf("%d %d %.1lf\n",a[i].day,a[i].num,a[i].temp);
	return 0;
}