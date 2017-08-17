EXEC	= test
CXX	= gcc
MAIN	= test.c
OPTIONS	= -O3 -Wall
LIBS	= -lufrn_lynx -lm

main:	clean
	$(CXX) $(OPTIONS) $(MAIN) -I./include/ -L./lib/ $(LIBS) -o $(EXEC) -ggdb

clean:
	clear
	rm -f include/*~
	rm -f lib/*~
	rm -f *~

