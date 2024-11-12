FREE_TEST_C = rm -rf test.c test.o 
TEST_CC = $(wildcard ./tests/*.cc)
TEST_FLAGS = -lgtest_main



%.o: %.cc
	mkdir -p obj
	$(CXX) $(CXXSTD) $(CFLAGS) -g -c $< -o obj/$(@F)

test.o:
	mkdir -p obj
	$(CXX) $(CXXSTD) $(CFLAGS) -g -c $(TEST_CC) -o ./obj/test.o

test: clean test.o $(BACKEND_CC:.cc=.o) $(CONTROLLER:.cc=.o)
	$(CXX) $(CFLAGS) $(CXXSTD) $(wildcard ./obj/*.o) -o test $(EXTRA_LIBS)
	./test


leak_test: clean test.o $(BACKEND_CC:.cc=.o) $(CONTROLLER:.cc=.o)
	$(CXX) $(CFLAGS) $(CXXSTD) $(wildcard ./obj/*.o) -o test $(EXTRA_LIBS)
	$(LEAKS_RUN_TEST)
	$(FREE_TEST)
