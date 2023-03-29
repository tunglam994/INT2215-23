#include <bits/stdc++.h>
using namespace std;
int main( )
{
    char a[4] = "abc";
    for (char *cp = a; (*cp) != '\0'; cp++) {
        cout << (void*) cp << " : " << (*cp) << endl;
   }
    /*a)0x61fdfc : a
        0x61fdfd : b
        0x61fdfe : c
        */

    int i[4] = {1,2,3};
    for (int *ip = i; (*ip) != NULL; ip++) {
        cout << (void*) ip << " : " << (*ip) << endl;
    }
    /*b)0x61fde0 : 1
        0x61fde4 : 2
        0x61fde8 : 3
        */
    double d[4] = {1,2,3};
    for (double *dp = d; (*dp) != NULL; dp+= 1)
    cout << (void*) dp << " : " << (*dp) << endl;

   /* c)0x61fdc0 : 1
        0x61fdc8 : 2
        0x61fdd0 : 3
    */
    for (double *dp = d; (*dp) != NULL; dp+= 2)
    cout << (void*) dp << " : " << (*dp) << endl;
   /* d)0x61fdc0 : 1
        0x61fdd0 : 3
    */
   return 0;
}
