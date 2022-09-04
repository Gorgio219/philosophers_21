NAME	=	philo

SRCS	=	philo.c	\
			philo_utils.c \
			philo_init.c \
			philo_life.c

OBJ		=	$(SRCS:%.c=%.o)

INCLUDE	=	include/

HEADER	=	philo.h

CC		=	gcc

FLAGS	=	-g -Wall -Wextra -Werror

RM		= rm -rf

.PHONY:		all	clean	fclean	re	libft

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o:		%.c $(INCLUDE)$(HEADER)
			$(CC) $(FLAGS)  -c $< -o $@ -I $(INCLUDE)

clean:
			@$(RM) $(OBJ) $(OBJ_B)

fclean:		clean
			@$(RM) $(NAME) $(NAME_B)

re:			fclean all

