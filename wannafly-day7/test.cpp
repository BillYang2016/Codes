#include <bits/stdc++.h>
#define mp make_pair
#define sqr(x) (x)*(x)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int maxn=100007;
const ll inf=1<<29;
ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
const ll mod=998244353;
inline ll solve(ll n,ll m,ll x){
    ll xm=x%mod,now=xm*(xm+1)/2%mod;
    if(x<=m) return now;
    else{
        x-=m;
        ll t=((x/(n-1))%mod)*((n-1)*(n+2)/2%mod)%mod;
        ll zz=x%(n-1);
        now=m*(m+1)/2%mod;
        return (((zz+1)*(zz+2)/2+mod-1)%mod+t+now)%mod;
    }
}
int main(){
    ll pow2=(mod+1)/2;
    int t=read();
    while(t--){
        ll n=read(),m=read(),x=read(),y=read();ll K=read();
        ll km=K%mod;
        if(n>1&&m>1){
            if(K<=n*m){
                printf("%lld\n",km*(km+1)/2%mod);
            }
            else{
                ll x=n*m%mod;
                printf("%lld\n",(((K-n*m)%mod)*x%mod+x*(x+1)/2%mod)%mod);
            }
        }
        else if(m>1){
            printf("%lld\n",solve(m,max(m-y+1,y),K)%mod);
        }
        else if(n>1){
            printf("%lld\n",solve(n,max(n-x+1,x),K)%mod);
        }
        else printf("%lld\n",km);
    }
    return 0;
}
