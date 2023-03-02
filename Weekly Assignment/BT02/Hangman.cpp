#include <bits/stdc++.h>

using namespace std;

const int MAX_WORD = 200;

const string word[MAX_WORD] = {
        "angle", "ant", "apple", "arch", "arm", "army",
        "baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry",
        "bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
        "brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
        "cake", "camera", "card",  "cart", "carriage", "cat", "chain", "cheese", "chest",
        "chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
        "cow", "cup", "curtain", "cushion",
        "dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
        "face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
        "foot", "fork", "fowl", "frame", "garden", "girl", "glove", "goat", "gun",
        "hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
        "hospital", "house", "island", "jewel",  "kettle", "key", "knee", "knife", "knot",
        "leaf", "leg", "library", "line", "lip", "lock",
        "map", "match", "monkey", "moon", "mouth", "muscle",
        "nail", "neck", "needle", "nerve", "net", "nose", "nut",
        "office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
        "pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
        "rail", "rat", "receipt", "ring", "rod", "roof", "root",
        "sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
        "shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
        "square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
        "store", "street", "sun", "table", "tail", "thread", "throat", "thumb", "ticket",
        "toe", "tongue", "tooth", "town", "train", "tray", "tree", "trousers", "umbrella",
        "wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm"
};

const string FIGURE[8] = {
    "   -------------    \n"
    "   |                \n"
    "   |                \n"
    "   |                \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |                \n"
    "   |                \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |                \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |           |    \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|    \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|\\  \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|\\  \n"
    "   |          /     \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|\\  \n"
    "   |          / \\  \n"
    "   |     \n"
    " -----   \n"
};

string chooseWord()
{
    int n = rand() %200;
    string secretWord = word[n];
    return secretWord;
}

void renderGame(string guessedWord, int badGuessCount)
{
	cout << guessedWord << endl;
	cout << FIGURE[badGuessCount];
}

bool contains(string secretWord, char guess)
{
    int n = secretWord.length();
    for (int i=0; i<n; i++)
    {
        if (secretWord[i] == guess) return 1;
    }
    return 0;
}

char readAGuess()
{
    char c;
    cout << "Enter your guess:  ";
    cin >> c;
    return c;
}

string update(string guessedWord, string secretWord, char guess)
{
	for (int i = secretWord.length() - 1; i >= 0; i--) {
        if (secretWord[i] == guess) {
            guessedWord[i] = guess;
        }
    }
    return guessedWord;
}

void playHangman (string secretWord)
{
    string guessedWord = string(secretWord.length(), '-');
    int badGuessCount = 0;

    do {
        renderGame(guessedWord, badGuessCount);
        char guess = readAGuess();
        if (contains(secretWord, guess))
        guessedWord = update(guessedWord, secretWord, guess);
        else badGuessCount++;
    } while (badGuessCount < 7 && secretWord != guessedWord);

    renderGame(guessedWord, badGuessCount);
    if (badGuessCount < 7) cout << "Congratulations! You win!" << endl;
    else cout << "You lost. The correct word is " << secretWord << endl;
}


int main()
{
    srand(time(0));
    bool quit = 0;
    while (!quit)
    {
        string secretWord = chooseWord();
        playHangman(secretWord);
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
