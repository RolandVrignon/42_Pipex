/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:25:52 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/29 15:38:07 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static char *get_cmd_path(char *cmd, char **envp)
{
    char *envp_PATH;
    char **paths;
    char *cmd_path;
    char *tmp;
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
    paths = ft_split(envp_PATH, ':');
    if (!paths)
        return (0);
    free(envp_PATH);
    i = 0;
    while (paths[i++])
    {
        tmp = paths[i];
        paths[i] = ft_strjoin(paths[i], "/");
        free(tmp);
    }
    i = 0;
    while (paths[i++])
    {
        cmd_path = ft_strjoin(paths[i], cmd);
        if (access(cmd_path, F_OK | X_OK) == 0)
            return (cmd_path);
        free(cmd_path);
    }
    return (NULL);
}

int main(int ac, char **av, char **envp)
{
    int pfd[2];
    int pcd[2];

    (void)ac;
    (void)av;
    // Creer les pipes; CMD - 1;
    if (pipe(pfd) == -1)
    {
        printf("pipe failed\n");
        return 1;
    }
    if (pipe(pcd) == -1)
    {
        printf("pipe failed\n");
        return 1;
    }
    //-----------------------------------------------------------------------------------
    //----------------------------------------rolexx#6326-------------------------------------------
    int pid2;
    if ((pid2 = fork()) < 0)
    {
        printf("fork failed\n");
        return 2;
    }
    if (pid2 == 0)
    {
        char *cmd3;
        char *options3[3] = {"awk", "NR>4", NULL};
        char *cmd_path3;
        // ------------- AWK -----------------------------//
        close(pfd[1]);
        dup2(pcd[1], 1);
        close(pfd[0]);
        cmd3 = options3[0];
        cmd_path3 = get_cmd_path(cmd3, envp);
        if (!cmd_path3)
        {
            ft_printf("Error!\n");
            return (-1);
        }
        execve(cmd_path3, options3, envp);
        free(cmd_path3);
        printf("wc failed");
        return 3;
        // ------------- AWK -----------------------------//
    }
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    int pid;
    if ((pid = fork()) < 0)
    {
        printf("fork failed\n");
        return 2;
    }
    if (pid == 0)
    {
        char *cmd1;
        char *options1[3] = {"wc", "-l", NULL};
        char *cmd_path1;
        // ------------- WC -----------------------------//
        close(pfd[1]);
        dup2(pfd[0], 0);
        close(pfd[0]);
        cmd1 = options1[0];
        cmd_path1 = get_cmd_path(cmd1, envp);
        if (!cmd_path1)
        {
            ft_printf("Error!\n");
            return (-1);
        }
        execve(cmd_path1, options1, envp);
        free(cmd_path1);
        printf("awk failed");
        return 4;
        // ------------- WC -----------------------------//
    }
    else
    {
        char *cmd2;
        char *options2[3] = {"ls", "-la", NULL};
        char *cmd_path2;
        // ------------- LS -----------------------------//
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);

        cmd2 = options2[0];
        cmd_path2 = get_cmd_path(cmd2, envp);
        if (!cmd_path2)
        {
            ft_printf("Error!\n");
            return (-1);
        }
        execve(cmd_path2, options2, envp);
        free(cmd_path2);
        printf("ls failed");
        return 4;
        // ------------- LS -----------------------------//
    }
    return 0;
}
