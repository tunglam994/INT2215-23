#include <bits/stdc++.h>
using namespace std;

int rndUsingceilfloor(double n)
{
    int c = ceil(n);
    int f = floor(n);
    if ( c - n <= n - f ) return c;
    return f;
}

int rnd (double n)
{
    int f = n/1;
    if ( n - f >= f+1-n ) return f+1;
    return f;
}

int main()
{
    double n;
    cin >> n;
    cout << rndUsingceilfloor(n) << ' ' << rnd(n);
}
