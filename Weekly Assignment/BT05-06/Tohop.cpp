#include<bits/stdc++.h>
using namespace std;

void combination (char arr[], char data[], int start, int End, int index, int k)
{
    if (index == k)
    {
        for (int j = 0; j < k; j++) cout << data[j] << ' ';
        cout << endl;
        return ;
    }
    for (int i = start; i<= End && End - i + 1 >= k - index; i++)
    {
        data[index] = arr[i];
        combination (arr, data, i+1, End, index+1, k);
    }
}

void printCombination(char arr[], int n, int k)
{
    char data[k];
    combination (arr, data, 0, n-1, 0, k);
}
int main()
{
    int n;
    cin >> n;
    int k;
    cin >> k;
    char arr[n];
    for (int i=0; i<n; i++)
    {
        arr[i] = 'a' + i;

    }
    printCombination(arr, n, k);
    return 0;
}
