#include<iostream>
#include<fstream>
#include<string>
#include <vector>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 
//=====================================================

// --------- Two DFAs ---------------------------------


// WORD DFA
// Done by: Tyler Cox, Maria Bailon, Tahwab Noori
// RE:   (vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+
bool word(string s)
{

    int state = 0; //state 0 is q0
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
            state = 2;//state 2 is q0qy
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
    if (state == 0 || state == 1 || state == 2) return(true);
    else return(false);

}

// PERIOD DFA
// Done by: Tyler Cox
bool period(string s)
{  // check if the character is a period and return true if it is
    if (s == ".")
        return (true);
    else
        return(false);
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Maria Bailon

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype { ERROR, WORD1, WORD2, PERIOD, EOFM, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, SUBJECT, OBJECT, DESTINATION, PRONOUN, CONNECTOR };

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = { "ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "SUBJECT", "OBJCT", "DESTINATION", "PRONOUN", "CONNECTOR" };

string reservedWords[30] = { "masu", "masen", "mashita", "masendeshita", "desu", "deshita", "o", "wa", "ni", "watashi", "anata", "kare", "kanojo", "sore", "mata", "soshite", "shikashi", "dakara", "eofm" };

struct reservedWord
{
    string WORD;
    tokentype TYPE;
};
vector <reservedWord> rWList;
void init()
{
    reservedWord rWord;

    rWord.WORD = "masu";
    rWord.TYPE = VERB;
    rWList.push_back(rWord);

    rWord.WORD = "masen";
    rWord.TYPE = VERBNEG;
    rWList.push_back(rWord);

    rWord.WORD = "mashita";
    rWord.TYPE = VERBPAST;
    rWList.push_back(rWord);


    rWord.WORD = "masendeshita";
    rWord.TYPE = VERBPASTNEG;
    rWList.push_back(rWord);


    rWord.WORD = "desu";
    rWord.TYPE = IS;
    rWList.push_back(rWord);


    rWord.WORD = "deshita";
    rWord.TYPE = WAS;
    rWList.push_back(rWord);


    rWord.WORD = "o";
    rWord.TYPE = OBJECT;
    rWList.push_back(rWord);


    rWord.WORD = "wa";
    rWord.TYPE = SUBJECT;
    rWList.push_back(rWord);


    rWord.WORD = "ni";
    rWord.TYPE = DESTINATION;
    rWList.push_back(rWord);


    rWord.WORD = "watashi";
    rWord.TYPE = PRONOUN;
    rWList.push_back(rWord);


    rWord.WORD = "anata";
    rWord.TYPE = PRONOUN;
    rWList.push_back(rWord);


    rWord.WORD = "kare";
    rWord.TYPE = PRONOUN;
    rWList.push_back(rWord);


    rWord.WORD = "kanojo";
    rWord.TYPE = PRONOUN;
    rWList.push_back(rWord);


    rWord.WORD = "sore";
    rWord.TYPE = PRONOUN;
    rWList.push_back(rWord);


    rWord.WORD = "mata";
    rWord.TYPE = CONNECTOR;
    rWList.push_back(rWord);


    rWord.WORD = "soshite";
    rWord.TYPE = CONNECTOR;
    rWList.push_back(rWord);


    rWord.WORD = "shikashi";
    rWord.TYPE = CONNECTOR;
    rWList.push_back(rWord);


    rWord.WORD = "dakara";
    rWord.TYPE = CONNECTOR;
    rWList.push_back(rWord);


    rWord.WORD = "eofm";
    rWord.TYPE = EOFM;
    rWList.push_back(rWord);

}



// ------------ Scanner and Driver -----------------------
// Done by: Tyler Cox, Maria Bailon, Tahwab Noori

ifstream fin;  // global stream for reading from the input file

int scanner(tokentype& tt, string& w)
{

    // ** Grab the next word from the file via fin
    fin >> w;

    // 2. Call the token functions one after another (if-then-else)
    if (word(w)) //if it is in the regular DFA
    {
        if (w.at(w.size() - 1) == 'I' || w.at(w.size() - 1) == 'E') //if the word ends in I or E
        { //then the expression is WORD2
            tt = WORD2;
        }
        else //otherwise, it is WORD1
        {
            tt = WORD1;
        }
        //if it is tt reserved word, then overwrite the token type.
        for (int i = 0; i < rWList.size(); i++)
        {
            reservedWord r = rWList.at(i);
            if (r.WORD == w) //if the word is found in the reserved list
            {
                tt = r.TYPE; //then append its token type
                break;
            }
        }
    }
    else if (period(w)) //if it is in the period DFA
    {
        tt = PERIOD;
    }
    else if (w == "eofm")
    {
        return 1;
    }
    else //if it is not found in any of the word DFA's
    {
        tt = ERROR;
    }

    if (tt == ERROR)
    {
        cout << "***Lexical Error: " << w << " is not tt valid token." << "***" << endl;
    }

    return 1;
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by:  Louis
int main()
{
    tokentype thetype;
    init();
    string theword;
    string filename;

    cout << "Enter the input file name: ";
    cin >> filename;

    fin.open(filename.c_str());

    // the loop continues until eofm is returned.
    while (true)
    {
        scanner(thetype, theword);  // call the scanner which sets
        // the arguments
        if (theword == "eofm") break;  // stop now

        cout << "\"" << theword << "\" is token type " << tokenName[thetype] << endl << endl;


    }

    cout << "End of file is encountered." << endl;
    fin.close();

}// end