#include <bits/stdc++.h>
using namespace std;
int main ()
{
	int m, n;
	cin >> m >> n;
	char a[m], b[n];
	for (int i = 0; i < m; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	int cnt = 0;
	for (int i = 0; i < n - m + 1; i++)
	{
		char temp[m];
		for (int k = 0; k < m; k++) temp[k] = b[k + i];
		if(strcmp(temp, a) == 0) cnt++;
	}
	cout << cnt;
	return 0;
}
