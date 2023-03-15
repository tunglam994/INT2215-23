#include <bits/stdc++.h>
using namespace std;
void f(char a[])
{
	cout << sizeof(a);
}
int main ()
{
	char b[10];
	cout << sizeof(b) << endl; //10 => kich co cua mang
	f(b); // 8 => kich co cua pointer
	return 0;
}
