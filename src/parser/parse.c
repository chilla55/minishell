/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:44:00 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/21 23:39:07 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*squote_parse(char *input, int *i)
{
	int		a;
	char	*tmp;

	a = 1;
	while (input[a + i[0]] != '\'' && input[a + i[0]])
		a++;
	tmp = ft_substr(input, i[0] + 1, a - 1);
	i[0] = i[0] + a;
	i[3] = i[0] + 1;
	return (tmp);
}

char	*env_parse(char *input, int *i, t_envp_list *envp_list)
{
	int		a;
	char	*tmp[2];

	a = 1;
	if (input[a + i[0]] == '?' && input[a + i[0] - 1] == '$')
		a++;
	else
	{
		while ((ft_isalnum(input[a + i[0]]) || input[a + i[0]] == '_')
			&& input[a + i[0]])
			a++;
		a--;
	}
	if (!ft_isdigit(input[*i + 1]))
	{
		tmp[0] = ft_substr(input, i[0] + 1, a);
		tmp[1] = msh_get_envp_value(envp_list, tmp[0]);
		free (tmp[0]);
		i[0] = a + i[0];
		i[3] = i[0] + 1;
		return (ft_strdup(tmp[1]));
	}
	i[0] = 1 + i[0];
	i[3] = i[0] + 1;
	return (NULL);
}

char	*dqute_env_parse(char *input, int *i, t_envp_list *envp_list)
{
	int		a;
	char	*tmp;
	char	*ret;

	a = 1;
	if (input[a + *i] == '?' && input[a + *i - 1] == '$')
		a++;
	else
	{
		while ((ft_isalnum(input[a + i[0]]) || input[a + i[0]] == '_')
			&& input[a + i[0]])
			a++;
		a--;
	}
	if (!ft_isdigit(input[*i + 1]))
	{
		tmp = ft_substr(input, *i + 1, a);
		ret = msh_get_envp_value(envp_list, tmp);
		free (tmp);
		*i = a + *i;
		return (ft_strdup(ret));
	}
	*i = *i + 1;
	return (NULL);
}

char	*dquote_parse(char *input, int *i, t_envp_list *envp_list)
{
	int		a[2];
	char	*tmp;

	a[0] = i[0] + 1;
	a[1] = a[0];
	tmp = 0x0;
	while (input[a[1]] != '\"' && input[a[1]])
	{
		if (input[a[1]] == '$')
		{
			tmp = join_try_free(tmp, ft_substr(input, a[0], a[1] - a[0]));
			tmp = join_try_free(tmp,
					dqute_env_parse(input, &a[1], envp_list));
			a[0] = a[1] + 1;
		}
		a[1]++;
	}
	i[0] = a[1];
	i[3] = i[0] + 1;
	if (tmp && a[0] != a[1])
		return (join_try_free(tmp,
				ft_substr(input, a[0], a[1] - a[0])));
	else if (tmp)
		return (tmp);
	return (ft_substr(input, a[0], a[1] - a[0]));
}
