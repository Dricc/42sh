/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:52:15 by thugo             #+#    #+#             */
/*   Updated: 2018/01/19 19:13:56 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer_types.h"

/*
**	string (char *); Token id (t_token_id);
*/

const t_token_assign	g_token_operator[] = {
	{"&&", AND_IF},
	{"&", AND},
	{"(", LPAR},
	{")", RPAR},
	{";;", DSEMI},
	{";", SEMI},
	{"\n", NEWLINE},
	{"||", OR_IF},
	{"|", PIPE},
	{"<<", DLESS},
	{">>", DGREAT},
	{"<&", LESSAND},
	{">&", GREATAND},
	{"<<-", DLESSDASH},
	{"<>", LESSGREAT},
	{">|", CLOBBER},
	{"<", LESS},
	{">", GREAT},
	{NULL, 0}
};

const t_token_assign	g_token_reserved[] = {
	{"if", If},
	{"then", Then},
	{"else", Else},
	{"elif", Elif},
	{"fi", Fi},
	{"done", Done},
	{"do", Do},
	{"case", Case},
	{"esac", Esac},
	{"while", While},
	{"until", Until},
	{"for", For},
	{NULL, 0}
};
