#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int Month[] {0,31,28,31,30,31,30,31,31,30,31,30,31};

bool Check(int year) {return (year%4==0&&year%100)||(year%400==0);}

int CalWeekDay(int y,int m,int d) {
	if(m==1||m==2) {m+=12;y--;}
	int Week=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
	return Week+1;
} 

int main() {
	int t=Get_Int();
	while(t--) {
		int ny=Get_Int(),nm=Get_Int(),nd=Get_Int();
		int y=ny,m=5,d=1,cnt=0,mm=0,md=0,fm=0,fd=0;
cal:
		if(CalWeekDay(y,m,d)==7)cnt++;
		while(true) {
			d++;
			if(Check(y))Month[2]=29;
			else Month[2]=28;
			if(d>Month[m]) {d=1;m++;}
			if(m>12) {m=1;y++;}
			if(CalWeekDay(y,m,d)==7)cnt++;
			if(cnt==2) {mm=m;md=d;break;}
		}
		cnt=0;
		m=6;
		d=1;
		if(CalWeekDay(y,m,d)==7)cnt++;
		while(true) {
			d++;
			if(Check(y))Month[2]=29;
			else Month[2]=28;
			if(d>Month[m]) {d=1;m++;}
			if(m>12) {m=1;y++;}
			if(CalWeekDay(y,m,d)==7)cnt++;
			if(cnt==3) {fm=m;fd=d;break;}
		}
		if(nm>fm||(nm==fm&&nd>=fd)) {y=ny+1;nm=1;nd=1;m=5;d=1;cnt=0;goto cal;}
		if(nm<mm||(nm==mm&&nd<md)) {
			if(md%10==1&&md/10!=1)printf("Mother's Day: May %dst, %d\n",md,y);
			else if(md%10==2&&md/10!=1)printf("Mother's Day: May %dnd, %d\n",md,y);
			else if(md%10==3&&md/10!=1)printf("Mother's Day: May %drd, %d\n",md,y);
			else printf("Mother's Day: May %dth, %d\n",md,y);
		} else {
			if(fd%10==1&&fd/10!=1)printf("Father's Day: June %dst, %d\n",fd,y);
			else if(fd%10==2&&fd/10!=1)printf("Father's Day: June %dnd, %d\n",fd,y);
			else if(fd%10==3&&fd/10!=1)printf("Father's Day: June %drd, %d\n",fd,y);
			else printf("Father's Day: June %dth, %d\n",fd,y);
		}
	}
	return 0;
}