#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int T[n];
    for (int i=0; i<n; i++)
    {
        cin >> T[i];
    }
    for (int j=n; j>=1; j--)
    {
        for (int i=0; i<j-1; i++)
        {
            if (T[i]>=T[i+1]) swap(T[i],T[i+1]);
        }
    }
    int time = 0;

    for (int i=0; i<n; i++)
    {

        time += T[i]*(n-i-1);
    }
    cout << time;
    return 0;
}
