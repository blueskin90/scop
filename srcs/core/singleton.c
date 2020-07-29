/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 20:10:59 by toliver           #+#    #+#             */
/*   Updated: 2020/07/29 17:14:31 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_env	**ft_getenvptr(void)
{
	static t_env	*env = NULL;

	return (&env);
}

t_env			*ft_getenv(void)
{
	return (*ft_getenvptr());
}

void			ft_setenv(t_env *env)
{
	*(ft_getenvptr()) = env;
}
