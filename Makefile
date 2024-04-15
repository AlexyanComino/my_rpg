##
## EPITECH PROJECT, 2024
## B-CPE-200-MPL-2-1-bsrobotfactory-alexyan.comino
## File description:
## Makefile
##

NAME	=	my_rpg

NAME_TESTS	=	unit_tests

SRCS    :=    $(shell find -name "*.c"    \
        -not -path "./tests/*")

SRCS_TESTS	=   $(shell find tests/ -name "*.c")

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-W -Wall -Wextra -Werror -g3

LDFLAGS	=	-lcsfml-graphics -lcsfml-system -lcsfml-window \
				-lcsfml-audio -lm

CPPFLAGS	=	-I./include

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
	$(RM) *.gc*

fclean:    clean
	$(RM) $(NAME)
	$(RM) $(NAME_TESTS)

re:    fclean all

tests_run:
	$(CC) -o $(NAME_TESTS) $(SRCS_TESTS) $(CPPFLAGS) --coverage -lcriterion
	./$(NAME_TESTS)
	gcovr --exclude tests/
	gcovr -b --exclude tests/
