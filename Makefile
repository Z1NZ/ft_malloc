# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srabah <srabah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/11 18:45:23 by srabah            #+#    #+#              #
#    Updated: 2017/03/10 12:51:33 by srabah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#	Library output
NAME = libft_malloc.so

#	GCC flags
CFLAGS = -Wall -Wextra -Werror 
# -g -Weverything

#	Includes directories
INC_TR = includes
INCLUDES += $(addprefix -iquote , $(INC_TR))

#	Sources
MALLOC_SOURCES = $(shell find lib | grep "\.c$$" | sed "s/\.c$$//g")
SRCS = $(addsuffix .c, $(MALLOC_SOURCES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo ">>>>> Génération de malloc"
	@$(CC) $(OBJS) -shared -o $(NAME)
	@echo "Terminée"

# To obtain object files
%.o: %.c 
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

# To remove generated files
clean:
	@echo "RM\ttous les objects (.o)"
	@$(RM) $(OBJS)

fclean: clean
	@echo "RM\tprojet ($(NAME))"
	@$(RM) $(NAME)

re: fclean all

git:
	@git add .
	@echo "Enter Your Commit :"
	@read var1 ; git commit -m "$$var1"
	@git push