//Ordered
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int x, y, z;
    cin >> x >> y >> z;
    bool b;
    if ((x-y)*(y-z)>=0) b= true;
    else b = false;
    cout << b;
    return 0;
}
