# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcharlsi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 12:32:59 by hcharlsi          #+#    #+#              #
#   Updated: 2021/12/24 20:45:34 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME = ft_container
TEST_NAME = ft_container_test

SRCS = main.cpp
DIR_SRCS = srcs
PATH_SRCS = $(addprefix $(DIR_SRCS)/, $(SRCS))

OBJS = $(patsubst %.cpp, %.o, $(SRCS))
DIR_OBJS = objs
PATH_OBJS = $(addprefix $(DIR_OBJS)/, $(OBJS))

HEADER = ft_algorithm.hpp \
         ft_containers.hpp \
         ft_iterator.hpp \
         ft_memory.hpp \
         ft_nullptr.hpp \
         ft_tree.hpp \
         ft_type_traits.hpp \
         ft_utility.hpp \
         ft_vector.hpp

DIR_HEADER = includes
PATH_HEADER = $(addprefix $(DIR_HEADER)/, $(HEADER))

CC = clang++
FLAGS = -Werror -Wextra -Wall -std=c++98 -g
RM = rm -rf

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): logo $(PATH_OBJS)
	@echo "$(GREEN)\nObjects were created $(RESET)"
	@$(CC) $(FLAGS) -I $(DIR_HEADER) $(PATH_OBJS) -o $@
	@echo "$(GREEN)\nft_containers was compiled $(RESET)"

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.cpp $(PATH_HEADER) Makefile
	@mkdir -p $(DIR_OBJS)
	@$(CC) $(FLAGS) -I $(DIR_HEADER) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

logo:
	@echo "$(GREEN)\n\
	 ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄    ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄ ▄▄▄ ▄▄    ▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄   ▄▄▄▄▄▄▄ \n\
    █       █       █  █       █       █  █  █ █       █      █   █  █  █ █       █   ▄  █ █       █\n\
    █    ▄▄▄█▄     ▄█  █       █   ▄   █   █▄█ █▄     ▄█  ▄   █   █   █▄█ █    ▄▄▄█  █ █ █ █  ▄▄▄▄▄█\n\
    █   █▄▄▄  █   █    █     ▄▄█  █ █  █       █ █   █ █ █▄█  █   █       █   █▄▄▄█   █▄▄█▄█ █▄▄▄▄▄ \n\
    █    ▄▄▄█ █   █    █    █  █  █▄█  █  ▄    █ █   █ █      █   █  ▄    █    ▄▄▄█    ▄▄  █▄▄▄▄▄  █\n\
    █   █     █   █    █    █▄▄█       █ █ █   █ █   █ █  ▄   █   █ █ █   █   █▄▄▄█   █  █ █▄▄▄▄▄█ █\n\
    █▄▄▄█     █▄▄▄█    █▄▄▄▄▄▄▄█▄▄▄▄▄▄▄█▄█  █▄▄█ █▄▄▄█ █▄█ █▄▄█▄▄▄█▄█  █▄▄█▄▄▄▄▄▄▄█▄▄▄█  █▄█▄▄▄▄▄▄▄█\n\
	$(RESET)"

clean:
	@$(RM) $(DIR_OBJS)
	@$(RM) $(DIR_TEST_OBJS)
	@echo "$(GREEN)clean instruction was executed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(TEST_NAME)
	@echo "$(GREEN)fclean instruction was executed$(RESET)"

re: fclean all

.PHONY: all logo clean fclean re test
