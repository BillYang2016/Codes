#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>

using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=7005;

struct Matrix {
	int x1,y1,x2,y2;
};

int n,BCC,father[maxn];

int Get_Father(int x) {
	if(father[x]==x)return x;
	return father[x]=Get_Father(father[x]);
}

bool Intersect(Matrix a,Matrix b) {
	return a.x2>=b.x1&&b.x2>=a.x1&&a.y2>=b.y1&&b.y2>=a.y1&&((a.x2!=b.x1&&b.x2!=a.x1)||(a.y2!=b.y1&&b.y2!=a.y1));
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i].x1=Get_Int();
		a[i].y1=Get_Int();
		a[i].x2=Get_Int();
		a[i].y2=Get_Int();
		father[i]=i;
	}
	BCC=n;
	for(int i=1; i<=n; i++)
		for(int j=i+1; j<=n; j++)
			if(Intersect(a[i],a[j])) {
				int fx=Get_Father(i),fy=Get_Father(j);
				if(fx==fy)continue;
				father[fx]=fy;
				BCC--;
			}
	printf("%d\n",BCC);
	return 0;
}