#include<bits/stdc++.h>
using namespace std;
int decTobin (int dec)
{
    int bin = 0;
    int cnt = 0;
    while ( dec > 0 )
    {
        bin = bin + (dec%2)*pow (10, cnt);
        dec /= 2;
        cnt++;
    }
    return bin;
}
int binTodec (int bin)
{
    int dec = 0;
    int cnt = 0;
    while ( bin > 0 )
    {
        dec = dec + (bin%10)*pow (2, cnt);
        bin /= 10;
        cnt++;
    }
    return dec;
}
int main()
{
    int n;
    cin >> n;
    cout << decTobin(n) << endl << binTodec(decTobin(n));
    return 0;
}
