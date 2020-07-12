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

int		add_vertexlist(t_vec4list **vertexlist, t_vec4 *ptr)
{
	t_vec4list	*node;
	t_vec4list	*listptr;

	if (!(node = malloc(sizeof(t_vec4list))))
	{
		ft_error(MALLOC, NULL);
		return (0);
	}
	ft_memcpy(&(node->vec), ptr, sizeof(t_vec4));
	node->next= NULL;
	if (*vertexlist == NULL)
		*vertexlist = node;
	else
	{
		listptr = *vertexlist;
		while (listptr->next)
			listptr = listptr->next;
		listptr->next = node;
	}
	return (1);
}

int		parse_vertex(char *line, t_vec4list **vertexlist, size_t *vertexnbr)
{
	t_vec4	vec;

	if (!parse_float(&line, &vec.x))
	{
		ft_error(PARSING_ERROR, line);
		return (0);
	}
	if (!parse_float(&line, &vec.y))
	{
		ft_error(PARSING_ERROR, line);
		return (0);
	}
	if (!parse_float(&line, &vec.z))
	{
		ft_error(PARSING_ERROR, line);
		return (0);
	}
	vec.w = 1;
	if (!(add_vertexlist(vertexlist, &vec)))
		return (0);
	*vertexnbr = (*vertexnbr) + 1;
	return (1);
}

int		parse_face(char *line, t_vec3intlist **facelist, size_t *facenbr)
{
	line = ft_skip_spaces(line);
	(void)line;
	(void)facelist;
	(void)facenbr;
	return (1);
}

int		parse_name(char *line, t_obj *obj)
{
	if (obj->name)
	{
		ft_error(TOO_MANY_OBJECTS, line);
		return (0);
	}
	line = ft_skip_spaces(line);
	if (!(obj->name = ft_strdup(line)))
	{
		ft_error(MALLOC, NULL);
		return (0);
	}
	return (1);
}

int		parse_otherline(char *line)
{
	ft_printf("line NOT parsed : %s\n", line);
	return (1);
}	

int		parse_line(char *line, t_obj *obj)
{
	static t_vec3intlist	*facelist = NULL;
	static size_t			facenbr = 0;
	static t_vec4list		*vertexlist = NULL;
	static size_t			vertexnbr = 0;

	if (*line)
	{
		if (*line == '#')
			return (1);
		else if (*line == 'v')
			return (parse_vertex(line + 1, &vertexlist, &vertexnbr));
		else if (*line == 'f')
			return (parse_face(line + 1, &facelist, &facenbr));
		else if (*line == 'o')
			return (parse_name(line + 1, obj));
		else
			return (parse_otherline(line));
	}
	return (1);
}

int		parse_file(t_env *env, int fd)
{
	char	*line;
	int		retval;

	line = NULL;
	// changer avec un mode et faire un while mode
	while ((retval = ft_get_next_line(fd, &line)) > 0)
	{
		if (parse_line(line, &env->obj) == -1)
		{
			free(line);
			break;
		}
		free(line);
	}
	if (retval == -1)
	{
		ft_error(MALLOC, NULL);
		return (0);
	}
	return (1);
}

void	ft_dump_obj(t_obj *obj)
{
	ft_printf("Obj name : %s\n", obj->name);
	ft_printf("vertices nbr : %zu\n", obj->vertices_nbr);
	ft_printf("faces nbr : %zu\n", obj->faces_nbr);
}

int		obj_parse(t_env *env, char *file)
{
	int		fd;

	if  (check_extension(file) && (fd = open_file(file)) != -1)
	{
		if (!(parse_file(env, fd)))
			return (0);
	}
	ft_dump_obj(&env->obj);
	return (1);
}
