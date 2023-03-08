#include<bits/stdc++.h>
using namespace std;

int check_col[10000] = {};
int check_ver[10000] = {};


int place (int y, int size, string* result) {
    if (y >= size) {
        for (int i = 0;i < size;i++) {
            for (int j = 0;j < size;j++) {
                cout << result[i][j];
            }
            cout << endl;
        }
        cout << endl;
        return 0;
    }

    for (int i = 0;i < size;i++) {
        // cout << i << " " << y << endl;
        if (!check_col[i] && !check_ver[abs(y-i)]) {
            check_col[i] = 1;
            check_ver[abs(y-i)] = 1;
            result[y][i] = '*';
            place((y+1),size,result);
            //
            result[y][i] = '.';
            check_col[i] = 0;
            check_ver[abs(y-i)] = 0;
        }
    }
    return 0;
}

int main()
{
    long long n;
    cin >> n;
    string a[1000];
    for (long long i=0; i< n; i++)
    {
        for (long long j=0; j< n; j++)
        {
            a[i] += '.';
        }
    }
    place(0,n,a);
    return 0;
}
