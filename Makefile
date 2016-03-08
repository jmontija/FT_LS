# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 17:28:13 by jmontija          #+#    #+#              #
#    Updated: 2016/03/08 22:55:22 by jmontija         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			=	ft_ls
COMPIL			=	gcc -Werror -Wextra -Wall

LIB_PATH		=	libft/
LIB				=	$(LIB_PATH)libft.a
LIB_LINK		=	-L $(LIB_PATH) -lft

INCLUDES		=	-I $(LIB_PATH)/includes -I ./includes
SRCS			+=	srcs/main.c
SRCS			+=	srcs/manager.c
SRCS			+=	srcs/lst_lib.c
SRCS			+=	srcs/launcher.c
SRCS			+=	srcs/organize_rights.c
SRCS			+=	srcs/organize_dir.c
SRCS			+=	srcs/organize_files.c
SRCS			+=	srcs/sort_arg.c
SRCS			+=	srcs/stuff_files.c
SRCS			+=	srcs/opt_set.c
SRCS			+=	srcs/opt_1tr.c
SRCS			+=	srcs/opt_l.c
SRCS			+=	srcs/define_space.c

OBJS			=	$(SRCS:srcs/%.c=srco/%.o)

all: srco $(NAME)

srco:
	@mkdir -p srco

$(NAME): $(LIB) $(OBJS)
	@$(COMPIL) -o $@ $^ $(LIB_LINK)
	@echo "Compiled" $(NAME) "done"

$(LIB):
	@make -C $(LIB_PATH)
	@echo "Created libft.a"

srco/%.o: srcs/%.c ./includes/*.h
	@$(COMPIL) $(INCLUDES) -c -o $@ $<

clean:
	@rm -f $(OBJS)
	@rm -rf srco
	@echo "Cleaning" $(NAME)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo "Delete" $(NAME)

re: fclean all
