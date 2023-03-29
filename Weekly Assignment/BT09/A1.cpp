#include<bits/stdc++.h>
using namespace std;

char* concat(const char* a, const char* b)
{
    int alen = strlen(a);
    int blen = strlen(b);
    char* dst = new char [alen+blen];
    for (int i = 0; i < alen; i++) dst[i] = a[i];
    for (int i = alen; i< alen + blen; i++) dst[i] = b[i - alen];
    return dst;
}

void print (char* a)
{
    int n = strlen(a);
    for (int i = 0; i<n; i++)
    {
        cout << a[i];
    }
}

int main()
{
    char a[] = "Hello";
    char b[] = "World";
    print (concat(a, b));

}
