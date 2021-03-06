/*
** launch_shell.c for  in /home/stanislas/PSU_2015_42sh
**
** Made by CUENAT
** Login   <stanislas@epitech.net>
**
** Started on  Wed May 18 18:24:09 2016 CUENAT
** Last update Sun Jun  5 21:43:05 2016 CUENAT
*/

#include "shell.h"
#include "arrows.h"

char	*ft_fill_null_path(char *dest)
{
  char	*tmp;

  if ((tmp = malloc(sizeof(char) * (strlen("/bin") + strlen(dest) + 2)))
      == NULL)
    exit(EXIT_FAILURE);
  strcpy(tmp, "/bin");
  tmp[strlen(tmp) + 1] = '\0';
  tmp[strlen(tmp)] = '/';
  strcat(tmp, dest);
  if (access(tmp, X_OK) == 0)
    {
      free(dest);
      return (tmp);
    }
  free(tmp);
  return (dest);
}

char	*ft_fill_path_for_execve(char *dest, char **path)
{
  char	*tmp;
  int	i;

  i = 0;
  if (path == NULL)
    return (ft_fill_null_path(dest));
  while (path != NULL && path[i])
    {
      if ((tmp = malloc(sizeof(char) *
			(strlen(dest) + strlen(path[i]) + 2))) == NULL)
	exit(EXIT_FAILURE);
      strcpy(tmp, path[i]);
      tmp[strlen(tmp) + 1] = '\0';
      tmp[strlen(tmp)] = '/';
      strcat(tmp, dest);
      if (access(tmp, X_OK) == 0)
	{
	  free(dest);
	  return (tmp);
	}
      free(tmp);
      i += 1;
    }
  return (dest);
}

char	**ft_fill_tab_for_execve(char **cmd, int *i)
{
  char	**res;
  int	j;

  j = 0;
  if ((res = malloc(sizeof(char *) * 2)) == NULL)
    exit(EXIT_FAILURE);
  while (cmd[*i] && cmd[*i][0] != '|' && cmd[*i][0] != '<'
	 && cmd[*i][0] != '>')
    {
      if ((res = realloc(res, sizeof(char *) * (j + 2))) == NULL)
	exit(EXIT_FAILURE);
      res[j] = strdup(cmd[*i]);
      j += 1;
      *i += 1;
    }
  res[j] = NULL;
  return (res);
}

int	ft_main_read_function(t_shell *shell, t_sub_list *tmp, char *tkn, int i)
{
  int	end;

  shell->cur_exec = ft_fill_tab_for_execve(tmp->exec_cmd, &i);
  if (shell->cur_exec[0] == NULL)
    return (-1);
  if (ft_is_a_build_in(shell->cur_exec[0]) == -1)
    shell->cur_exec[0] =
      ft_fill_path_for_execve(shell->cur_exec[0], shell->path);
  if (tmp->exec_cmd[i] != NULL)
    {
      tkn = strdup(tmp->exec_cmd[i]);
      if (strcmp(tkn, "<") == 0 || strcmp(tkn, "<<") == 0
	  || strcmp(tkn, ">") == 0 || strcmp(tkn, ">>") == 0)
	{
	  i += 1;
	  shell->file = strdup(tmp->exec_cmd[i]);
	}
    }
  (tmp->exec_cmd[i] != NULL && tmp->exec_cmd[i + 1] != NULL) ?
    (end = 0) : (end = 1);
  ft_choose_type_execution(shell, tkn, end);
  free(tkn);
  (tmp->exec_cmd[i] != NULL) ? (tkn = strdup(tmp->exec_cmd[i])) : 0;
  ft_free_tab(shell->cur_exec);
  return (i);
}

int	ft_create_exec_function(t_shell *shell, t_sub_list *tmp, char *tkn)
{
  int	i;

  i = 0;
  if (tmp->separator == NO || (tmp->separator == AND && shell->res_exec == 0)
      || (tmp->separator == OR && shell->res_exec != 0))
    {
      shell->res_exec = 0;
      shell->fd_in = dup(0);
      shell->nb_fork = 0;
      while (tmp->exec_cmd[i])
	{
	  if ((i = ft_main_read_function(shell, tmp, tkn, i)) == -1)
	    return (-1);
	  (tmp->exec_cmd[i] != NULL) ? (i += 1) : 0;
	  (tmp->exec_cmd[i] != NULL &&
	   strcmp(tmp->exec_cmd[i], "|") == 0) ? (i += 1) : 0;
	}
      ft_execute_instr_fork_2(shell);
      close(shell->fd_in);
    }
  else
    return (-1);
  return (0);
}
