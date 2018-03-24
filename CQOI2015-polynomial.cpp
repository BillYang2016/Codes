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

const int BASE=100000000,WIDTH=8;

struct BigInteger {
	vector<LL> s;
	BigInteger(LL num=0) {*this=num;}
	//赋值
	BigInteger operator = (LL num) {
		s.clear();
		do {
			s.push_back(num%BASE);
			num/=BASE;
		} while(num);
		return *this;
	}
	BigInteger operator = (const string &str) {
		s.clear();
		LL x;
		int len=(str.length()-1)/WIDTH+1;
		for(int i=0; i<len; i++) {
			int end=str.length()-i*WIDTH,start=max(0,end-WIDTH);
			sscanf(str.substr(start,end-start).c_str(),"%lld",&x);
			s.push_back(x);
		}
		return *this;
	}
	//+
	BigInteger operator + (BigInteger b) {
		BigInteger c;c.s.clear();
		LL g=0;
		for(int i=0; g||i<s.size()||i<b.s.size(); i++) {
			g+=(i<s.size()?s[i]:0)+(i<b.s.size()?b.s[i]:0);
			c.s.push_back(g%BASE);
			g/=BASE;
		}
		return c;
	}
	void operator += (BigInteger b) {*this=*this+b;}
	BigInteger operator + (const LL &b) {
		BigInteger c=b;
		c+=*this;
		return c;
	}
	void operator += (const LL &b) {*this=*this+b;}
	//-
	BigInteger operator - (BigInteger b) {
		BigInteger a=*this;
		for(int i=0; i<a.s.size(); i++) {
			LL tmp=i<b.s.size()?b.s[i]:0;
			if(a.s[i]<tmp) {a.s[i+1]--;a.s[i]+=BASE;}
			a.s[i]-=tmp;
		}
		while(!a.s.back()&&a.s.size()>1)a.s.pop_back();
		return a;
	}
	void operator -= (BigInteger b) {*this=*this-b;}
	BigInteger operator - (const LL &b) {
		BigInteger a=*this;
		a-=BigInteger(b);
		return a;
	}
	void operator -= (const LL &b) {*this=*this-b;}
	//*
	BigInteger operator * (const LL &b) {
		if(b==0)return 0;
		BigInteger c;c.s.clear();
		for(int i=0; i<s.size(); i++)c.s.push_back(s[i]*b);
		for(int i=0; i<c.s.size()-1; i++)c.s[i+1]+=c.s[i]/BASE,c.s[i]%=BASE;
		while(c.s.back()>=BASE) {LL now=c.s.back();c.s.back()%=BASE;c.s.push_back(now/BASE);}
		return c;
	}
	void operator *= (const LL &b) {*this=*this*b;}
	BigInteger operator * (const BigInteger &b) {
		BigInteger c;c.s.resize(s.size()+b.s.size());
		for(int i=0; i<s.size(); i++)
			for(int j=0; j<b.s.size(); j++)c.s[i+j]+=s[i]*b.s[j];
		for(int i=0; i<c.s.size()-1; i++)c.s[i+1]+=c.s[i]/BASE,c.s[i]%=BASE;
		while(!c.s.back()&&c.s.size()>1)c.s.pop_back();
		return c;
	}
	void operator *= (const BigInteger &b) {*this=*this*b;}
	// /
	BigInteger Divide(BigInteger a,const LL &b,LL &d) { //'/'&'%'
		for(int i=a.s.size()-1; i>=0; i--)d=d*BASE+a.s[i],a.s[i]=d/b,d%=b;
		while(!a.s.back()&&a.s.size()>1)a.s.pop_back();
		return a;
	}
	BigInteger operator / (LL b) {LL d=0;return Divide(*this,b,d);}
	void operator /= (const LL &b) {*this=*this/b;}
	//%
	LL operator % (const LL &b) {LL d=0;Divide(*this,b,d);return d;}
	void operator %= (const LL &b) {*this=*this%b;}
	friend istream& operator >> (istream& input,BigInteger& x) {
		string s;
		if(!(input>>s))return input;
		x=s;
		return input;
	}
	friend ostream& operator << (ostream& output,const BigInteger& x) {
		output<<x.s.back();
		for(int i=x.s.size()-2; i>=0; i--) {
			char buf[20];
			sprintf(buf,"%08lld",x.s[i]);
			for(int j=0; j<strlen(buf); j++)output<<buf[j];
		}
		return output;
	}
};

const int mod=3389;

LL Quick_Pow(LL a,LL b,LL mod) {
	int ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

LL inv(LL x) {return Quick_Pow(x,mod-2,3389);}

LL Cala(BigInteger x) {
	if(x.s.empty())return 1;
	return (Quick_Pow(1234,x%3388,3389)+5678*inv(1233)%mod*(Quick_Pow(1234,x%3388,3389)-1+mod)%mod)%mod;
}

LL t;
BigInteger n,m,ans=0;

int main() {
	cin>>n>>t>>m;
	int delta=(n-m).s.back();
	BigInteger C=1,pow=1;
	for(int i=0; i<=delta; i++) {
		ans+=C*Cala(m+i)*pow;
		C=C*(m+i+1)/(i+1);
		pow*=t;
	}
	cout<<ans<<endl;
	return 0;
}