/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:51:45 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/30 15:41:45 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char *get_envp(char **envp)
{
    char *envp_PATH;
    int i;

    i = 0;
    while (envp[i++])
    {
        envp_PATH = ft_strnstr(envp[i], "PATH=", 5);
        if (envp_PATH)
        {
            envp_PATH = ft_substr(envp_PATH, 5, ft_strlen(envp_PATH));
            if (!envp_PATH)
                return (0);
            break;
        }
    }
    return (envp_PATH);
}

int create_pipes(t_pipex pipex)
{
    int i;

    i = 0;
    while (i < pipex.pipe_nbr)
    {
        if (pipe(pipex.pfd + (2 * i)) < 0)
            return (0);
        i++;
    }
    return (1);
}

void free_double(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

int free_stuff(t_pipex pipex)
{
	(void)pipex;
	free(pipex.env_path);
    // free(pipex.pfd);
	free_double(pipex.cmd);
	free_double(pipex.opt);
	free_double(pipex.cpath);
    return (1);
}

char **get_cmd(int cmd_nbr, char **av)
{
    int i;
    char **tab;
    char **split;

    i = 0;
    tab = malloc(sizeof(char *) * (cmd_nbr + 1));
    if (!tab)
        return (NULL);
    while (i < cmd_nbr)
    {
        split = ft_split(av[i + 2], ' ');
        if (!split)
            return (NULL);
        tab[i] = ft_strdup(split[0]);
		free_double(split);
        i++;
    }
    tab[i] = 0;
    return (tab);
}

char **get_opt(int cmd_nbr, char **av)
{
    int i;
    char **tab;
    char **split;

    i = 0;
    tab = malloc(sizeof(char *) * (cmd_nbr + 1));
    if (!tab)
        return (NULL);
    while (i < cmd_nbr)
    {
        split = ft_split(av[i + 2], ' ');
        if (!split)
            return (NULL);
        tab[i] = ft_strdup(split[1]);
		free_double(split);
        i++;
    }
    tab[i] = 0;
    return (tab);
}