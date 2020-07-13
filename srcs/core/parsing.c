/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 20:11:35 by toliver           #+#    #+#             */
/*   Updated: 2020/07/13 01:19:36 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
			return (1);
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

char	*ft_skip_spaces(char *line)
{
	while (*line && (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\r' || *line == '\v' || *line == '\f'))
		line++;
	return (line);
}

int		parse_float(char **line, float *value)
{
	char	*tmp;

	*line = ft_skip_spaces(*line);
	if (*value == '\0')
		return (0);
	*value = strtof(*line, &tmp);
	if (tmp == *line)
		return (0);
	*line = tmp;
	return (1);
}

int		ft_parsing_error(char *line, int *mode)
{
	ft_error(UNEXPECTED_TOKEN, line);
	*mode = ERR;
	return (0);
}

int		count_indices(size_t *size, char *line, int *mode)
{
	*size = 0;
	while (*line)
	{
		if (*line != '-' && !ft_isdigit(*line))
			return (ft_parsing_error(line, mode));
		if (*line == '-' && !ft_isdigit(*(line + 1)))
			return (ft_parsing_error(line + 1, mode));
		if (*line == '-')
			line++;
		*size += 1;
		while (ft_isdigit(*line))
			line++;
		line = ft_skip_spaces(line);
	}
	if (*size < 3)
	{
		ft_error(NOT_ENOUGH_INDICES, NULL);
		return (0);
	}
	return (1);
}

int		*alloc_indice_arr(size_t *size, char *line, int *mode)
{
	int		*arr;

	*size = 0;
	if (!(count_indices(size, line, mode)))
		return (NULL);
	if ((*size) * sizeof(int) / (*size) != sizeof(int))
	{
		ft_error(OVERFLOW, NULL);
		*mode = ERR;
		return (NULL);
	}
	if (!(arr = (int*)malloc(sizeof(int) * (*size))))
	{
		ft_error(MALLOC, NULL);
		*mode = ERR;
		return (NULL);
	}
	return (arr);
}

int		parse_indices(int *arr, char *line, int vertex_max, int *mode)
{
	long long int	value;

	while (*line)
	{
		value = strtoll(line, &line, 10);
		if ((value < 0 && -(value) > vertex_max) || value > vertex_max || value > INT_MAX || value < INT_MIN)
		{
			*mode = ERR;
			ft_error(WRONG_FACE_VALUE, NULL);
			return (0);
		}
		*arr = value;
		line = ft_skip_spaces(line);
		arr++;
	}
	return (1);
}

	

int		add_face(size_t size, int *arr, t_obj *obj, int *mode)
{
	if (obj->faces_arr_size == obj->faces_nbr)
	{
		obj->faces_arr_size += 50;
		if (obj->faces_arr_size < 50)
		{
			*mode = ERR;
			ft_error(OVERFLOW, NULL);
			return (0);
		}
		obj->faces = (t_face*)realloc(obj->faces,
				sizeof(t_face) * obj->faces_arr_size);
		if (obj->faces == NULL)
		{
			*mode = ERR;
			ft_error(MALLOC, NULL);
			return (0);
		}
	}
	obj->faces[obj->faces_nbr].size = size;
	obj->faces[obj->faces_nbr].arr = arr;
	obj->faces_nbr += 1;
	return (1);
}

int		parse_face(char *line, t_obj *obj, int *mode)
{
	int		*arr;
	size_t	size;

	if (*mode == INIT)
		return (ft_parsing_error(line, mode));
	if (*mode == VERT)
		*mode = FACE;
	line = ft_skip_spaces(line + 1);
	if (!(arr = alloc_indice_arr(&size, line, mode)))
		return (0);
	if (!(parse_indices(arr, line, obj->vertices_nbr, mode)))
	{
		free(arr);
		return(0);
	}
	if (!(add_face(size, arr, obj, mode)))
	{
		free(arr);
		return (0);
	}
	return (1);
}

int		add_vertex(t_vec4 *vec, t_obj *obj, int *mode)
{
	if (obj->vertices_arr_size == obj->vertices_nbr)
	{
		obj->vertices_arr_size += 50;
		if (obj->vertices_arr_size < 50)
		{
			*mode = ERR;
			ft_error(OVERFLOW, NULL);
			return (0);
		}
		obj->vertices = (t_vec4*)realloc(obj->vertices,
				sizeof(t_vec4) * obj->vertices_arr_size);
		if (obj->vertices == NULL)
		{
			*mode = ERR;
			ft_error(MALLOC, NULL);
			return (0);
		}
	}
	obj->vertices[obj->vertices_nbr] = *vec;
	obj->vertices_nbr += 1;
	return (1);
}

int		parse_vertex(char *line, t_obj *obj, int *mode)
{
	t_vec4	vec;

	if  (*mode != INIT && *mode != VERT)
		return (ft_parsing_error(line, mode));
	*mode = VERT;
	line += 1;
	if (!parse_float(&line, &vec.x))
		return (ft_parsing_error(line, mode));
	if (!parse_float(&line, &vec.y))
		return (ft_parsing_error(line, mode));
	if (!parse_float(&line, &vec.z))
		return (ft_parsing_error(line, mode));
	vec.w = 1;
	add_vertex(&vec, obj, mode);
	return (1);
}


void	parse_name(char *line, t_obj *obj, int *mode)
{
	if (*mode != INIT)
	{
		ft_error(UNEXPECTED_TOKEN, line);
		*mode = ERR;
		return ;
	}
	if (obj->name)
	{
		ft_error(TOO_MANY_OBJECTS, line);
		*mode = ERR;
		return ;
	}
	line = ft_skip_spaces(line + 1);
	if (!(obj->name = ft_strdup(line)))
	{
		ft_error(MALLOC, NULL);
		*mode = ERR;
	}
}


void	parse_line(t_env *env, char *line, int *mode)
{
	line = ft_skip_spaces(line);
	if (*line == '#')
		return ;
	if (ft_strncmp(line, "mtllib", 6) == 0)
	{
		ft_printf("parsing material lib not yet implemented, line = %s\n", line);
		return ;
	}
	if (ft_strncmp(line, "usemtl", 6) == 0)
	{
		ft_printf("parsing using material not yet implemented, line = %s\n", line);
		return ;
	}
	if (*line != 'v' && *line != 'f' && *line != 'o')
	{
		ft_printf("parsing for this not yet implemented, line = %s\n", line);
		return ;
	}
	if (*line == 'o')
		parse_name(line, &env->obj, mode);
	else if (*line == 'v')
		parse_vertex(line, &env->obj, mode);
	else if (*line == 'f')
		parse_face(line, &env->obj, mode);	
}

int		parse_file(t_env *env, int fd)
{
	int		mode;
	char	*line;
	int		retval;

	mode = INIT;
	while (mode != ERR && mode != END)
	{
		retval = ft_get_next_line(fd, &line);
		if (retval == -1)
		{
			ft_error(MALLOC, NULL);
			mode = ERR;
		}
		else if (retval == 0)
			mode = END;
		parse_line(env, line, &mode);
		free(line);
	}
	if (mode == ERR)
		return (0);
	return (1);
}

void	ft_dump_obj(t_obj *obj)
{
	size_t	i;
	size_t	j;

	ft_printf("Obj name : %s\n", obj->name);
	ft_printf("vertices nbr : %zu\n", obj->vertices_nbr);
	i = 0;
	while (i < obj->vertices_nbr)
	{
		ft_printf("vertex %zu : [%f][%f][%f][%f]\n", i  + 1, obj->vertices[i].x, obj->vertices[i].y, obj->vertices[i].z, obj->vertices[i].w);
		i++;
	}
	ft_printf("faces nbr : %zu\n", obj->faces_nbr);
	i = 0;
	while (i < obj->faces_nbr)
	{
		ft_printf("face %zu : %zu indices", i + 1, obj->faces[i].size);
		j = 0;
		while (j < obj->faces[i].size)
		{
			ft_printf(" [%d]", obj->faces[i].arr[j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int		obj_parse(t_env *env, char *file)
{
	int		fd;

	if (check_extension(file) == 0)
		return (0);
	if  ((fd = open_file(file)) == -1)
		return (0);
	if (!(parse_file(env, fd)))
		return(0);
	ft_dump_obj(&env->obj);
	return (1);
}
