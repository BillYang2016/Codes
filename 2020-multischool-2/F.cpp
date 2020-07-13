#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>
using namespace std;
const int N = 5e3 + 5;
int t[N][N];
int ans[N][N];
deque<int> win(N);

// 标准的滑动窗口
void solve1(int n, int len, int *arr, int *ans) {
	win.clear();
    for(int i = 0; i < n; i ++) {
        while(!win.empty() && arr[win.back()] < arr[i])
			win.pop_back();
		while(!win.empty() && win.front() < i - len + 1)
			win.pop_front();
		win.push_back(i);
		if(i + 1 >= len)
			ans[i - len + 1] = arr[win.front()];
    }
}


int main() {
    ios::sync_with_stdio(false);
	int m, n, a, b, k;
    cin >> n >> m >> k;
	a=k;b=k;
    for(int i = 0; i < m; i ++)
        for(int j = 0; j < n; j ++)
            t[i][j]=(i+1)/__gcd(i+1,j+1)*(j+1);
	for(int i = 0; i < m; i ++)
		solve1(n, b, t[i], ans[i]);

    // 遍历每列
    // 第二次用作滑动窗口的数组是经过第一次处理后的
	int len = a;
	for(int i = 0; i < n; i ++) {
		win.clear();
		for(int j = 0; j < m; j ++) {
			while(!win.empty() && ans[win.back()][i] < ans[j][i])
				win.pop_back();
			while(!win.empty() && win.front() < j - len + 1)
				win.pop_front();
			win.push_back(j);
			if(j + 1 >= len)
				ans[j - len + 1][i] = ans[win.front()][i];
		}
	}

	long long sum=0;

	for(int i = 0; i < m - a + 1; i ++)
		for(int j = 0; j < n - b + 1; j ++)sum+=ans[i][j];
		
	printf("%lld\n",sum);
	return 0;
}