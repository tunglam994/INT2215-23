#include<iostream>
using namespace std;
int main()
{
    int year;
    cin >> year;
    if (year%4!=0) cout << "false";
    else if (year%400==0) cout << "true";
    else if (year%100==0) cout << "false";
    else cout << "true";
    return 0;
}
