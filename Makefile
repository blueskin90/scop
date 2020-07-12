# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2020/07/12 20:32:58 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

MLX = #./libs/mlx/libmlx.a 

LIBS = ./libs/libft/libft.a \
	   ./libs/ft_printf/libftprintf.a \
	  # ./libs/libftg/libftg.a \

INCLUDES = -I includes/ -I ./libs/mlx/ -I ./libs/libft/includes/ -I ./libs/ft_printf/includes/ -I/Users/toliver/.brew/Cellar/glfw/3.3.2/include

FLAGS = -Wall -Wextra -Werror -Ofast

MLXFLAGS = -framework OpenGL `pkg-config --static --libs glfw3`

OBJS = $(addprefix objs/, $(addsuffix .o, \
		$(addprefix core/, \
			main \
			parsing \
			singleton \
			error \
			) \
		)) 


HEADERS = includes/scop.h \

all: $(NAME)

$(NAME): libs objs $(OBJS) $(HEADERS)
	@printf "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
#	@make -C ./libs/mlx
#	@make -C ./libs/libft
#	@make -C ./libs/libftg
#	@make -C ./libs/ft_printf
	@gcc -o $(NAME) $(FLAGS) $(MLX) $(MLXFLAGS) $(LIBS) $(OBJS) $(INCLUDES)
	
objs/%.o: srcs/%.c
	@printf  "\033[1:92mCompiling $(NAME)\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@gcc -o $@ -c $< $(FLAGS) $(INCLUDES)
	@printf "\033[A\033[2K"

objs:
	@mkdir -p objs/core

clean:
#	@	make -C ./libs/mlx clean
#	@	make -C ./libs/libft clean
#	@	make -C ./libs/libftg clean
#	@	make -C ./libs/ft_printf clean
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -rf objs

fclean: clean
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@	rm -f $(NAME)
	@	rm -f $(MLX)
#	@	make -C ./libs/mlx clean
#	@	make -C ./libs/libft fclean
#	@	make -C ./libs/libftg fclean
#	@	make -C ./libs/ft_printf fclean

re:
	@$(MAKE) fclean
	@$(MAKE)
