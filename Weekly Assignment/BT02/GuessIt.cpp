#include<bits/stdc++.h>
using namespace std;

int generateSecretnumber()
{
    int secretNumber = rand()% 100 +1;
    return secretNumber;
}
int getPlayerguess()
{
    cout << "Enter a number (1-100): ";
    int guess;
    cin >> guess;
    return guess;
}
void printAnswer (int guess, int secretnumber)
{
    if (guess > secretnumber) cout << "Your number is too big. Try again." << endl;
    else if (guess < secretnumber) cout << "Your number is too small. Try again." << endl;
    else cout << "Congratulation! You win." << endl;
}
void playGuessit(int secretnumber)
{
    int guess=0;
    do
    {
        guess = getPlayerguess();
        printAnswer (guess, secretnumber);
    }
    while (guess != secretnumber);
}

int main()
{
    srand(time(0));
    bool quit = 0;
    while (!playing)
    {

        int secretnumber = generateSecretnumber();
        playGuessit(secretnumber);
        cout << "Play again? Press 'y' for Yes or 'n' for No:          ";
        char ans = '0';
        while (ans != 'y' && ans != 'Y' && ans != 'N' && ans != 'n')
        {
            cin >> ans;
            if (ans == 'N' || ans == 'n') quit = 1;
        }
    }

    return 0;
}


