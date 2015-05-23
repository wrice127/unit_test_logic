# Makefile written by Jae Hyuk Kwak
CC=g++-4.7
CFLAGS=-Wall -g -std=c++11
ExtCompileTest=compile_had_to_fail
FailTestMacro=

all: test_0

test_0: *.hpp stdafx.h.gch test_0.cpp
	$(CC) $(CFLAGS) $(LIBS) test_0.cpp -o test_0

stdafx.h.gch: stdafx.h
	$(CC) $(CFLAGS) -c stdafx.h

clean:
	rm stdafx.h.gch test_0 *.$(ExtCompileTest)

fail_0: *.hpp stdafx.h.gch test_0.cpp
	echo **** Fail test 1 *****
	- $(CC) $(CFLAGS) $(LIBS) test_0.cpp -o test_0.$(ExtCompileTest) -DCOMPILE_FAIL_TEST=1
	echo **** Fail test 2 *****
	- $(CC) $(CFLAGS) $(LIBS) test_0.cpp -o test_0.$(ExtCompileTest) -DCOMPILE_FAIL_TEST=2
