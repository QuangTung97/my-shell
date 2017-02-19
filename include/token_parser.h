#ifndef TOKEN_PARSER
#define TOKEN_PARSER

#include <string>
#include <vector>
#include <stdexcept>

using std::string;
using std::vector;


class TokenParseError: public std::exception {
	string message;
public:
	TokenParseError(const char *s): message{s}{}
	virtual const char *what() const throw() override { return message.c_str(); }
	virtual ~TokenParseError() {}
};

class TokenNode;
class TokenParser;

typedef bool (*range_test)(char);

struct transition 
{
	TokenNode *next;
	range_test range;
};

typedef void (*add_character_type)(string &token, char ch);

class TokenNode {
private:
	friend TokenParser;
	vector<range_test> loop_range;
	vector<transition> transitions;
	bool is_end = false;
	
public:
	TokenNode();
	void add_loop_range(range_test range);
	void add_transition(TokenNode *next, range_test range);
	void set_end();
	
	add_character_type add_character;
};

class TokenParser 
{
protected:
	// available ranges
	range_test utf8_word;
	range_test alpha_underscore;
	range_test digit;
	range_test single_quote;
	range_test double_quote;
	range_test white_space;
	range_test backslash;
	range_test special;
	
	TokenNode start;
	
private:
	TokenNode *current = &start;
	
public:
	TokenParser();
	virtual ~TokenParser() {}
	void parse(const string &str, vector<string> &tokens);
	
};

#endif
