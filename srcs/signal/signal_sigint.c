/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 14:50:28 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/08 15:43:22 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include "sh_signal.h"

void		signal_sigint(int sig, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	(void)sig;
	g_new_prompt = 1;
	g_sh.exitstatus = 1;
}
