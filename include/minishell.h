/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguney <iguney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:19:03 by iguney            #+#    #+#             */
/*   Updated: 2025/08/03 20:19:05 by iguney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINSHELL_H

# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"
# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

char		*prompt(void);
void		process(char *input);
int			has_unclosed_quotes(const char *input);

#endif