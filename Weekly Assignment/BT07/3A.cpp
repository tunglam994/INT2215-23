#include <bits/stdc++.h>
using namespace std;
void count_even(int* a, int n)
{
	int count = 0;
	for(int i = 0; i < n; i++)
	{
		if(*(a + i) % 2 == 0) count++;
	}
	cout << count << endl;
}
int main ()
{
	int test[10];
	for (int i = 0; i<10; i++)
    {
        cin >> test[i];
    }
	count_even(test, 5);
	count_even(test + 5, 5);
	return 0;
}
