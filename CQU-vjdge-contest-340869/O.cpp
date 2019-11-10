#include<bits/stdc++.h>

using namespace std;

struct Square { //WA
	double x1,x2,y1,y2;
	Square(double a,double b,double c,double d):x1(a),x2(b),y1(c),y2(d) {}
};

vector<Square> a;

void Add(double aa,double b,double c,double d) {a.push_back(Square(aa,b,c,d));}

void Cut(int id,double x1,double x2,double y1,double y2,int type) {
	if(type==1) {
		double k1=max(x1,a[id].x1),k2=min(x2,a[id].x2);
		if(a[id].x1<k1)Add(a[id].x1,k1,a[id].y1,a[id].y2);
		if(a[id].x2>k2)Add(k2,a[id].x2,a[id].y1,a[id].y2);
		Cut(id,k1,k2,y1,y2,2);
	} else {
		double k1=max(y1,a[id].y1),k2=min(y2,a[id].y2);
		if(a[id].y1<k1)Add(x1,x2,a[id].y1,k1);
		if(a[id].y2>k2)Add(x1,x2,k2,a[id].y2);
	}
}

int main() {
	int t=0,n;
	while(scanf("%d",&n)) {
		if(n==0)break;
		a.clear();
		for(int i=1; i<=n; i++) {
			double x1,x2,y1,y2;
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			for(int j=0; j<a.size(); j++) {
				Square &s=a[j];
				if(x1>=s.x2||x2<=s.x1||y1>=s.y2||y2<=s.y1)continue;
				Cut(j,x1,x2,y1,y2,1);
				s=a.back();
				a.pop_back();
				j--;
			}
			Add(x1,x2,y1,y2);
			puts("...");
		}
		double ans=0;
		for(auto s:a)ans+=(s.x2-s.x1)*(s.y2-s.y1);
		printf("Test case #%d\n",++t);
		printf("Total explored area: %.2lf\n\n",ans);
	}
	return 0;
}