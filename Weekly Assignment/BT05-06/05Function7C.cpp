#include<bits/stdc++.h>
using namespace std;

void printTriangle(int n)
{
    for (int i = 0; i< n; i++)
    {
        for (int j = -n + 1; j <= n-1; j++)
        {
            if ( abs(j) > i) cout << ' ';
            else cout << '*';
        }
        cout << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    printTriangle(n);
    return 0;
}
