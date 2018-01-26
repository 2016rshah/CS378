.PHONY: all
all: project

# This rule tells make how to build hello from hello.cpp
project: project.cpp
	g++ -o project project.cpp -lpthread

# This rule tells make to delete hello and hello.o
.PHONY: clean
clean:
	rm -f project
