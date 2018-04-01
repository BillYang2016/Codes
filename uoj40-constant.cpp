#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=131075,K=3;
const double eps=1e-6;

int dcmp(double x) {return fabs(x)<=eps?0:(x>eps?1:-1);}
double sqr(double x) {return x*x;}

int D;

struct Point {
	double d[K],Min[K],Max[K];
	int id;
	int ls,rs;
	bool del;
	double& operator [] (int x) {return d[x];}
	bool operator < (const Point &b) const {return d[D]<b.d[D];}
	bool operator == (const Point &b) const {
		for(int i=0; i<K; i++)if(dcmp(d[i]-b.d[i]))return 0;
		return 1;
	}
} p[maxn];

int pos[maxn];
double ans=0.1;
bool bj=1;

struct KD_Tree {
#define lson p[index].ls
#define rson p[index].rs
	void push_up(int index) {
		for(int i=0; i<K; i++) {
			if(!p[index].del)p[index].Min[i]=p[index].Max[i]=p[index][i];
			else p[index].Min[i]=1e18;
			if(lson) {
				p[index].Min[i]=min(p[index].Min[i],p[lson].Min[i]);
				p[index].Max[i]=max(p[index].Max[i],p[lson].Max[i]);
			}
			if(rson) {
				p[index].Min[i]=min(p[index].Min[i],p[rson].Min[i]);
				p[index].Max[i]=max(p[index].Max[i],p[rson].Max[i]);
			}
		}
	}
	int build(int Left,int Right,int now) {
		int mid=(Left+Right)>>1,root=mid;
		D=now;
		nth_element(p+Left,p+mid,p+Right+1);
		pos[p[mid].id]=root;
		if(Left<mid)p[root].ls=build(Left,mid-1,(now+1)%K);
		if(Right>mid)p[root].rs=build(mid+1,Right,(now+1)%K);
		push_up(root);
		return root;
	}
	int insert(int index,int id,int now) {
		if(!index) {push_up(id);return id;}
		if(p[id][now]<=p[index][now])lson=insert(lson,id,(now+1)%K);
		else rson=insert(rson,id,(now+1)%K);
		push_up(index);
		return index;
	}
	double get_max(int index,Point P) { 
		if(!index)return 0;
		double ans=0;
		for(int i=0; i<K; i++)ans+=max(sqr(p[index].Max[i]-P[i]),sqr(p[index].Min[i]-P[i]));
		return ans;
	}
	double get_min(int index,Point P) {
		if(!index)return 1e18;
		double ans=0;
		for(int i=0; i<K; i++) {
			if(p[index].Min[i]-P[i]>0)ans+=sqr(p[index].Min[i]-P[i]);
			if(P[i]-p[index].Max[i]>0)ans+=sqr(P[i]-p[index].Max[i]);
		}
		return ans;
	}
	double dist(Point a,Point b) { 
		double ans=0;
		for(int i=0; i<K; i++)ans+=sqr(a[i]-b[i]);
		return ans;
	}
	void find(int index,Point P,double r) {
		if(!index||bj||dcmp(get_min(index,P)-r)>0||dcmp(get_max(index,P)-r)<0)return;
		double Dist=dist(p[index],P);
		if(!p[index].del&&dcmp(Dist-r)==0) {ans=p[index].id;bj=1;return;}
		find(lson,P,r);
		find(rson,P,r);
	}
	void erase(int index,Point P,int now) {
		if(p[index]==P) {p[index].del=1;push_up(index);return;}
		if(P[now]<=p[index][now])erase(lson,P,(now+1)%K);
		else erase(rson,P,(now+1)%K);
		push_up(index);
	}
} tree;

int n,m;
double a,b,x,y,i;

double decode(double v,double Left=-100,double Right=100) {
	while(Right-Left>1e-9) {
		double mid=(Left+Right)/2,x=mid*ans+1;
		if(v>x*a-b*sin(x))Left=mid;
		else Right=mid;
	}
	return (Left+Right)/2;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	scanf("%lf%lf",&a,&b);
	for(int i=1; i<=n; i++) {
		for(int j=0; j<K; j++)scanf("%lf",&p[i].d[j]);
		p[i].id=i;
	}
	int root=tree.build(1,n,0);
	while(m--) {
		int opt=Get_Int();
		if(opt==0) {
			scanf("%lf",&i);
			int x=round(decode(i,1,n));
			n++;
			for(int j=0; j<K; j++) {
				scanf("%lf",&y);
				p[n][j]=decode(y);
			}
			tree.erase(root,p[pos[x]],0);
			p[pos[x]=n].id=x;
			tree.insert(root,n,0);
		} else {
			Point P;
			for(int i=0; i<K; i++) {
				scanf("%lf",&y);
				P[i]=decode(y);
			}
			double r;
			scanf("%lf",&r);
			r=sqr(decode(r,0,350));
			bj=0;
			tree.find(root,P,r);
			printf("%d\n",(int)ans);
		}
	}
	return 0;
}