#include<bits/stdc++.h>
using namespace std;
int main()
{
    int* p = new int;
    int* p2 = p; // p, p2 cùng chỉ vào 1 vùng nhớ
    *p = 10;
    delete p; //p và p2 trở thành con trỏ lơ lửng
    *p2 = 100; // không thể gán như vậy vì p2 đang truy cập vào vùng nhớ chưa được cấp phát
    cout << *p2;
    delete p2;

}
