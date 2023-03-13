# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 12:29:30 by ael-maar          #+#    #+#              #
#    Updated: 2023/03/13 10:38:09 by ael-maar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# MANDATORY SOURCE FILES 
PHILO_SRCS = run.c philo_utils.c libft.c initialize_shared_data.c init_threads.c \
free.c error.c check_args.c actions.c

# MANDATORY OBJECT FILES
PHILO_OBJS = $(PHILO_SRCS:%.c=%.o)

#EXTRA FLAGS FOR CC
CFLAGS = -Wall -Wextra -Werror

# FORCE REMOVE FILES
RM = rm -rf

# PROGRAM NAME
NAME = philo

all: $(NAME)

$(NAME): | $(PHILO_OBJS)
	@$(CC) $(CFLAGS) $| -o $@
	@echo "\n\033[32m <==== COMPILING MANDATORY SUCCESSFULY ====> \033[0m\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling object ==> \c"
	@echo $@
	@sleep 0.100

clean:
	@$(RM) $(PHILO_OBJS)
	@echo "\n\033[32m <==== CLEANED SUCCESSFULY ====> \033[0m\n"

fclean:
	@$(RM) $(PHILO_OBJS) $(NAME)
	@echo "\n\033[32m <==== FULLY CLEANED SUCCESSFULY ====> \033[0m\n"

re: fclean all

.PHONY: all clean fclean re
