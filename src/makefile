CC = gcc
CFLAGS_DEFOULT = -Wall -Wextra -pedantic -std=c11
CFLAGS_GTK = `pkg-config --cflags gtk+-3.0`
FLAGS_LINK_GTK = `pkg-config --libs gtk+-3.0`
FLAGS_X11 = -lX11 -lXtst
BIN_DIR = ../bin/
BUILD_DIR = ../build/
NAME = app
TEST_NAME = test

all : main

main : main.o start.o gtk_application.o clicer.o get_id_name_win.o file_rplus.o input.o
	$(CC) main.o start.o gtk_application.o clicer.o get_id_name_win.o file_rplus.o input.o -o $(BUILD_DIR)$(NAME) $(FLAGS_LINK_GTK) $(FLAGS_X11)

main.o : main/main.c main/main.h
	$(CC) -c $(CFLAGS_GTK) main/main.c -o main.o

start.o : main/start.c main/start.h
	$(CC) -c $(CFLAGS_GTK) main/start.c -o start.o

gtk_application.o : etc/gtk_application.c etc/gtk_application.h
	$(CC) -c $(CFLAGS_GTK) etc/gtk_application.c -o gtk_application.o

clicer.o : clicer/clicer.c clicer/clicer.h
	$(CC) -c $(CFLAGS_DEFOULT) $(CFLAGS_GTK) clicer/clicer.c $(FLAGS_X11) -o clicer.o

get_id_name_win.o : clicer/get_id_name_win.c clicer/get_id_name_win.h
	$(CC) -c $(CFLAGS_DEFOULT) clicer/get_id_name_win.c -o get_id_name_win.o $(FLAGS_X11)

file_rplus.o : clicer/file_rplus.c clicer/file_rplus.h
	$(CC) -c $(CFLAGS_DEFOULT) clicer/file_rplus.c -o file_rplus.o

input.o : input/input.c input/input.h
	$(CC) -c $(CFLAGS_DEFOULT) $(CFLAGS_GTK) input/input.c -o input.o $(FLAGS_X11)

clean_o :
	rm -rf *.o

clean_dat :
	rm -rf *.dat
	rm -rf config/*.dat

clean_conf :
	rm -rf *.conf
	rm -rf config/*.conf

clean_tst :
	rm -rf $(TEST_NAME)

clean : clean_o clean_dat clean_conf clean_tst
	rm -rf $(BUILD_DIR)*
	rm -rf $(BIN_DIR)*

rebuild : clean all

go :
	$(BUILD_DIR)$(NAME)

style_check :
	find . -name "*.c" -o -name "*.h" | xargs clang-format -n --style=Google

style :
	find . -name "*.c" -o -name "*.h" | xargs clang-format -i --style=Google

valgrind : clean
	make main && CK_FORK=no valgrind --vgdb=no --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --verbose --read-var-info=yes ./$(BUILD_DIR)$(NAME)