#include <bits/stdc++.h>
#define mp make_pair
#define sqr(x) (x)*(x)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
typedef int int_;
#define int long long
const int maxn=1000007;
const ll inf=0x3f3f3f3f;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
const int mod=1e9+7;
int pown(int a,int b){
    int ans=1;
    while(b){
        if(b&1) ans=(1LL*ans*a)%mod;
        a=(1LL*a*a)%mod;
        b>>=1;
    }
    return ans;
}
int add(int x,int y){
    x+=y;
    if(x>=mod) x%=mod;
	return x;
}
int mul(int x,int y){
    return 1LL*x*y%mod;
}
int dec(int x,int y){
    x-=y;if(x<0) x+=mod;
    return x;
}
int fac[maxn],inv[maxn];
int C(int a,int b){
    if(a<b) return 0;
    return 1LL*fac[a]*inv[b]%mod*inv[a-b]%mod;
}
struct node{
    int l,r;
    bool operator < (node x) const{
        return r<x.r;
    }
}nd[maxn];
int pre2[maxn],pre6[maxn],pre10[maxn];
int pren0[maxn],pren3[maxn],pren[maxn];
vector<int> g[maxn];
int dp[maxn][4];
int_ main(){
    pre2[0]=pre6[0]=1,pre10[0]=1;
    for(int i=1;i<=100000;i++){
        pre2[i]=mul(pre2[i-1],2);
        pre6[i]=mul(pre6[i-1],6);
        pre10[i]=mul(pre10[i-1],10);
    }
    fac[0]=inv[0]=1;
    int N=1000000;
    for(int i=1;i<=N;i++) fac[i]=1LL*fac[i-1]*i%mod;
    inv[N]=pown(fac[N],mod-2);
    for(int i=N-1;i;i--) inv[i]=1LL*inv[i+1]*(i+1)%mod;
    pren[0]=1;
    for(int i=1;i<=100000;i++){
        pren[i]=pre6[i];
        pren3[i]=add(mul(pren3[i-1],6),mul(pren[i-1],2));
        pren0[i]=add(mul(pren0[i-1],10),add(mul(pren3[i-1],4),mul(pren[i-1],2)));
    }
    int top=0;
    int n,m;
    while(scanf("%lld%lld",&n,&m)==2){
        for(int i=1;i<=m;i++){
            int l=read();
			int r=read();
            nd[i].l=l;nd[i].r=r;
        }
        sort(nd+1,nd+m+1);
        int mx=0;
        node last;last.l=last.r=0;
        int ans=1;top=0;
        node Last;
        for(int i=1;i<=m;i++){
            if(nd[i].l<=mx){
                continue;
            }
            if(!last.l||nd[i].l>last.r){
                if(last.l) ans=mul(ans,pre10[nd[i].l-last.r-1]);
                else ans=mul(ans,pre10[nd[i].l-1]);
                ++top;g[top].clear();
                g[top].push_back(0);
                g[top].push_back(0);
                Last=node{nd[i].l,nd[i].r};
            }
            else{
                g[top].push_back(nd[i].l-Last.l);
                g[top].push_back(Last.r-nd[i].l+1);
                Last=node{Last.r+1,nd[i].r};
            }
            last=nd[i];
            mx=max(mx,nd[i].l);
        }
        ans=mul(ans,pre10[n-last.r]);
        g[top].push_back(Last.r-Last.l+1);
        g[top].push_back(0);
        for(int i=1;i<=top;i++){
            int len=g[i].size()-1;
            dp[1][0]=1;dp[1][1]=0;dp[1][2]=0;
            for(int k=2;k<=len;k++){
                int x=g[i][k];
                if(k%2==0){
                    dp[k][2]=add(mul(dp[k-1][2],pre10[x]),add(mul(dp[k-1][1],add(pren0[x],pren3[x])),mul(dp[k-1][0],pren0[x])));
                    dp[k][1]=add(mul(dp[k-1][1],pren[x]),mul(dp[k-1][0],pren3[x]));
                    dp[k][0]=mul(dp[k-1][0],pren[x]);
                }
                else{
                    dp[k][2]=mul((0LL+dp[k-1][0]+dp[k-1][1]+dp[k-1][2])%mod,pren0[x]);
                    dp[k][1]=mul(add(dp[k-1][1],dp[k-1][2]),pren3[x]);
                    dp[k][0]=mul(dp[k-1][2],pren[x]);
                }
            }
      //      cout<<len<<" "<<dp[len][0]<<" "<<dp[len][1]<<" "<<dp[len][2]<<" "<<dp[2][2]<<" "<<pren[2]<<endl;
            ans=mul(ans,(0LL+dp[len][0]+dp[len][1]+dp[len][2])%mod);
        }
        printf("%lld\n",ans);
    }
    return 0;
}