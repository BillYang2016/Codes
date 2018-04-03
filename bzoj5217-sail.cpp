#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

struct cp {
	double x,y;
	cp(double x=0,double y=0):x(x),y(y) {}
	cp operator + (const cp &b) const {return cp(x+b.x,y+b.y);}
	void operator += (const cp &b) {*this=*this+b;}
	cp operator - (const cp &b) const {return cp(x-b.x,y-b.y);}
	cp operator * (const cp &b) const {return cp(x*b.x-y*b.y,x*b.y+y*b.x);}
	void operator *= (const cp &b) {*this=*this*b;}
	cp operator / (const double &b) const {return cp(x/b,y/b);}
	void operator /= (const double &b) {*this=*this/b;}
};

cp conj(cp a) {return cp(a.x,-a.y);}

const int maxn=1048576+5;
const double pi=acos(-1);

struct FastFourierTransform {
	int n,rev[maxn];
	cp omega[maxn],iomega[maxn];
	void init(int n) {
		this->n=n;
		for(int i=0; i<n; i++) {
			omega[i]=cp(cos(2*pi/n*i),sin(2*pi/n*i));
			iomega[i]=conj(omega[i]);
		}
		int k=log2(n);
		for(int i=0; i<n; i++) {
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=1<<(k-j-1);
			rev[i]=t;
		}
	}
	void transform(cp *a,cp *omega) {
		for(int i=0; i<n; i++)if(i<rev[i])swap(a[i],a[rev[i]]); //no double reversion
		for(int len=2; len<=n; len*=2) {
			int mid=len>>1;
			for(cp *p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					cp t=omega[n/len*i]*p[mid+i];
					p[mid+i]=p[i]-t;
					p[i]+=t;
				}
		}
	}
	void dft(cp *a) {
		transform(a,omega);
	}
	void idft(cp *a) {
		transform(a,iomega);
		for(int i=0; i<n; i++)a[i]/=n;
	}
} fft;

#define pii pair<int,int>

const int dx[]= {1,-1,0,0},dy[]= {0,0,1,-1};

int n,m,minx=700,maxx,miny=700,maxy,vst[705][705];
char mp[705][705];
cp a[maxn],b[maxn];

void Bfs(int sx,int sy) {
	queue<pii> Q;
	Q.push(pii(sx,sy));
	vst[sx][sy]=0;
	while(!Q.empty()) {
		int x=Q.front().first,y=Q.front().second;
		Q.pop();
		a[(x-1)*m+y-1]=cp(1,0);
		for(int i=0; i<4; i++) {
			int nx=x+dx[i],ny=y+dy[i];
			if(vst[nx][ny]) {vst[nx][ny]=0;Q.push(pii(nx,ny));}
		}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)scanf("%s",mp[i]+1);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(mp[i][j]=='o')minx=min(minx,i),miny=min(miny,j),maxx=max(maxx,i),maxy=max(maxy,j);
			else if(mp[i][j]=='#')a[(n-i+1)*m-j]=cp(1,0);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(mp[i][j]=='o')b[(i-minx)*m+j-miny]=cp(1,0);
	int t=1;
	while(t<n*m*2)t<<=1;
	fft.init(t);
	fft.dft(a),fft.dft(b);
	for(int i=0; i<t; i++)a[i]*=b[i];
	fft.idft(a);
	for(int i=1; i<=n-(maxx-minx); i++)
		for(int j=1; j<=m-(maxy-miny); j++)
			if(!round(a[(n-i+1)*m-j].x))vst[i][j]=1;
	fill(a,a+t,0);
	Bfs(minx,miny);
	fft.dft(a);
	for(int i=0; i<t; i++)a[i]*=b[i];
	fft.idft(a);
	int ans=0;
	for(int i=0; i<n*m; i++)ans+=round(a[i].x)>0;
	printf("%d\n",ans);
	return 0;
}