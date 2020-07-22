#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,maxb=320;

int belong2[maxn],cnt_block[maxb][maxb],cnt[maxb][maxn],Left[maxb],Right[maxb];
int num_block=0,belong1[maxn];
int n,m,a[maxn];
vector<int> edges[maxn],Big[maxn];

void Modify(int x,int val,int opt) {
	val++;
	if(val>n)return;
	if(cnt[x][val]==0&&opt==1)cnt_block[x][belong2[val]]++;
	if(cnt[x][val]==1&&opt==-1)cnt_block[x][belong2[val]]--;
	cnt[x][val]+=opt;
}

int Mex(int x) {
	for(int i=1; i<=belong2[n]; i++) {
		if(cnt_block[x][i]==Right[x]-Left[x]+1)continue;
		for(int j=Left[i]; j<=Right[i]; j++)if(!cnt[x][j])return j-1;
	}
	return n;
}

void Clear() {
	for(int i=1; i<=n; i++) {
		edges[i].clear();
		Big[i].clear();
		Left[i]=Right[i]=0;
	}
	num_block=0;
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		int size=sqrt(n);
		Clear();
		for(int i=1; i<=n; i++) {
			a[i]=Get_Int();
			belong2[i]=(i-1)/size+1;
			if(!Left[belong2[i]])Left[belong2[i]]=i;
			Right[belong2[i]]=i;
		}
		for(int i=1; i<=m; i++) {
			int x=Get_Int(),y=Get_Int();
			edges[x].push_back(y);
			edges[y].push_back(x);
		}
		for(int i=1; i<=n; i++)if(edges[i].size()>size) {
			belong1[i]=++num_block;
			for(int j=1; j<=belong2[n]; j++)cnt_block[num_block][j]=0;
			for(int j=1; j<=n; j++)cnt[num_block][j]=0;
		}
		for(int x=1; x<=n; x++)
			for(int y:edges[x])if(edges[y].size()>size) {
				Modify(belong1[y],a[x],1);
				Big[x].push_back(y);
			}
		int q=Get_Int();
		while(q--) {
			int opt=Get_Int();
			if(opt==1) {
				int x=Get_Int(),v=Get_Int();
				for(int y:Big[x]) {
					Modify(belong1[y],a[x],-1);
					Modify(belong1[y],v,1);
				}
				a[x]=v;
			} else {
				int x=Get_Int();
				if(edges[x].size()<=size) {
					vector<int> tmp;
					for(int y:edges[x])tmp.push_back(a[y]);
					sort(tmp.begin(),tmp.end());
					int mex=0;
					for(int v:tmp)
						if(v==mex)mex++;
						else break;
					printf("%d\n",mex);
				} else printf("%d\n",Mex(belong1[x]));
			}
		}
	}
	return 0;
}
