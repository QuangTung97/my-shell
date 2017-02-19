#include <cmd_token_parser.h>

CmdTokenParser::CmdTokenParser()
{
	// node start
	start.add_transition(&n_utf8, utf8_word);
	start.add_transition(&n_utf8, special);
	start.add_transition(&n_utf8, backslash);
	start.add_transition(&n_sq, single_quote);
	start.add_transition(&n_dq, double_quote);
	
	// node utf8
	n_utf8.set_end();
	n_utf8.add_loop_range(utf8_word);
	n_utf8.add_loop_range(special);
	n_utf8.add_loop_range(backslash);
	
	// node sq
	n_sq.add_character = no_add;
	n_sq.add_transition(&n_sq_utf8, utf8_word);
	n_sq.add_transition(&n_sq_utf8, white_space);
	n_sq.add_transition(&n_sq_utf8, special);
	n_sq.add_transition(&n_sq_utf8, double_quote);
	n_sq.add_transition(&n_sq_bs, backslash);
	
	// node sq utf8
	n_sq_utf8.add_loop_range(utf8_word);
	n_sq_utf8.add_loop_range(white_space);
	n_sq_utf8.add_loop_range(special);
	n_sq_utf8.add_loop_range(double_quote);
	n_sq_utf8.add_transition(&n_sq_bs, backslash);
	n_sq_utf8.add_transition(&n_sq_end, single_quote);
	
	// node sq bs
	n_sq_bs.add_character = no_add;
	n_sq_bs.add_transition(&n_sq_utf8, single_quote);
	n_sq_bs.add_transition(&n_sq_utf8, backslash);
	
	// node sq end
	n_sq_end.add_character = no_add;
	n_sq_end.set_end();
	
	// node dq
	n_dq.add_character = no_add;
	n_dq.add_transition(&n_dq_utf8, utf8_word);
	n_dq.add_transition(&n_dq_utf8, white_space);
	n_dq.add_transition(&n_dq_utf8, special);
	n_dq.add_transition(&n_dq_utf8, single_quote);
	n_dq.add_transition(&n_dq_bs, backslash);
	
	// node dq utf8
	n_dq_utf8.add_loop_range(utf8_word);
	n_dq_utf8.add_loop_range(white_space);
	n_dq_utf8.add_loop_range(special);
	n_dq_utf8.add_loop_range(single_quote);
	n_dq_utf8.add_transition(&n_dq_bs, backslash);
	n_dq_utf8.add_transition(&n_dq_end, double_quote);
	
	// node dq bs
	n_dq_bs.add_character = no_add;
	n_dq_bs.add_transition(&n_dq_utf8, double_quote);
	n_dq_bs.add_transition(&n_dq_utf8, backslash);
	
	// node dq end
	n_dq_end.add_character = no_add;
	n_dq_end.set_end();
}
