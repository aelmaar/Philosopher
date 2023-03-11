# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 16:40:18 by ael-maar          #+#    #+#              #
#    Updated: 2023/03/11 18:24:07 by ael-maar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BONUS SOURCE FILES 
PHILO_BONUS_SRCS = run.c philo_bonus_utils.c libft.c initialize_shared_data.c init_processes.c \
free.c check_args.c libft_extra.c

# BONUS OBJECT FILES
PHILO_BONUS_OBJS = $(PHILO_BONUS_SRCS:%.c=%.o)

#EXTRA FLAGS FOR CC
CFLAGS = -Wall -Wextra -Werror -c

# FORCE REMOVE FILES
RM = rm -rf

# PROGRAM NAME
NAME = philo_bonus

bonus: $(NAME)

$(NAME): | $(PHILO_BONUS_OBJS)
	@$(CC) $| -o $@
	@echo "\n\033[32m <==== COMPILING BONUS SUCCESSFULY ====> \033[0m\n"

%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@
	@echo "Compiling object ==> \c"
	@echo $@
	@sleep 0.100

clean:
	@$(RM) $(PHILO_BONUS_OBJS)
	@echo "\n\033[32m <==== CLEANED SUCCESSFULY ====> \033[0m\n"

fclean:
	@$(RM) $(PHILO_BONUS_OBJS) $(NAME)
	@echo "\n\033[32m <==== FULLY CLEANED SUCCESSFULY ====> \033[0m\n"

re: fclean bonus

.PHONY: bonus clean fclean re
