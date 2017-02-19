#include <unix.h>
#include <unix_executor.h>
#include <printf_color.h>
#include <token_parser.h>
#include <stdio.h>
#include <cstring>

UnixExecutor::UnixExecutor(Unix *unix, TokenParser *parser) 
{
	this->parser = parser;
	this->unix = unix;

	paths.clear();
	system_cmds.clear();
	bg_processes.clear();
	
	init_paths();
	init_system_cmds();
}

void UnixExecutor::init_paths() 
{
	paths.push_back("/bin");
	paths.push_back("bin");
	paths.push_back(".");
}

void UnixExecutor::init_system_cmds() 
{
	init_cmd_exit();
	init_cmd_help();
	init_cmd_path();
	init_cmd_addpath();
	init_cmd_list();
	init_cmd_kill();
	init_cmd_stop();
	init_cmd_resume();
}

void UnixExecutor::init_cmd_exit() 
{
	system_cmds["exit"] = [this](vector<string> &args) {
		for (auto &p: bg_processes) 
			unix->kill_process(p.pid);
		exit(0);
	};
}

void UnixExecutor::init_cmd_help()
{
	system_cmds["help"] = [this](vector<string> &args) {
		printf(PFRED "Help section\n" PFNORMAL);
	};
}

void UnixExecutor::init_cmd_path()
{
	system_cmds["path"] = [this](vector<string> &args) {
		printf(PFGREEN "Number of paths: %ld\n" PFNORMAL, 
				paths.size());
		for (auto &p: paths) 
			printf(PFMAGENTA "%s\n" PFNORMAL,
					p.c_str());
	};
}

void UnixExecutor::init_cmd_addpath()
{
	system_cmds["addpath"] = [this](vector<string> &args) {
		for (int i = 1; i < args.size(); i++)
			paths.push_back(args[i]);
	};
}

void UnixExecutor::init_cmd_list()
{
	system_cmds["list"] = [this](vector<string> &args) {
		printf(PFRED "%5s   %-10s   %-8s\n" PFNORMAL,
				"pid", "command", "status");
		for (auto &s: bg_processes) 
			printf(PFGREEN "%5d   %-10s   %-8s\n"
				PFNORMAL, s.pid, s.cmd.c_str(),
				s.status.c_str());
	};
}

void UnixExecutor::init_cmd_kill()
{
	system_cmds["kill"] = [this](vector<string> &args) {
		if (args.size() == 1)
			return;
		int pid = std::stoi(args[1]);

		Process *p = 0;
		for (auto &e: bg_processes) 
			if (e.pid == pid) {
				p = &e;
				break;
			}

		if (p)
			unix->kill_process(pid);
		else 
			printf(PFRED "PID khong chinh xac!\n" 
				PFNORMAL);
	};
}

void UnixExecutor::init_cmd_stop()
{
	system_cmds["stop"] = [this](vector<string> &args) {
		if (args.size() == 1)
			return;
		int pid = std::stoi(args[1]);

		Process *p = 0;
		for (auto &e: bg_processes) 
			if (e.pid == pid) {
				p = &e;
				break;
			}

		if (p) {
			unix->stop_process(pid);
			p->status = "stopped";
		}
		else 
			printf(PFRED "PID khong chinh xac!\n" 
				PFNORMAL);
	};
}

void UnixExecutor::init_cmd_resume()
{
	system_cmds["resume"] = [this](vector<string> &args) {
		if (args.size() == 1)
			return;
		int pid = std::stoi(args[1]);

		Process *p = 0;
		for (auto &e: bg_processes) 
			if (e.pid == pid) {
				p = &e;
				break;
			}

		if (p) {
			unix->resume_process(pid);
			p->status = "running";
		}
		else 
			printf(PFRED "PID khong chinh xac!\n" 
				PFNORMAL);
	};
}

UnixExecutor::~UnixExecutor() 
{
}

void UnixExecutor::execute(vector<string> &args)
{
	if (args.size() == 0)
		return;
	bool is_foreground = args[args.size() - 1] != "&";
	if (!is_foreground)
		args.pop_back(); // remove &

	// execute system command
	if (system_cmds.find(args[0])
		!= system_cmds.end()) {
		system_cmds[args[0]](args);
		return;
	}

	string path = "";

	// search for path
	for (auto it = paths.rbegin(); it != paths.rend(); ++it) {
		vector<string> files;
		unix->get_files_in_path(files, *it);
		for (auto &f: files)
			if (f == args[0]) {
				path = *it + "/" + f;
				goto found_path;
			}
	}

found_path:
	
	if (path == "") {
		printf(PFRED "Lenh khong ton tai!\n" PFNORMAL);
		return;
	}

	if (is_bat_file(args[0])) {
		handle_bat(path, is_foreground);
		return;
	}

	int pid = unix->create_process(path, args);

	wait_or_discard(is_foreground, pid, args[0]);
}

void UnixExecutor::wait_or_discard(bool is_foreground, int pid,
					string cmd)
{
	if (is_foreground) {
		has_fg_process = true;
		fg_pid = pid;
		unix->wait_for_process(pid);
		has_fg_process = false;
	}
	else {
		struct Process p;
		p.pid = pid;
		p.cmd = cmd;
		p.status = "running";
		bg_processes.push_back(p);
	}
}

bool UnixExecutor::is_bat_file(string &file)
{
	if (file.length() < 5) {
		return false;
	}
	
	const char *cmd = file.c_str();
	cmd = cmd + strlen(cmd) - 4;
	string bat = cmd;
	if (bat == ".bat")
		return true;
	return false;
}

void UnixExecutor::handle_bat(string &path, bool is_foreground)
{
	int pid = unix->fork_process();
	if (pid == 0) {
		FILE *fp = fopen(path.c_str(), "r");

		char buf[2048];
		while (fgets(buf, 1024, fp)) {
			int len = strlen(buf);
			buf[--len] = 0; // remove \n

			// convert string to tokens
			vector<string> args;
			string s = buf;
			parser->parse(s, args);

			this->execute(args);
		}

		fclose(fp);
		exit(0);
	}
	else 
		wait_or_discard(is_foreground, pid, "bat");
}

void UnixExecutor::sigint()
{
	if (has_fg_process) {
		unix->kill_process(fg_pid);
	}
}

void UnixExecutor::sigchild() 
{
	int pid = unix->get_dead_child_process();
	if (pid == 0)
		return;
	for (auto it = bg_processes.begin();	
		it != bg_processes.end(); ++it) {
		if (it->pid == pid) {
			bg_processes.erase(it);
			break;
		}
	}
}
