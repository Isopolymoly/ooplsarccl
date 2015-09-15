CXX        := g++
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    :=  -pthread
GCOV       := gcov
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = /home/spa_training/gtest-1.7.0/

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

TESTS = TestCollatz

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h



clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunCollatz
	rm -f RunCollatz.tmp
	rm -f TestCollatz
	rm -f TestCollatz.tmp

config:
	git config -l

scrub:
	make  clean
	rm -f  Collatz.log
	rm -rf collatz-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunCollatz.tmp TestCollatz.tmp

RunCollatz: Collatz.h Collatz.c++ RunCollatz.c++ 
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Collatz.c++ RunCollatz.c++ -o RunCollatz

RunCollatz.tmp: RunCollatz
	./RunCollatz < RunCollatz.in > RunCollatz.tmp
	diff RunCollatz.tmp RunCollatz.out

TestCollatz: Collatz.h Collatz.c++ TestCollatz.c++ gtest_main.a $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS)  $(CXXFLAGS) $(GCOVFLAGS) Collatz.c++ TestCollatz.c++ -o TestCollatz $(LDFLAGS) gtest_main.a

TestCollatz.tmp: TestCollatz
	$(VALGRIND) ./TestCollatz                                       >  TestCollatz.tmp 2>&1
	$(GCOV) -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.tmp
	$(GCOV) -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.tmp
	cat TestCollatz.tmp
