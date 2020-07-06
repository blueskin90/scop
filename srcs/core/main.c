/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:36:21 by toliver           #+#    #+#             */
/*   Updated: 2020/06/18 11:36:35 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>

t_env		*ft_getenv(void)
{
	static t_env	env = {
		NULL
	};
	return (&env);
}

int		ft_error(int error, char *str)
{
	t_env	*env;

	env = ft_getenv();
	ft_printf("%s: %s", env->name, g_error_value[error]);
	if (error == INVALID_FILE || error ==  OPEN)
		ft_printf("%s", str);
	ft_printf("\n");
	return (error);
}



int	ft_glinit()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	} 

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	/* OTHER STUFF GOES HERE NEXT */

	// close GL context and any other GLFW resources
	glfwTerminate();
	return (0);
}

int		check_extension(char *file)
{
	int			i;
	
	if (file)
	{
		i = 0;
		while (file[i])
			i++;
		i-=4;
		if (i > 0 && ft_strcmp(file + i, ".obj") == 0)
		{
			ft_printf("correct file !\n");
			return (1);
		}
	}
	ft_error(INVALID_FILE, file);
	return (0);
}

int		open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_error(OPEN, path);
		return (-1);
	}
	return (fd);
}

void	obj_parse(t_env *env, int ac, char **av)
{
	int		fd;

	(void)env;
	while (ac > 0)
	{
		if  (check_extension(*av) && (fd = open_file(*av)) != -1)
		{
			ft_printf("start parsing !\n");	
		}
		av++;
		ac--;
	}
}
void	ft_usage(void)
{
	ft_printf("usage: ./scop -%s file.obj\n", FLAGS);
}

int		main(int ac, char **av)
{
	t_env	*env;

	env = ft_getenv();
	env->name = av[0];
	if (ac < 2)
	{
		ft_usage();
		return (-1);
	}
//		ft_error(&env, MALLOC);
//		ft_error(&env, NO_VALID_OBJ);
	obj_parse(env, ac - 1, av + 1);
	ft_glinit();
	return 0;
}
