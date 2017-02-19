#ifndef UNIX_EXECUTOR
#define UNIX_EXECUTOR

#include <executor.h>
#include <map>
#include <functional>

struct Process 
{
	int pid;
	string cmd;
	string status;
};

class Unix;
class TokenParser;

class UnixExecutor: public Executor
{
private:
	Unix *unix;
	int fg_pid;
	vector<string> paths;
	std::map<string, 
		std::function<void(vector<string> &)>> system_cmds;

	vector<Process> bg_processes;
	bool has_fg_process = false;
	TokenParser *parser;

	void init_paths();
	void init_system_cmds();

	void init_cmd_exit();
	void init_cmd_help();
	void init_cmd_path();
	void init_cmd_addpath();
	void init_cmd_list();
	void init_cmd_kill();
	void init_cmd_stop();
	void init_cmd_resume();

	bool is_bat_file(string &file);
	void wait_or_discard(bool is_foreground, int pid,
				string args);
	void handle_bat(string &path, bool is_foreground);

public:
	UnixExecutor(Unix *unix, TokenParser *parser);
	virtual ~UnixExecutor();
	virtual void execute(vector<string> &args) override;
	virtual void sigint() override;
	virtual void sigchild() override;
};

#endif
