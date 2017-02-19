#ifndef UNIX_H
#define UNIX_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Unix {
private:

public:
	void stop_process(int pid);
	void resume_process(int pid);
	void kill_process(int pid);

	void get_files_in_path(vector<string> &files, 
					string &path);

	// return pid, 0 if have no dead process
	int get_dead_child_process();
	void wait_for_process(int pid);
	int create_process(string &exec_path, 
				vector<string> &args);
	int fork_process();
};

class Executor;
void signal_set_executor(Executor *e);
void set_signal_handlers();

#endif
