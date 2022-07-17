/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:29:03 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/03 13:38:50 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	how_many_words(char const *s, char c)
{
	unsigned int	i;
	unsigned int	words;

	if (!s[0])
		return (0);
	i = 0;
	words = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			words++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		words++;
	return (words);
}

static void	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free (tab);
	return (NULL);
}

static char	**create_tabs(char **tab, char const *str, char c, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < len)
	{
		if (str[i] != c)
		{
			j = 0;
			while (str[i] != c && i < len)
			{
				i++;
				j++;
			}
			tab[k] = ft_calloc(sizeof(char), (j + 1));
			if (!tab[k])
				return ((char **)free_tab(tab));
			k++;
		}
		i++;
	}
	return (tab);
}

static char	**fill_tab(char **tab, char const *s, char c, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < len)
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i] != c && i < len)
			{
				tab[k][j] = s[i];
				i++;
				j++;
			}
			k++;
		}
		i++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		words;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	words = how_many_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab = create_tabs(tab, s, c, len);
	if (!tab)
		return (NULL);
	tab = fill_tab(tab, s, c, len);
	tab[words] = NULL;
	return (tab);
}
