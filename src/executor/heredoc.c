/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 06:51:59 by mugenan           #+#    #+#             */
/*   Updated: 2025/08/04 06:54:34 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    is_redir_heredoc(t_redir *redir, t_cmd *cmds)
{
	while (redir)
	{
		if (redir->type == HEREDOC)
			//handle_heredoc(redir, cmds);
		redir = redir->next;
	}
}