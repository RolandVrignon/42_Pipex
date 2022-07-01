/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:51:45 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/01 15:10:47 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_envp(char **envp)
{
	char	*env_path;
	int		i;

	i = 0;
	while (envp[i++])
	{
		env_path = ft_strnstr(envp[i], "PATH=", 5);
		if (env_path)
		{
			env_path = ft_substr(env_path, 5, ft_strlen(env_path));
			if (!env_path)
				return (0);
			break ;
		}
	}
	return (env_path);
}

void	free_double(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

int	free_stuff(t_pipex pipex)
{
	(void)pipex;
	if (pipex.env_path)
		free(pipex.env_path);
	if (pipex.pfd)
		free(pipex.pfd);
	if (pipex.cmd)
		free_double(pipex.cmd);
	if (pipex.opt)
		free_double(pipex.opt);
	if (pipex.cpath)
		free_double(pipex.cpath);
	return (1);
}

char	**get_cmd(int cmd_nbr, char **av, int heredoc)
{
	int		i;
	int		j;
	char	**tab;
	char	**split;

	i = 0;
	j = 2 + heredoc;
	tab = malloc(sizeof(char *) * (cmd_nbr + 1));
	if (!tab)
		return (NULL);
	while (i < cmd_nbr)
	{
		split = ft_split(av[i + j], ' ');
		if (!split)
			return (NULL);
		tab[i] = ft_strdup(split[0]);
		free_double(split);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
