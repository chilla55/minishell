/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 08:45:29 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/16 23:34:35 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*insert_here(char *temp, int *i_0);
static char	*ft_strinsertchar(char *str, char c, int pos);
static int	ft_find_word_end(char *temp, int i);

/*
** insert_pipes takes the input, searches for redirections and inserts pipes.
** The redirections are then executed like built-in functions
** in their own child processes.
**
** If a pipe is the first element of the input, echo -n "" is put in front.
** This is necessary to give the redirection an empty source/silent drain.
**
** When searching the input for < or >, quotes have to be interpreted.
** If an unquoted < or > is found, insert_here is started to change the
** input string as needed.
*/

char	*ft_insert_pipes(char *input)
{
	char	*temp;
	int		sq;
	int		dq;
	int		i;

	sq = 0;
	dq = 0;
	i = 0;
	temp = ft_strdup(input);
	if (temp[0] == '<' || temp[0] == '>')
		temp = ft_strjoin_frees2("echo -n \"\" ", temp);
	while (temp[i])
	{
		if (temp[i] == '\'' && !dq)
			sq = (sq + 1) % 2;
		else if (temp[i] == '\"' && !sq)
			dq = (dq + 1) % 2;
		else if ((temp[i] == '<' || temp[i] == '>') && !sq && !dq)
			temp = insert_here(temp, &i);
		if (temp[i])
			i++;
	}
	return (temp);
}

/*
** insert_here takes a string and the address of the index where
** in this string a redirection is found.
**
** It first checks if there has already been inserted a pipe '|' in front,
** and adds it if missing.
**
** If no space is between redirection and argument, it is inserted.
**
** The end of the argument word is located, and
** where necessary, a pipe '|' is inserted.
**
** The index is updated to the end of the current redirection,
** and the string is returned.
*/

char	*insert_here(char *temp, int *i_0)
{
	int	i;

	i = *i_0;
	if (i > 0)
	{
		if (temp[i - 1] == '|')
			i--;
		else
			temp = ft_strinsertchar(temp, '|', i);
	}
	if (temp[i + 2] == temp[i + 1])
		i++;
	i = i + 2;
	temp = ft_strinsertchar(temp, ' ', i);
	*i_0 = i;
	i = ft_find_word_end(temp, i);
	while (temp[i] == ' ')
		i++;
	if (temp[i] && temp[i] != '|')
		temp = ft_strinsertchar(temp, '|', i);
	return (temp);
}

/*
** sort_redirections takes the split input and switches every input redirection
** with the command in front of it.
**
** So, the output of the built-in redirection command will be piped
** into the input of the appropriate command.
*/

void	ft_sort_redirections(char **split)
{
	int		i;
	int		a;
	char	*temp;

	i = 1;
	while (split[0] && split[i])
	{
		if (split[i][0] == '<')
		{
			temp = split[i];
			split[i] = split[i - 1];
			split[i - 1] = temp;
		}
		else if (split[i][0] == '>' && split[i - 1][0] != '>')
		{
			a = i;
			while (split[i + 1] && split[i + 1][0] == '>')
				i++;
			temp = split[a];
			split[a] = split[i];
			split[i] = temp;
		}	
		i++;
	}
	return ;
}

/*
** Inserts char 'c' at position pos into string str.
**
** Frees the original string str. Allocates memory for the return string.
** So str = ft_strinsertchar(str, c, i) does not cause memory leaks.
*/

static char	*ft_strinsertchar(char *str, char c, int pos)
{
	char	*str1;
	char	*str2;
	char	*c_str;
	char	*dest;

	if (!str)
		return (NULL);
	if (pos > (int)ft_strlen(str))
		pos = ft_strlen(str);
	str1 = ft_substr(str, 0, pos);
	str2 = ft_substr(str, pos, ft_strlen(str) - pos);
	c_str = malloc(2 * sizeof(char));
	c_str[0] = c;
	c_str[1] = '\0';
	dest = ft_strjoin_3(str1, c_str, str2);
	free(c_str);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str)
		free(str);
	return (dest);
}

/*
** Returns the index of the next word in string temp following index i.
*/

static int	ft_find_word_end(char *temp, int i)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (temp[i] == ' ')
		i++;
	while (temp[i] != ' ' || sq || dq)
	{
		if (temp[i] == '\0')
			break ;
		else if (temp[i] == '\'' && !dq)
			sq = (sq + 1) % 2;
		else if (temp[i] == '\"' && !sq)
			dq = (dq + 1) % 2;
		i++;
	}
	return (i);
}
