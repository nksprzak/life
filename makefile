FILES :=                              \
    .travis.yml                       \
    Life.h                        \
    html                              \
    TestLife.c++                    \
    TestLife.out                    \
    Life.c++

CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread 
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
VALGRIND   := valgrind 

check:
	@not_found=0;                                 \
    for i in $(FILES);                            \
    do                                            \
        if [ -e $$i ];                            \
        then                                      \
            echo "$$i found";                     \
        else                                      \
            echo "$$i NOT FOUND";                 \
            not_found=`expr "$$not_found" + "1"`; \
        fi                                        \
    done;                                         \
    if [ $$not_found -ne 0 ];                     \
    then                                          \
        echo "$$not_found failures";              \
        exit 1;                                   \
    fi;                                           \
    echo "success";

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f TestLife
	rm -f TestLife.tmp
	rm -f RunLife

config:
	git config -l

scrub:
	make clean
	rm -f  Life.log
	rm -rf Life-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: TestLife.out

life-tests:
	git clone https://github.com/cs371p-fall-2015/life-tests.git

html: Doxyfile Life.h TestLife.c++
	doxygen Doxyfile

Life.log:
	git log > life.log

Doxyfile:
	doxygen -g

TestLife: Life.h TestLife.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) TestLife.c++ Life.c++ -o TestLife $(LDFLAGS)

TestLife.out: TestLife
	$(VALGRIND) ./TestLife                                       >  TestLife.out 2>&1
	$(GCOV) -b Life.c++ | grep -A 5 "File 'Life.c++'" >> TestLife.out
	$(GCOV) -b TestLife.c++ | grep -A 5 "File 'TestLife.c++'" >> TestLife.out
	cat TestLife.out
