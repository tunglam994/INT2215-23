#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;

    cin >> n;
    int f1=n;
    cout << f1 <<' ';
    while (n>-1)
    {
        cin >> n;
        if (n==f1 ) continue;
        f1 = n;
        cout << n <<' ';
    }
    return 0;
}
