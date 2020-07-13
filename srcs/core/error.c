/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 20:33:13 by toliver           #+#    #+#             */
/*   Updated: 2020/07/13 01:19:37 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const char * const g_error_value[MAXVALUE + 1] =
{
	"malloc failed",
	"no valid .obj file given",
	"invalid file was given:  ",
	"couldn't open file: ",
	"can't handle multi object files, new object : ",
	"Error while parsing: ",
	"Unexpected token while parsing: ",
	"A value overflowed",
	"Not enough indices for face definition",
	"Wrong face indice value",
	"No faces given",
	0
}; 

int		ft_error(int error, char *str)
{
	t_env	*env;

	env = ft_getenv();
	ft_printf("%s: %s", env->name, g_error_value[error]);
	if (error == INVALID_FILE || error ==  OPEN || error == TOO_MANY_OBJECTS || error == PARSING_ERROR || error == UNEXPECTED_TOKEN)
		ft_printf(" %s", str);
	if (error < TOO_MANY_OBJECTS && error != INVALID_FILE)
		ft_printf(" :%s\n", strerror(errno));
	if (error == INVALID_FILE)
		ft_printf("\n");
	return (0);
}
