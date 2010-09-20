#include <iostream>
#include <string>
#include "strmath.cpp"

using namespace std;

int main()
{
    Tokenizer token;
    token.feed("The quick brown fox .. jumped over the lazy dog.");
    token.add_break(" .");
    token.tokenize();
    for (int i = 0; i < token.num_words; i++)
    {
        cout << low_string(up_string(token.word[i])) << endl;
    }
}

