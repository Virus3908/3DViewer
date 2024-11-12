OS = $(shell uname)
CC = gcc
CXX = g++
GCOV = gcov
ifeq ("$(OS)","Linux")
	LEAKS_RUN_TEST = valgrind --tool=memcheck --leak-check=yes --log-file=1.txt ./test
	PKG =`pkg-config --cflags --libs gtest`
else
	LEAKS_RUN_TEST = leaks -atExit -- ./test
	PKG =`pkg-config --cflags --libs gtest gtest_main`
endif

CSTD = -std=c11
CXXSTD = -std=c++17
CFLAGS = -Wall -Werror -Wextra -pedantic
EXTRA_LIBS = -lm $(PKG)

BACKEND_CC = $(wildcard ./backend/*.cc) $(wildcard ./backend/model/*.cc) $(wildcard ./backend/matrix/*.cc) $(wildcard ./backend/transform/*.cc)
CONTROLLER = $(wildcard ./controller/*.cc)

OBJECTS_GCOV_CC = $(addprefix gcov_obj/,$(BACKEND_CC:.cc=.o)) $(addprefix gcov_obj/,$(CONTROLLER:.cc=.o))

TARGET = 3DViewer
OPEN_CMD = open



all: install

install:
	@mkdir -p ../build
	@cd ./gui && qmake && make && make clean && mv $(TARGET).app ../../build
	@make clean
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	# @clear

open:
	$(OPEN_CMD) ~/Desktop/$(TARGET).app
	../build/3DViewer.app/Contents/MacOS/3DViewer

uninstall: clean
	@rm -rf ./../build
	@rm -rf ~/Desktop/$(TARGET).app 

dist:
	tar -czvf $(TARGET).tar.gz ../src

dvi:
	doxygen
	$(OPEN_CMD) ./doxygen/html/index.html

include ./Makefiles/utilites.mk
include ./Makefiles/test.mk
include ./Makefiles/gcov_report.mk