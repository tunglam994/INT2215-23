#include<bits/stdc++.h>
using namespace std;
int getRandlower (int n)
{
    return rand()%n;
}
int main()
{
    srand((unsigned int)time(NULL));
    int n;
    cin >> n;
    cout << getRandlower (n);
    return 0;
}
