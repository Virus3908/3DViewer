CLANG_FORMAT = ../materials/linters/.clang-format

clang:
	clang-format --style=file:$(CLANG_FORMAT) -i \
	$(wildcard ./controller/*.h) $(wildcard ./controller/*.cc) $(wildcard ./common/*.h) \
	$(wildcard ./backend/*.cc) $(wildcard ./backend/*.h) \
	$(wildcard ./gui/*.cc) $(wildcard ./gui/*.h) \
	$(wildcard ./backend/*/*.cc) $(wildcard ./backend/*/*.h) \
	$(wildcard ./gui/*/*.cc) $(wildcard ./gui/*/*.h) \

clang_check:
	clang-format --style=file:$(CLANG_FORMAT) -n \
	$(wildcard ./controller/*.h) $(wildcard ./controller/*.cc) $(wildcard ./common/*.h) \
	$(wildcard ./backend/*.cc) $(wildcard ./backend/*.h) \
	$(wildcard ./gui/*.cc) $(wildcard ./gui/*.h) \
	$(wildcard ./backend/*/*.cc) $(wildcard ./backend/*/*.h) \
	$(wildcard ./gui/*/*.cc) $(wildcard ./gui/*/*.h) \

check:
	cppcheck -q --enable=warning,portability --check-level=exhaustive --inconclusive ./

#.PHONY: all clean rebuild clang check

clean:

	rm -rf $(LIBS) $(TEST_LIB) *.o *.so *.a *.out ./gcov_obj *.info test.c test_gcov report ./obj test
	rm -rf ./doxygen
	rm -f *.txt
	rm -rf ./dist
	rm -rf ./gui/desktop.app
	rm -f ./gui/*.o
	rm -rf ./build
	rm -f ./gui/Makefile ./gui/desktop.pro.user ./gui/moc_predefs.h ./gui/ui_s21_ui.h ./gui/.qmake.stash ./gui/*.cpp
	

rebuild: clean all