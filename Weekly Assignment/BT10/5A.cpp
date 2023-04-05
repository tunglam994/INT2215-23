#include <iostream>

using namespace std;

struct Array
{
    int n;
    int* arr;
    Array(const int _n = 10) {
        n = _n;
        arr = new int[n];
    }

    ~Array()
    {
        delete [] arr;
    }
};

struct List
{
    Array Arr;
    void print()
    {
        cout << Arr.arr << endl;
    }
};

int main()
{
    List a;
    List b = a;
    a.print();
    b.print();

    return 0;
}

// 2 con trỏ cùng chỉ vào 1 vùng nhớ
