#include <bits/stdc++.h>
using namespace std;
int main ()
{
	int n;
	cin >> n;
	int a[n], k;
	for (int i = 0; i < n; i++) cin >> a[i];
	cin >> k;
	int* l = a;
	int *r = a + sizeof(a) - 1;
	int* m;
	while(l < r)
	{
		m = l + (r - l)/2;
		if(k > *m) l = m + 1;
		else r = m;
	}
	if (k == *l) cout << "yes";
	else cout << "no";
	return 0;
}
