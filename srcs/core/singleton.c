/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 20:10:59 by toliver           #+#    #+#             */
/*   Updated: 2020/07/13 00:23:30 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_env		*ft_getenv(void)
{
	static t_env	env = {
		NULL,
		{
			NULL,
			0,
			NULL,
			0,
			NULL,
		}
	};
	return (&env);
}
