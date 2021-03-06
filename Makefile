# Makefile written by Jae Hyuk Kwak
CC=g++-4.7
CFLAGS=-Wall -g -std=c++11
ExtCompileTest=compile_had_to_fail
GREP=grep
assertMsg=static\ assertion\ failed
TESTS=test_0.o test_1.o test_2.o test_3.o test_4.o

all: $(TESTS)

test_0.o: *.hpp stdafx.h.gch test_0.cpp
	$(CC) $(CFLAGS) $(LIBS) test_0.cpp -o test_0.o

test_1.o: *.hpp stdafx.h.gch test_1.cpp
	$(CC) $(CFLAGS) $(LIBS) test_1.cpp -o test_1.o

test_2.o: *.hpp stdafx.h.gch test_2.cpp
	$(CC) $(CFLAGS) $(LIBS) test_2.cpp -o test_2.o

test_3.o: *.hpp stdafx.h.gch test_3.cpp
	$(CC) $(CFLAGS) $(LIBS) test_3.cpp -o test_3.o

test_4.o: *.hpp stdafx.h.gch test_4.cpp
	$(CC) $(CFLAGS) $(LIBS) test_4.cpp -o test_4.o

stdafx.h.gch: stdafx.h
	$(CC) $(CFLAGS) -c stdafx.h

clean:
	- rm stdafx.h.gch $(TESTS) *.$(ExtCompileTest) 2> /dev/null

fail: *.hpp stdafx.h.gch test_2.cpp
	@echo ===== Fail test 1 =====
	@$(CC) $(CFLAGS) $(LIBS) test_2.cpp -o test_2.$(ExtCompileTest) -DCOMPILE_FAIL_TEST=1 2>&1 | $(GREP) $(assertMsg)
	@echo ===== Fail test 2 =====
	@$(CC) $(CFLAGS) $(LIBS) test_2.cpp -o test_2.$(ExtCompileTest) -DCOMPILE_FAIL_TEST=2 2>&1 | $(GREP) $(assertMsg)
	@echo ===== Fail test 3 =====
	@$(CC) $(CFLAGS) $(LIBS) test_2.cpp -o test_2.$(ExtCompileTest) -DCOMPILE_FAIL_TEST=3 2>&1 | $(GREP) $(assertMsg)
	@echo ===== Fail test 4 =====
	@$(CC) $(CFLAGS) $(LIBS) test_2.cpp -o test_2.$(ExtCompileTest) -DCOMPILE_FAIL_TEST=4 2>&1 | $(GREP) $(assertMsg)
	@echo ===== Fail test 5 =====
	@$(CC) $(CFLAGS) $(LIBS) test_2.cpp -o test_2.$(ExtCompileTest) -DCOMPILE_FAIL_TEST=5 2>&1 | $(GREP) $(assertMsg)
	@echo ===== Fail test 6 =====
	@$(CC) $(CFLAGS) $(LIBS) test_2.cpp -o test_2.$(ExtCompileTest) -DCOMPILE_FAIL_TEST=6 2>&1 | $(GREP) $(assertMsg)
	@echo ===== Fail test 7 =====
	@$(CC) $(CFLAGS) $(LIBS) test_2.cpp -o test_2.$(ExtCompileTest) -DCOMPILE_FAIL_TEST=7 2>&1 | $(GREP) $(assertMsg)
	@echo ===== Fail test 8 =====
	@$(CC) $(CFLAGS) $(LIBS) test_3.cpp -o test_3.$(ExtCompileTest) -DCOMPILE_FAIL_TEST=1 2>&1 | $(GREP) $(assertMsg)

test: $(TESTS)
	./test_0.o
	./test_1.o
	./test_2.o
	./test_3.o
	./test_4.o
