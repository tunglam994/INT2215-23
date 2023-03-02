#include<bits/stdc++.h>


using namespace std;
int main()
{
    int d, m, y;
    cin >> d >> m >> y;
    int DayOfWeek = ((d+y+y/4-y/100+y/400+(31*m)/12)+4)%7;
    switch (DayOfWeek)
    {
    case 0:
        cout << "Sunday";
        break;
    case 1:
        cout << "Monday";
        break;
    case 2:
        cout << "Tuesday";
        break;
    case 3:
        cout << "Wednesday";
        break;
    case 4:
        cout << "Thursday";
        break;
    case 5:
        cout << "Friday";
        break;
    case 7:
        cout << "Saturday";
        break;
    }
    return 0;
}
