include = -I include
SRC = cmd_token_parser.cpp main.cpp token_parser.cpp \
	unix.cpp unix_executor.cpp
libs =  
main = shell

sources = $(SRC:%=src/%)
objs = $(SRC:%.cpp=objs/%.o)
depends = $(SRC:%.cpp=objs/%.cpp.d)

CC = g++ -std=c++11

all: $(main)

$(main): $(objs)
	$(CC) $^ -o $@ $(libs)

-include $(depends)

objs/%.cpp.d: src/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(include) -M $< -MT $(<:src/%.cpp=objs/%.o) -MF $@

objs/%.o: src/%.cpp
	$(CC) $(include) -c $< -o $@

clean: 
	rm -rf objs/*
	rm $(main)

.PHONY: all clean
