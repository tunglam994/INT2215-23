#include<bits/stdc++.h>
using namespace std;
int main()
{
    int steps;
    cin >> steps;
    long minH = LONG_MAX;
    long minV = LONG_MAX;
    long H[steps], V[steps];
    for (int i =0; i<steps; i++)
    {
        cin >> H[i] >> V[i];
        minH = min(minH,H[i]);
        minV = min(minV,V[i]);
    }
    cout << minH*minV;
    return 0;
}
