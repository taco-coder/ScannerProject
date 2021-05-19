#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/
// parser begins on line 224
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
      return 1;
   }
   else
   {
      cout << endl
           << "Lexical error: " << w << " is not a valid token" << endl;
      tt = ERROR;
   }
} //the end of scanner
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

//=================================================
// File parser.cpp written by Group Number: 8
//=================================================

tokentype saved_token;
bool token_available;
string saved_lex;

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

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
}

// Grammar: <verb> ::= WORD2
// Done by: Maria Bailon
void verb()
{
   cout << "Processing <verb>" << endl;

   match(WORD2);
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
      verb();
      tense();
      match(PERIOD);
      break;
   case OBJECT:
      match(OBJECT);
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
   }

   noun();

   match(SUBJECT);

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

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Tyler Cox
int main()
{
   cout << "Enter the input file name: ";
   cin >> filename;
   fin.open(filename.c_str());

   story();
   fin.close();

} // end