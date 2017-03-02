#include <token_parser.h>
#include <cstring>

TokenNode::TokenNode() 
{
	loop_range.clear();
	transitions.clear();
	// default add_character
	add_character = [](string &token, char ch)->void {
		token += ch;
	};
}

void TokenNode::add_loop_range(range_test range) 
{
	loop_range.push_back(range);
}

void TokenNode::add_transition(TokenNode *next, range_test range)
{
	struct transition t;
	t.next = next;
	t.range = range;
	transitions.push_back(t);
}

void TokenNode::set_end() { is_end = true; }

// for class TokenParser

TokenParser::TokenParser()
{
	// setting available ranges
	utf8_word = [](char ch)->bool {
		if (ch < 0) {
			return true;
		}
		
		if (ch >= 'a' && ch <= 'z')
			return true;
		if (ch >= 'A' && ch <= 'Z')
			return true;
		if (ch >= '0' && ch <= '9')
			return true;
		return false;
	};
	
	alpha_underscore = [](char ch)->bool {
		if (ch == '_')
			return true;
		if (ch >= 'a' && ch <= 'z')
			return true;
		if (ch >= 'A' && ch <= 'Z')
			return true;
		return false;
	};
	
	digit = [](char ch)->bool {
		if (ch >= '0' && ch <= '9')
			return true;
		return false;
	};
	
	single_quote = [](char ch)->bool {
		return ch == '\'';
	};
	
	double_quote = [](char ch)->bool {
		return ch == '\"';
	};
	
	white_space = [](char ch)->bool {
		return ch == ' ' || ch == '\n' || 
					ch == '\t' || ch == '\r';
	};
	
	backslash = [](char ch)->bool {
		return ch == '\\'; 
	};
	
	/*  %, ! / . */
	special = [](char ch)->bool {
		if (ch == '\"' || ch == '\'')
			return false;
		if (ch == '%' || ch == ':' || ch == ';')
			return true;
		
		if (ch >= '!' && ch <= '/')
			return true;
		return false;
	};
	// default start node
	start.add_loop_range(white_space);
}

void TokenParser::parse(const string &str,
			vector<string> &tokens)
{
	string token = "";
	current = &start;
	
	for (auto it = str.begin(); it != str.end(); ++it) {
		char ch = *it;
		
		if (current == &start) {
			// loop if white space
			for (range_test range: current->loop_range)
				if (range(ch)) 
					goto node_continue;
			
			for (transition t: current->transitions) 
				if (t.range(ch)) {
					token = "";
					current = t.next;
					
					current->add_character(token, ch);
					goto node_continue;
				}
			throw TokenParseError("Start Entry");
		}
		else {
			for (range_test range: current->loop_range)
				if (range(ch)) {
					current->add_character(token, ch);
					goto node_continue;
				}
			for (transition t: current->transitions) 
				if (t.range(ch)) {
					current = t.next;
					current->add_character(token, ch);
					goto node_continue;
				}
				
			if (current->is_end) {
				tokens.push_back(token);
				--it;
				current = &start;
				goto node_continue;
			}
			
			throw TokenParseError("Non Start Entry");
		}

node_continue:;
	}
	if (current->is_end) {
		tokens.push_back(token);
		return;
	}

	if (current != &start)
		throw TokenParseError("Non Terminate");
}
