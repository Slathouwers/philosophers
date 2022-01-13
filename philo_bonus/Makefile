# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 13:26:56 by slathouw          #+#    #+#              #
#    Updated: 2022/01/13 14:44:21 by slathouw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############
# VARIABLES #
#############

NAME 	= philo_bonus
INCLUDES= includes
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g 
LIBFLAGS = -lpthread 
OBJDIR	= obj

# ADD "SRCS" FILES HERE
SOURCES	= death.c free_destroy.c philo_bonus.c utils.c utils2.c init.c life.c utils3.c \
			monitor_launch.c
SRCDIR 	= srcs
SRCS 	= ${addprefix $(SRCDIR)/, $(SOURCES)}
OBJS	= ${addprefix $(OBJDIR)/srcs_, $(SOURCES:.c=.o)}

all : 		${NAME}

###############
# COMPILATION #
###############

# PHILO linking compilation
$(NAME) :	$(OBJS) includes/philo_bonus.h
	@${CC} ${CFLAGS} -I ${INCLUDES} ${OBJS} $(LIBFLAGS) -o ${NAME}
	@echo "philo_bonus binary created!"

# SRCS object compilation
$(OBJDIR)/srcs_%.o: $(SRCDIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@
	
clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@echo "philo_bonus objects removed..."

fclean: clean
	@rm -f $(NAME)
	@echo "philo_bonus binary removed..."


re :		fclean all

.PHONY: all clean fclean re
