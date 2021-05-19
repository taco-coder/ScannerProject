#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 8
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA
// Done by: Tyler Cox, Maria Bailon, Tahwab Noori
// RE:   (vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+
bool word(string s)
{
    int state = 0;
    int charpos = 0;
    while (s[charpos] != '\0')
    {
        //initial transitions from state 0 or q0
        if (state == 0 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
            state = 1; //state 1 is q0q1
        else if (state == 0 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r'))
            state = 4; //state 4 is qy
        else if (state == 0 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
            state = 5; //state 5 is qsa
        else if (state == 0 && s[charpos] == 'c')
            state = 3; //state 3 is qc
        else if (state == 0 && s[charpos] == 's')
            state = 6; //state 6 is qs
        else if (state == 0 && s[charpos] == 't')
            state = 7; //state 7 is qt

        //transitions from q0q1
        else if (state == 1 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r'))
            state = 4; //state 4 is qy
        else if (state == 1 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
            state = 5; //state 5 is qsa
        else if (state == 1 && s[charpos] == 'c')
            state = 3; //state 3 is qc
        else if (state == 1 && s[charpos] == 's')
            state = 6; //state 6 is qs
        else if (state == 1 && s[charpos] == 't')
            state = 7; //state 7 is qt

        //transitions from q0qy
        else if (state == 2 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'm' || s[charpos] == 'k' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r'))
            state = 4; //state 4 is qy
        else if (state == 2 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
            state = 5; //state 5 is qsa
        else if (state == 2 && s[charpos] == 'c')
            state = 3; //state 3 is qc
        else if (state == 2 && s[charpos] == 's')
            state = 6; //state 6 is qs
        else if (state == 2 && s[charpos] == 't')
            state = 7; //state 7 is qt

        else if (state == 1 && s[charpos] == 'n')
            state = 2; //state 2 is q0qy
        else if (state == 2 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
            state = 1;
        else if (state == 1 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
            state = 1; //account for the loop on q0q1

        //to get qsa qy qt and qs back to q0q1
        else if (state == 5 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
            state = 1;
        else if (state == 4 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
            state = 1;
        else if (state == 7 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
            state = 1;
        else if (state == 6 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'o' || s[charpos] == 'u' || s[charpos] == 'I' || s[charpos] == 'E'))
            state = 1;

        //the different letters that can get to qsa
        else if (state == 3 && s[charpos] == 'h')
            state = 5;
        else if (state == 6 && s[charpos] == 'h')
            state = 5;
        else if (state == 7 && s[charpos] == 's')
            state = 5;
        else if (state == 4 && s[charpos] == 'y')
            state = 5;

        //returns false if no character fits any definition
        else
            return (false);
        charpos++;
    }
    //final check of where we are
    if (state == 0 || state == 1 || state == 2)
        return (true);
    else
        return (false);
}

// PERIOD DFA
// Done by: Tyler Cox
bool period(string s)
{
    int state = 0;

    for (char c : s)
    {
        if (state == 0 && c == '.')
        {
            state = 1;
        }
        else
        {
            return false;
        }
    }
    return state == 1;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Maria Bailon

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype
{
    ERROR,
    WORD1,
    WORD2,
    PERIOD,
    EOFM,
    VERB,
    VERBNEG,
    VERBPAST,
    VERBPASTNEG,
    IS,
    WAS,
    SUBJECT,
    OBJECT,
    DESTINATION,
    PRONOUN,
    CONNECTOR
};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR"};

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
map<string, tokentype> reserved_words = {
    {"masu", VERB},
    {"masen", VERBNEG},
    {"mashita", VERBPAST},
    {"masendeshita", VERBPASTNEG},
    {"desu", IS},
    {"deshita", WAS},
    {"o", OBJECT},
    {"wa", SUBJECT},
    {"ni", DESTINATION},
    {"watashi", PRONOUN},
    {"anata", PRONOUN},
    {"kare", PRONOUN},
    {"kanojo", PRONOUN},
    {"sore", PRONOUN},
    {"mata", CONNECTOR},
    {"soshite", CONNECTOR},
    {"shikashi", CONNECTOR},
    {"dakara", CONNECTOR},
};

// ------------ Scanner and Driver -----------------------

ifstream fin; // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Maria Bailon, Tahwab Noori
int scanner(tokentype &tt, string &w)
{
    fin >> w;
    cout << "Scanner called using word: " << w << endl;
    map<string, tokentype>::iterator word_type;

    if (word(w))
    {
        word_type = reserved_words.find(w);
        if (word_type != reserved_words.end())
        {
            tt = word_type->second;
        }
        else
        {
            char last_c = w.back();
            tt = (last_c == 'I' || last_c == 'E') ? WORD2 : WORD1;
        }
    }
    else if (period(w))
    {
        tt = PERIOD;
    }
    else if (w == "eofm")
    {
        return;
    }
    else
    {
        cout << endl
             << "Lexical error: " << w << " is not a valid token" << endl;
        tt = ERROR;
    }
} //the end of scanner

// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by:  Louis
int main()
{
    tokentype thetype;
    string theword;
    string filename;

    cout << "Enter the input file name: ";
    cin >> filename;

    fin.open(filename.c_str());

    // the loop continues until eofm is returned.
    while (true)
    {
        scanner(thetype, theword); // call the scanner which sets
                                   // the arguments
        if (theword == "eofm")
            break; // stop now

        cout << "Type is:" << tokenName[thetype] << endl;
        cout << "Word is:" << theword << endl;
    }

    cout << "End of file is encountered." << endl;
    fin.close();

} // end
