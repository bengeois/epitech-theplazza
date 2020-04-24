##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## A simple Makefile
##

NAME	= plazza

SRC	=	src/Error/Error.cpp	\
		src/Parser/Parser.cpp	\
		src/Thread/Thread.cpp	\
		src/Mutex/Mutex.cpp	\
		src/Reception/Reception.cpp	\
		src/Reception/KitchenProcess.cpp	\
		src/UserShell/UserShell.cpp	\
		src/Pizza/APizza.cpp	\
		src/Pizza/Americana.cpp		\
		src/Pizza/Fantasia.cpp		\
		src/Pizza/Margarita.cpp		\
		src/Pizza/Regina.cpp		\
		src/Stock/Stock.cpp	\
		src/Kitchen/Kitchen.cpp	\
		src/Socket/Client.cpp	\
		src/Socket/Server.cpp	\
		src/Order/Order.cpp		\
		src/Utils/Utils.cpp		\
		src/File.cpp		\
		src/Process/Process.cpp		\
		src/IPC/Socket.cpp	\
		src/SmartBuffer/SmartBuffer.cpp	\
		src/LocalTime/LocalTime.cpp	\
		src/Factory/Factory.cpp		\

SRC_MAIN	=	src/main.cpp	\

NAME_TESTS	=	unit_test

SRC_TESTS =		$(SRC)	\
				tests/tests_redirect.cpp	\

CXXFLAGS += 	-W -Wall -Wextra -Iinclude -std=c++17

LDFLAGS = -lpthread

LDFLAGS_TESTS = -lcriterion --coverage	\

OBJ	=	$(SRC:.cpp=.o) $(SRC_MAIN:.cpp=.o)

OBJ_TESTS =	$(SRC_TESTS:.cpp=.o)

CC	=	g++

all:	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_TESTS)

fclean: clean
	rm -rf $(NAME)

rclean:
	rm -rf $(NAME_TESTS)
	find . -type f -name "*.gcno" -delete -or -name "*.gcda" -delete

tests_run: CXXFLAGS += -fprofile-arcs -ftest-coverage
tests_run: fclean $(OBJ_TESTS)
	$(CC) -o $(NAME_TESTS) $(OBJ_TESTS) $(LDFLAGS) $(LDFLAGS_TESTS)
	./$(NAME_TESTS)

functional_tests: re
	./tests/functional/tests.sh

coverage:
	sudo gcovr -e tests/

debug : CXXFLAGS += -g
debug : re

re: fclean all

.PHONY: all clean fclean re tests_run rclean functional_tests
