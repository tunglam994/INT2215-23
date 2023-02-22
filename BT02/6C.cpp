#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    for (int i=0; i<=n-1; i++)
    {
        for (int j=1; j<=n; j++)
        {
            if (j+i>n) cout<< j+i-n << ' ';
            else cout << j+i << ' ';
        }
        cout << endl;
    }
    return 0;
}
