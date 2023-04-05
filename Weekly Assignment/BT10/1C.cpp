#include <iostream>
#include <cstring>
using namespace std;

struct String
{
    //a
    char* str;
    int n;

    //b
    String(const char* _s)
    {
        n = strlen(_s);
        str = new char[n];
        strncpy(str, _s, n);
    }

    //c
    ~String()
    {
        delete [] str;
    }

    //d
    void print()
    {
        cout << str;
    }

    //e
    void append(const char* add)
    {
        int add_length = strlen(add);
        char* temp = new char [add_length + n];
        for (int i = 0; i<n; i++) temp[i] = str[i];
        for (int i = 0; i<add_length; i++) temp[i+n] = add[i];
        delete [] str;
        str = temp;
        n = add_length + n;

    }
};

int main()
{
    String s("Hi");
    s.append(" there");
    s.print();
    return 0;
}
