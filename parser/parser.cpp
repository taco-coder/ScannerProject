#include <iostream>
#include <fstream>
#include <string>
#include "parser.hpp"
#include "scanner.hpp"
using namespace std;


//=================================================
// File parser.cpp written by Group Number: 8
//=================================================

extern string tokenName[];
extern map<string, tokentype> reserved_words;

tokentype saved_token;
bool token_available;
string saved_lex;

// Error type: Match fails
// Done by: Tahwab Noori
void syntax_error1(tokentype expected) {
	cout << endl << "SYNTAX ERROR: expected " << tokenName[expected] << " but found " << saved_lex << endl;
	exit(1);
}

// Error type: Switch Default
// Done by: Tahwab Noori
void syntax_error2(string function_name) {
	cout << endl << "SYNTAX ERROR: unexpected " << saved_lex << " found in " << function_name << endl;
	exit(1);
}

// Purpose: Gets next token
// Done by: Maria Bailon
tokentype next_token()
{
	if (!token_available) {
		scanner(saved_token, saved_lex);
		token_available = true;
	}

	return saved_token;
}

// Purpose: Checks if token was expected
// Done by: Maria Bailon
bool match(tokentype expected)
{
	if (next_token() != expected) {
		syntax_error1(expected);
	}
	else {
		token_available = false;
		cout << "Matched " << tokenName[expected] << endl;
		return true;
	}
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <story> ::= <s> { <s> }
// Done by: Tahwab Noori
void story()
{
	cout << "Processing <story>" << endl << endl;

	s();

	bool done = false;
	while (!done) {
		switch (next_token()) {
		case CONNECTOR:
		case WORD1:
		case PRONOUN:
			s();
			break;
		default: done = true;
		}
	}

	cout << endl << "Successfully parsed <story>." << endl;
}

// Grammar: <s> ::= [CONNECTOR] <noun> SUBJECT <after subject>
// Done by: Maria Bailon
void s()
{
	cout << "Processing <s>" << endl;

	if (next_token() == CONNECTOR) {
		match(CONNECTOR);
	}

	noun();

	match(SUBJECT);

	after_subject();
}

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Tyler Cox
void noun()
{
	cout << "Processing <noun>" << endl;

	switch (next_token()) {
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

// Grammar: <after subject> ::= <verb> <tense> PEROD | <noun> <after noun>
// Done by: Tahwab Noori
void after_subject()
{
	cout << "Processing <after_subject>" << endl;

	switch (next_token()) {
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

	switch (next_token()) {
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

// Grammar: <after noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <after object>
// Done by: Tahwab Noori
void after_noun()
{
	cout << "Processing <after_noun>" << endl;

	switch (next_token()) {
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

// Grammar: <be> ::= IS | WAS
// Done by: Maria Bailon
void be()
{
	cout << "Processing <be>" << endl;

	switch (next_token()) {
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

	switch (next_token()) {
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

//---------------------------------------

extern ifstream fin;

// The new test driver to start the parser
// Done by: Tyler Cox
int main()
{
	string filename;

	cout << "Enter the input file name: ";
	cin >> filename;
	fin.open(filename.c_str());


	story(); 
	fin.close(); 
}// end