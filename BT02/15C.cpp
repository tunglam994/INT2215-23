#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int f1=1, f2=1;
    int fn = f1+f2;
    vector <int> f;
    f.push_back(f1);
    f.push_back(f2);
    while (fn<=n)
    {
        fn = f1+f2;
        if (fn>n) continue;
        f.push_back(fn);
        f1=f2;
        f2=fn;
    }
    if (f2!=n&&fn!=n) cout <<"Khong thuoc day Fibonacci"<<endl;
    else cout << "Thuoc day Fibonacci"<< endl;
    int s = f.size();
    for (int i=0; i<s; i++) cout << f[i] <<' ';
    return 0;
}
