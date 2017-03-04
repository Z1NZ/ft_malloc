# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srabah <srabah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/04 20:11:58 by srabah            #+#    #+#              #
#    Updated: 2015/03/04 20:24:28 by srabah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Library output
NAME = libftprintf.a
NAME_TEST = test_pf

#	GCC flags
CFLAGS = -Werror
ALL_CFLAGS = -Wall -Wextra $(CFLAGS)

#	Includes directories
INC_LIBFT = libft/includes
INC_FT_PRINTF = includes
INCLUDES += $(addprefix -iquote , $(INC_LIBFT))
INCLUDES += $(addprefix -iquote , $(INC_FT_PRINTF))

#	Sources
FT_PRINTF_SOURCES = $(shell find lib | grep "\.c$$" | sed "s/\.c$$//g")
SRCS = $(addsuffix .c, $(FT_PRINTF_SOURCES))
OBJS = $(SRCS:.c=.o)

OBJS_LIBFT = $(shell ls -1 libft | grep -E ".\.o")
OBJS_LIBFT_FINAL = $(addprefix "libft/", $(OBJS_LIBFT))

all: $(NAME)

$(NAME): $(OBJS)
	@echo ">>>>> Génération de FT_PRINTF"
	make -C libft
	@$(AR) rcus $(NAME) $(OBJS) $(OBJS_LIBFT_FINAL)
	@echo "Terminée"

# To obtain object files
%.o: %.c
	$(CC) -c $(ALL_CFLAGS) $(INCLUDES) $< -o $@

# To remove generated files
clean:
	@echo "RM\ttous les objects (.o)"
	@$(RM) $(OBJS)

fclean: clean
	@echo "RM\tprojet ($(NAME))"
	@$(RM) $(NAME)

lftclean:
	make -C libft clean

lftfclean:
	make -C libft fclean

re: fclean all
