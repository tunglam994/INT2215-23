#include<bits/stdc++.h>
using namespace std;
char**  Hadamard(long long n)
{
    long long N = pow (2,n);
    char** a = new char*[N];
    for (long long i=0; i<N; i++) a[i] = new char[N];
    if (n==0)
    {
        a[0][0] = '.';
        return a;
    }
    long long k = N/2;
    char **hadamard = Hadamard(n-1);
    for (long long i=0; i<k; i++)
    {
        for (long long j=0; j<k; j++)
        {
            a[i][j] = hadamard[i][j];
            a[i][j+k] = hadamard[i][j];
            a[i+k][j] = hadamard[i][j];
            if (hadamard[i][j]=='o') a[i+k][j+k] = '.';
            if (hadamard[i][j]=='.') a[i+k][j+k] = 'o';
        }

    }
    return a;
}

int main()
{
    long long n;
    cin >> n;
    char** a = Hadamard(n);
    for (long long i=0; i< pow(2,n); i++)
    {
        for (long long j=0; j< pow(2,n); j++)
        {
            cout << a[i][j];
        }
        cout << endl;
    }
    return 0;
}
