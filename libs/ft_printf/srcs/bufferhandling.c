/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferhandling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 20:41:34 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:15 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <stdio.h>

void			buff_check(t_penv *env)
{
	if (env->buffi == BUFFSIZE)
	{
		env->buffilasttoken = env->buffi;
		buff_flush(env);
	}
}

void			buff_flush(t_penv *env)
{
	env->printflen += env->buffilasttoken;
	write(1, env->buff, env->buffilasttoken);
	env->buffi = 0;
	env->buffilasttoken = 0;
}
