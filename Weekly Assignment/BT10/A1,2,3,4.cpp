#include<bits/stdc++.h>
using namespace std;
struct Point
{
    double x;
    double y;
    Point(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    Point(){};
};
//A1
void print(Point p)
{
    cout << '(' << p.x << " , " << p.y << ')' << endl;
}
//A2
void printAddress1 (Point &p)
{
    cout << &p << endl;
}
void printAddress2 (Point p)
{
    cout << &p << endl;
}
//A3
Point mid_point(Point a, Point b)
{
    double mx = (a.x+b.x)/2;
    double my = (a.y+b.y)/2;
    Point midPoint(mx,my);
    return midPoint;
}
//A4
void print_point_address(Point &p)
{
    cout << &(p.x) << ' ' << &(p.y)<< endl;
}
int main()
{
    Point p(2,4);
    print(p);
    printAddress1(p); // địa chỉ thật của p 0x61fe00
    printAddress2(p); // địa chỉ giá trị copy của p 0x61fd70
    Point c(1,2);
    Point d(3,4);
    print(mid_point(c,d));
    print_point_address(p); // 0x61fe00,  0x61fe08
    // nhận xét: địa chỉ p trùng địa chỉ x
}
