#ifndef CMD_TOKEN_PARSER
#define CMD_TOKEN_PARSER

#include <token_parser.h>

class CmdTokenParser: public TokenParser 
{
private:
	TokenNode n_utf8;
	
	TokenNode n_sq;
	TokenNode n_sq_utf8;
	TokenNode n_sq_end;
	TokenNode n_sq_bs; // backslash
	
	TokenNode n_dq;
	TokenNode n_dq_utf8;
	TokenNode n_dq_end;
	TokenNode n_dq_bs;
	
	add_character_type no_add = 
		[](string &token, char ch)->void {};
public:
	CmdTokenParser();
	virtual ~CmdTokenParser() {};
};

#endif