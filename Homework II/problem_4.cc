#include <iostream>
#include <fstream>

using namespace std;


int main()
{
    int n, length, i;
    ofstream palindromes_file;
    int bolean1 = 0;
    
    cout << "Please insert the number of letters of your word: " << endl;
    cin >> n;
    
    char word[n];

    cout << "Please insert a word or a phrase: " << endl;
    cin >> word;
    
    length = sizeof(word);
    
    for (i = 0; i < length; i++)
    {
        if (word[i] != word[length-i-1])
        {
            bolean1 = 1;
        }
    }

    if (not bolean1)
    {
        cout << "The word is a palindrome." << endl;
        palindromes_file.open ("palindrome_file.txt", ios::app | ios::ate);
        palindromes_file << word << " The word is a palindrome." << endl;
        palindromes_file.close();
    }
    
    else if (bolean1)
    {
        cout << "The word is not a palindrome." << endl;
        palindromes_file.open ("palindrome_file.txt", ios::app | ios::ate);
        palindromes_file << word << " The word is not a palindrome." << endl;
        palindromes_file.close();
    }
}

