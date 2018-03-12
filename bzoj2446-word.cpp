#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=505;

char a[maxn][8],s1[2005],s2[2005],s[8],useless[8];
int n,m,f[maxn][2005],son[maxn][2],len[maxn],H[maxn];

int Hash(char *s) {
	int len=strlen(s),sum=0;
	for(int i=0; i<5; i++)sum=sum*27+(i<len?s[i]-'A'+1:0);
	return sum;
}

int Dp(int x,int y) {
	if(~f[x][y])return f[x][y];
	if(son[x][0])return f[x][y]=Dp(son[x][1],Dp(son[x][0],y));
	int j=y;
	for(int i=0; i<len[x]&&j<m; i++)if(a[x][i]==s2[j])j++;
	return f[x][y]=j;
}

int main() {
	int t=Get_Int();
	while(t--) {
		memset(f,-1,sizeof(f));
		n=Get_Int();
		for(int i=1; i<=n; i++) {
			scanf("%s%s%s",s,useless,a[i]);
			H[i]=Hash(s);
			if(isupper(a[i][0]))scanf("%s%s",useless,s),son[i][0]=Hash(a[i]),son[i][1]=Hash(s);
			else son[i][0]=0,len[i]=strlen(a[i]);
		}
		for(int i=1; i<=n; i++)if(son[i][0])
			for(int j=0; j<2; j++)
				for(int k=1; k<=n; k++)
					if(son[i][j]==H[k]) { //build DAG
						son[i][j]=k;
						break;
					}
		scanf("%s%s",s1,s2);
		m=strlen(s2);
		int h=Hash(s1);
		for(int i=1; i<=n; i++)if(H[i]==h) {puts(Dp(i,0)<m?"NO":"YES");break;}
	}
	return 0;
}