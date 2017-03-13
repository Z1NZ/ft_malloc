# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srabah <srabah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/11 18:45:23 by srabah            #+#    #+#              #
#    Updated: 2017/03/12 09:02:20 by srabah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

#	Library output
LIB_NAME = libft_malloc_$(HOSTTYPE).so
NAME = libft_malloc.so

#	GCC flags
CFLAGS = -Wall -Wextra -Werror 
#-Weverything

#	Includes directories
INC_TR = includes
INCLUDES += $(addprefix -iquote , $(INC_TR))

#	Sources
MALLOC_SOURCES = $(shell find lib | grep "\.c$$" | sed "s/\.c$$//g")
MALLOC_HEADERS = $(shell find includes | grep "\.h$$")
SRCS = $(addsuffix .c, $(MALLOC_SOURCES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo ">>>>> Génération de malloc"
	@$(CC) $(OBJS) -shared -o $(LIB_NAME)
	@ln -s $(LIB_NAME) $(NAME)
	@echo "Terminée"

# To obtain object files
%.o: %.c $(MALLOC_HEADERS)
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

# To remove generated files
clean:
	@echo "RM\ttous les objects (.o)"
	@$(RM) $(OBJS)

fclean: clean
	@echo "RM\tprojet ($(NAME))"
	@$(RM) $(NAME) $(LIB_NAME)

re: fclean all

git:
	@git add .
	@echo "Enter Your Commit :"
	@read var1 ; git commit -m "$$var1"
	@git push