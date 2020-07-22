#include<bits/stdc++.h>

using namespace std;

const int n=11;
int Scores[]= {95,90,85,80,75,70,67,65,62,60,0};
double Points[]= {4.3,4.0,3.7,3.3,3.0,2.7,2.3,2.0,1.7,1.0,0};

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int x;
		scanf("%d",&x);
		double ans=0;
		for(int a=0; a<11; a++)
			for(int b=0; b<11; b++)
				for(int c=0; c<11; c++)
					for(int d=0; d<11; d++)
						if(Scores[a]+Scores[b]+Scores[c]+Scores[d]<=x)ans=max(ans,Points[a]+Points[b]+Points[c]+Points[d]);
		printf("%.1lf\n",ans);
	}
	return 0;
}