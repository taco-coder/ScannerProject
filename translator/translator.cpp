#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: 8
//=================================================
// ------ Three  Tables -------------------------------------

// TABLES Done by: Maria Bailon
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

string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR"};

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

tokentype saved_token;
bool token_available;
string saved_lex;
string saved_e_word;
// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt
//  Done by: Tahwab Noori
map<string, string> lexicon;
ofstream trans;

// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result
//                 in saved_E_word
//  Done by: Maria Bailon
void getEword()
{
    map<string, string>::iterator e_word = lexicon.find(saved_lex);
    if (e_word != lexicon.end())
    { // lexicon[saved_lexeme] exists
        saved_e_word = e_word->second;
    }
    else
    {
        saved_e_word = saved_lex;
    }
}
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Tyler Cox
void gen(string line_type)
{
    string saved;

    if (line_type == "TENSE")
    {
        saved = tokenName[saved_token] + '\n';
    }
    else
    {
        saved = saved_e_word;
    }

    trans << line_type << ": " << saved << endl;
}

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
        return 1;
    }
    else
    {
        cout << endl
             << "Lexical error: " << w << " is not a valid token" << endl;
        tt = ERROR;
    }
} //the end of scanner
// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar
//    rule with semantic routine calls
//    above each non-terminal function

// ** Each non-terminal function should be calling
//    getEword and/or gen now.
// Type of error: Match Fails
// Done by: Tahwab Noori
void syntax_error1(tokentype expected)
{
    cout << endl
         << "SYNTAX ERROR: expected " << tokenName[expected] << " but found " << saved_lex << endl;
    exit(1);
}
// Type of error: Switch Default
// Done by: Tahwab Noori
void syntax_error2(string function_name)
{
    cout << endl
         << "SYNTAX ERROR: unexpected " << saved_lex << " found in " << function_name << endl;
    exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Gets next token
// Done by: Maria Bailon
tokentype next_token()
{
    if (!token_available)
    {
        scanner(saved_token, saved_lex);
        token_available = true;
    }

    return saved_token;
}

// Purpose: Checks if token was expected
// Done by: Maria Bailon
bool match(tokentype expected)
{
    if (next_token() != expected)
    {
        syntax_error1(expected);
    }
    else
    {
        token_available = false;
        cout << "Matched " << tokenName[expected] << endl;
        return true;
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Tyler Cox
void noun()
{
    cout << "Processing <noun>" << endl;

    switch (next_token())
    {
    case WORD1:
        match(WORD1);
        break;
    case PRONOUN:
        match(PRONOUN);
        break;
    default:
        syntax_error2("noun");
    }
    getEword();
}

// Grammar: <verb> ::= WORD2
// Done by: Maria Bailon
void verb()
{
    cout << "Processing <verb>" << endl;

    match(WORD2);
    getEword();
    gen("ACTION");
}

// Grammar: <tense> := VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Tyler Cox
void tense()
{
    cout << "Processing <tense>" << endl;

    switch (next_token())
    {
    case VERBPAST:
        match(VERBPAST);
        break;
    case VERBPASTNEG:
        match(VERBPASTNEG);
        break;
    case VERB:
        match(VERB);
        break;
    case VERBNEG:
        match(VERBNEG);
        break;
    default:
        syntax_error2("tense");
    }
    gen("TENSE");
}
// Grammar: <be> ::= IS | WAS
// Done by: Maria Bailon
void be()
{
    cout << "Processing <be>" << endl;

    switch (next_token())
    {
    case IS:
        match(IS);
        break;
    case WAS:
        match(WAS);
        break;
    default:
        syntax_error2("be");
    }
    gen("DESCRIPTION");
    gen("TENSE");
}

// Grammar: <after object> ::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
// Done by: Tyler Cox
void after_object()
{
    cout << "Processing <after_object>" << endl;

    switch (next_token())
    {
    case WORD2:
        verb();
        tense();
        match(PERIOD);
        break;
    case WORD1:
    case PRONOUN:
        noun();
        match(DESTINATION);
        gen("TO");
        verb();
        tense();
        match(PERIOD);
        break;
    default:
        syntax_error2("after_object");
    }
}

// Grammar: <after noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <after object>
// Done by: Tahwab Noori
void after_noun()
{
    cout << "Processing <after_noun>" << endl;

    switch (next_token())
    {
    case IS:
    case WAS:
        be();
        match(PERIOD);
        break;
    case DESTINATION:
        match(DESTINATION);
        gen("TO");
        verb();
        tense();
        match(PERIOD);
        break;
    case OBJECT:
        match(OBJECT);
        gen("OBJECT");
        after_object();
        break;
    default:
        syntax_error2("after_noun");
    }
}
// Grammar: <after subject> ::= <verb> <tense> PEROD | <noun> <after noun>
// Done by: Tahwab Noori
void after_subject()
{
    cout << "Processing <after_subject>" << endl;

    switch (next_token())
    {
    case WORD2:
        verb();
        tense();
        match(PERIOD);
        break;
    case WORD1:
    case PRONOUN:
        noun();
        after_noun();
        break;
    default:
        syntax_error2("after_subject");
    }
}

// Grammar: <s> ::= [CONNECTOR] <noun> SUBJECT <after subject>
// Done by: Maria Bailon
void s()
{
    cout << "Processing <s>" << endl;

    if (next_token() == CONNECTOR)
    {
        match(CONNECTOR);
        getEword();
		gen("CONNECTOR");
    }

    noun();

    match(SUBJECT);
    gen("ACTOR");
    after_subject();
}

// Grammar: <story> ::= <s> { <s> }
// Done by: Tahwab Noori
void story()
{
    cout << "Processing <story>" << endl
         << endl;

    s();

    bool done = false;
    while (!done)
    {
        switch (next_token())
        {
        case CONNECTOR:
        case WORD1:
        case PRONOUN:
            s();
            break;
        default:
            done = true;
        }
    }

    cout << endl
         << "Successfully parsed <story>." << endl;
}

string filename;

// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  Tahwab Noori
int main()
{
    //** opens the lexicon.txt file and reads it into Lexicon
    //** closes lexicon.txt

    //** opens the output file translated.txt
    ifstream lex("lexicon.txt", ios::in);
    string line;

    while (getline(lex, line))
    {
        istringstream tokens(line);
        string jap, eng;

        tokens >> jap;
        tokens >> eng;

        lexicon[jap] = eng;
    }

    lex.close();

    trans.open("translated.txt", ios::out);

    cout << "Enter the input file name: ";
    cin >> filename;
    fin.open(filename.c_str());

    //** calls the <story> to start parsing
	story(); 

	fin.close();
	trans.close();
    //** closes the input file
    //** closes traslated.txt

} // end