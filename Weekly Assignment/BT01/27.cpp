#include<iostream>
using namespace std;
int main()
{
    int n;
    while (true)
    {
        cin >> n;
        if (n==-1)
        {
            cout << "Bye";
            break;
        }
        if (n%5==0 && n>0) cout << n/5 << endl;
        else cout << -1;

    }
    return 0;
}
