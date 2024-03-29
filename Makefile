# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2022/01/17 16:08:57 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

INCLUDES = -I ./includes/ -I /Users/toliver/homebrew/include/ -I ~/.linuxbrew/include/ 

FLAGS = -Wall -Wextra -Werror -Ofast -fsanitize=address 


ifeq ($(shell uname), Linux)

FRAMEWORK_FLAGS = -lm -lGL `pkg-config --static --libs glfw3`

endif

ifeq ($(shell uname), Darwin)

FRAMEWORK_FLAGS = -framework OpenGL `pkg-config --static --libs glfw3`

endif

OBJS = $(addprefix objs/, $(addsuffix .o, \
		$(addprefix core/, \
			main \
			callbacks \
			init \
			) \
		$(addprefix classes/, \
			Obj \
			Vector \
			Vector3int \
			Matrix \
			Model \
			Camera \
			Mouse \
			Shader \
			Time \
		) \
)) 


TESTOBJS = $(addprefix objs/, $(addsuffix .o, \
		$(addprefix core/, \
			callbacks \
			init \
			) \
		$(addprefix classes/, \
			Obj \
			Vector \
			Vector3int \
			Matrix \
			Model \
			Camera \
			Mouse \
			Shader \
			Time \
			) \
		$(addprefix test/, \
			main \
			)\
)) 



HEADERS = includes/scop.hpp \
		  includes/Vector.hpp \
		  includes/Vector3int.hpp \
		  includes/Obj.hpp \
		  includes/Camera.hpp \
		  includes/Matrix.hpp \
		  includes/Model.hpp \
		  includes/Mouse.hpp \
		  includes/Time.hpp \
		  includes/Shader.hpp \
		  includes/glincludes.hpp \

all: $(NAME)

$(NAME): objs $(OBJS) $(HEADERS)
	@printf "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	clang++ -o $(NAME) $(FLAGS) $(FRAMEWORK_FLAGS) $(LIBS) $(OBJS) $(INCLUDES)


test: objs $(TESTOBJS) $(HEADERS)
	@printf "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	clang++ -o testscop $(FLAGS) $(FRAMEWORK_FLAGS) $(LIBS) $(TESTOBJS) $(INCLUDES)

	
objs/%.o: srcs/%.cpp
	@printf  "\033[1:92mCompiling $(NAME)\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@clang++ -o $@ -c $< $(FLAGS) $(INCLUDES)
	@printf "\033[A\033[2K"

objs:
	@mkdir -p objs/core
	@mkdir -p objs/classes
	@mkdir -p objs/test #a supprimer apres

clean:
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -rf objs

fclean: clean
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@	rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE)
