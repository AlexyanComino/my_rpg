##
## EPITECH PROJECT, 2024
## B-CPE-200-MPL-2-1-bsrobotfactory-alexyan.comino
## File description:
## Makefile
##

NAME	=	my_rpg

NAME_TESTS	=	unit_tests

SRCS	=	main.c

SRCS_TESTS	=	

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-W -Wall -Wextra -Werror -g3

CPPFLAGS	=	-I./include -I./B-CPE-200_op

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) *.cor
	$(RM) *.gcno
	$(RM) *.gcda

fclean:    clean
	$(RM) $(NAME)
	$(RM) $(NAME_TESTS)

re:    fclean all

tests_run:
	$(CC) -o $(NAME_TESTS) $(SRCS_TESTS) $(CPPFLAGS) --coverage -lcriterion
	./$(NAME_TESTS)
	gcovr --exclude tests/
	gcovr -b --exclude tests/
