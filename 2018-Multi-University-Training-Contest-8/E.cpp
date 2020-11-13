#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

char a[5][5];

void Rotate(int num,char dir) {
	int xpos=(num>2)+1,ypos=(!(num&1))+1;
	char &m_lu=a[xpos][ypos],&m_ru=a[xpos][ypos+1],&m_ld=a[xpos+1][ypos],&m_rd=a[xpos+1][ypos+1];
	char lu=a[xpos][ypos],ru=a[xpos][ypos+1],ld=a[xpos+1][ypos],rd=a[xpos+1][ypos+1];
	if(dir=='C') { //clockwise
		m_lu=ld;
		m_ru=lu;
		m_rd=ru;
		m_ld=rd;
	} else {
		m_lu=ru;
		m_ld=lu;
		m_rd=ld;
		m_ru=rd;
	}
}

int main() {
	int t=Get_Int();
	while(t--) {
		int m=Get_Int();
		for(int i=1; i<=3; i++)scanf("%s",a[i]+1);
		while(m--) {
			char opt[5];
			scanf("%s",opt);
			Rotate(opt[0]-'0',opt[1]);
		}
		for(int i=1; i<=3; i++)printf("%s\n",a[i]+1);
	}
	return 0;
}