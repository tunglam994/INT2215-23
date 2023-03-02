#include<bits/stdc++.h>
using namespace std;


int main() {

    int n, m, Count;
    cin >> n >> m;
    string s;
    cin >> s;
    int i[m], j[m], l[m], rT[m];
    for (int a=0; a<m; a++)
    {
        cin >> i[a] >> j[a];
        l[a] = j[a] - i[a] + 1;
        Count = 0;
        for (int b= i[a]-1; b<= n-l[a]; b++)
        {
            if (s[b]!=s[b+l[a]]) break;
            Count ++;
        }
        rT[a] = (Count/l[a]) + 1;
    }
    for (int a=0; a<m; a++)
    {
        cout << rT[a] << endl;
    }
    return 0;
}

