#include <unix.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <dirent.h>
#include <cstring>
#include <executor.h>

void Unix::stop_process(int __pid) 
{
	pid_t pid = (pid_t)__pid;
	kill(pid, SIGSTOP);
}

void Unix::resume_process(int __pid) 
{
	pid_t pid = (pid_t)__pid;
	kill(pid, SIGCONT);
}

void Unix::kill_process(int __pid) 
{
	pid_t pid = (pid_t)__pid;
	kill(pid, SIGKILL);
}

void Unix::get_files_in_path(vector<string> &files, 
				string &path) 
{
	files.clear();
	DIR *d;
	struct dirent *dir;
	d = opendir(path.c_str());
	if (d) {
		while ((dir = readdir(d)) != NULL) 
			files.push_back(dir->d_name);
		closedir(d);
	}
}

int Unix::get_dead_child_process() 
{
	int stat;
	pid_t pid = waitpid(-1, &stat, WNOHANG);
	return pid;
}

void Unix::wait_for_process(int pid)
{
	int stat;
	waitpid((pid_t)pid, &stat, 0);
}

int Unix::create_process(string &exec_path, vector<string> &args)
{
	pid_t pid = fork();
	if (pid == -1)
		exit(1);
	
	if (pid == 0) {
		signal(SIGINT, SIG_IGN);

		char *argv[30];
		int i;

		for (i = 0; i < args.size(); i++)
			argv[i] = (char *)args[i].c_str();
		argv[i] = NULL;
		execv(exec_path.c_str(), argv);
		exit(0);
	}

	return pid;
}

int Unix::fork_process() 
{
	pid_t pid = fork();
	if (pid == -1)
		exit(1);
	return pid;
}	

static Executor *exec;

void signal_set_executor(Executor *e) 
{
	exec = e;
}

void sigint_handler(int signum)
{
	exec->sigint();
}

void sigchild_handler(int signum) 
{
	exec->sigchild();
}

void set_signal_handlers()
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR) {
		exit(1);
	}

	if (signal(SIGCHLD, sigchild_handler) == SIG_ERR) {
		exit(1);
	}
}
