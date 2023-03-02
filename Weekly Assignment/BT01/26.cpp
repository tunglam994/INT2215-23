#include<iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int Max=INT_MIN, Min=INT_MAX;
    double Mean=0;
    int m;
    for (int i=0; i<n; i++)
    {
        cin >> m;
        Mean += m;
        if (m > Max) Max = m;
        if (m < Min) Min = m;
    }
    Mean = Mean / n;
    cout << "Mean: " << Mean << endl << "Max: " << Max << endl << "Min: "<< Min;
    return 0;
    }
