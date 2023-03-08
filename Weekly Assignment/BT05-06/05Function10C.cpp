#include<bits/stdc++.h>
using namespace std;
int getRandlower (int n)
{
    return rand()%n;
}
void printNumber (int s[], int n)
{

    for (int i = 0; i < n-2; i++)
    {
        for (int j = i+1; j < n-1; j++)
        {
            for (int k = j +1; k < n; k++)
            {
                if ((s[i]+s[j]+s[k]) % 25 == 0) cout << s[i] << ' ' << s[j] << ' ' << s[k] << endl;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i<n; i++)
    {
        a[i] = getRandlower(50);
    }
    printNumber(a,n);
    return 0;
}
