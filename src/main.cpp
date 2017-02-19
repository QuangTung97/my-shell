#include <stdio.h>
#include <stdlib.h>
#include <printf_color.h>
#include <unix.h>
#include <unix_executor.h>
#include <cmd_token_parser.h>
#include <cstring>

int main(int argc, char **argv) {
	printf("Chao mung den voi shell cua Ta Quang Tung:\n");
	printf("--------------------------------------------\n");

	set_signal_handlers();

	// initialize
	Unix *unix = new Unix();
	TokenParser *parser = new CmdTokenParser();
	Executor *exec = new UnixExecutor(unix, parser);
	signal_set_executor(exec);

	while (1) {
		char buf[2048];
		printf(PFBLUE "my-shell$ " PFNORMAL);
		fgets(buf, 2048, stdin);		
		string str = buf;
		vector<string> args;
		
		try {
			parser->parse(str, args);
		}
		catch (TokenParseError &e) {
			printf(PFRED "Loi cu phap nhap!\n" PFNORMAL);
			continue;
		}
		exec->execute(args);
	}

	delete exec;
	delete parser;
	delete unix;
	return 0;
}
