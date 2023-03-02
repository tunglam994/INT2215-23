#include <bits/stdc++.h>
using namespace std;
int main()
{
    string f0, f1, f;
    f0 = "a";
    f1 = "b";
    cout << f0 << ' ' << f1 << ' ';
    for (int i = 2; i<=10; i++)
    {
        f = f1 + f0;
        f0 = f1;
        f1 = f;
        cout << f << ' ';
    }
    return 0;
}
