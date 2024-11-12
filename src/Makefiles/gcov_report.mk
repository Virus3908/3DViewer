GCOVFLAGS = --coverage


gcov_report: clean test.o $(OBJECTS_GCOV_CC)
	mkdir -p gcov_obj
	$(CXX) $(CXXSTD) $(CFLAGS) obj/test.o $(wildcard gcov_obj/*.o) -o gcov_obj/test_gcov $(GCOVFLAGS) $(PKG)
	gcov_obj/test_gcov
	mkdir report
	gcovr -r . --html --html-details -o ./report/index.html
	$(OPEN_CMD) ./report/index.html

gcov_obj/%.o: %.cc
	mkdir -p gcov_obj
	$(CXX) $(CXXSTD) $(CFLAGS) -c $< -o gcov_obj/$(@F) $(GCOVFLAGS)
