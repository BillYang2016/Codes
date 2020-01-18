#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n,a,b,c,d;
char s[1005];

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		a=Get_Int(); //普通
		b=Get_Int(); //圣盾
		c=Get_Int(); //普通嘲讽
		d=Get_Int(); //圣盾嘲讽
		int Max=0,Min=0,ra=a,rb=b,rc=c,rd=d;
		scanf("%s",s+1);
		for(int i=1; i<=n; i++) {
			if(rc||rd) {
				if(s[i]=='1'&&rc) {
					Max++;
					rc--;
				} else if(rd) {
					rd--;
					rc++;
				}
			} else {
				if(s[i]=='1'&&ra) {
					Max++;
					ra--;
				} else if(rb) {
					rb--;
					ra++;
				}
			}
		}
		ra=a,rb=b,rc=c,rd=d;
		for(int i=1; i<=n; i++) {
			if(rc||rd) {
				if(s[i]=='1'&&!rd) {
					Min++;
					rc--;
				} else if(s[i]=='1') {
					rd--;
					rc++;
				}
				if(s[i]=='0'&&!rc) {
					rd--;
					rc++;
				}
			} else {
				if(!ra&&!rb)break;
				if(s[i]=='1'&&!rb) {
					Min++;
					ra--;
				} else if(s[i]=='1') {
					rb--;
					ra++;
				}
				if(s[i]=='0'&&!ra) {
					rb--;
					ra++;
				}
			}
		}
		printf("%d %d\n",Max,Min);
	}
	return 0;
}