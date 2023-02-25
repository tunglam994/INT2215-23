#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int w, h;
    cin >> w >> h;
    char pos[h][w];
    for (int i =0; i<h; i++) for (int j=0; j<w; j++) cin >> pos[i][j];
    for (int i=0; i<h; i++)
    {
        bool alive = 0;
        for (int j=0; j<w; j++)
        {
            if (pos[i][j]!='Y') continue;
            alive = 1;
            for (int k=-1; k<=1; k++)
            {
                if (j+k >=0 && j+k<w && pos[i+1][j+k]=='E' && pos[i][j+k] != 'R') pos[i+1][j+k] = 'Y';
            }
            if (!alive)
            {
                cout << "NO" ;
                return 0;
            }
        }
    }
    for (int j = 0; j < w; j++) {
        if (pos[h - 1][j] == 'Y') {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}
