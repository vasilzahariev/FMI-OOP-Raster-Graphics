#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
public:
	virtual std::string execute() = 0;
};

#endif // !COMMAND_H
