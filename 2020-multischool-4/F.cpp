#include<bits/stdc++.h>

using namespace std;

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int AC,AD,BC,BD;
		scanf("%d%d%d%d",&AC,&AD,&BC,&BD);
		if(AC>AD) {
			if(BC>BD) {
				if(AC<BC)puts("AB//CD");
				else puts("AB//DC");
			} else {
				puts("AB//DC");
			}
		} else {
			if(BC>BD) {
				puts("AB//CD");
			} else {
				if(AD>BD)puts("AB//CD");
				else puts("AB//DC");
			}
		}
	}
	return 0;
}