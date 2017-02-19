#ifndef EXECUTOR
#define EXECUTOR

#include <vector>
#include <string>

using std::vector;
using std::string;

class Executor 
{
public:
	virtual void execute(vector<string> &args) = 0;
	virtual void sigint() = 0;
	virtual void sigchild() = 0;
	virtual ~Executor() {}
};

#endif
