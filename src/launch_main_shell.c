/*
** launch_main_shell.c for  in /home/stanislas/clone/PSU_2015_42sh
**
** Made by CUENAT
** Login   <stanislas@epitech.net>
**
** Started on  Mon May 30 16:18:20 2016 CUENAT
** Last update Sun Jun  5 21:04:01 2016 CUENAT
*/

#include "arrows.h"
#include "shell.h"

int		ft_start_exec(t_shell *shell)
{
  t_list	*tmp_list;
  t_sub_list	*tmp_sub;
  char		*tkn;

  tmp_list = shell->exec_list;
  while (tmp_list != NULL)
    {
      tmp_sub = tmp_list->sub_list;
      while (tmp_sub != NULL)
	{
	  tkn = strdup("\0");
	  if (ft_create_exec_function(shell, tmp_sub, tkn) == -1)
	    break ;
	  tmp_sub = tmp_sub->next;
	}
      tmp_list = tmp_list->next;
    }
  return (0);
}

int	ft_in_lauch(t_shell *shell, t_raw *raw, char *line)
{
  shell->path = ft_fill_bin_path(shell->env);
  line = replace_env(shell, line);
  line = epur(line);
  line = replace_alias(shell->alias, line);
  line = replace_glob(line);
  if ((shell->res_exec = ft_check_input(line)) == 0)
    {
      ft_create_list(shell, line);
      ft_create_sub_list(shell);
      ft_start_exec(shell);
      ft_free_struct(shell);
    }
  free(line);
  return (0);
}

int	ft_launch_shell(t_shell *shell)
{
  char	*line;
  t_raw	*raw;

  signal(SIGINT, ctrl);
  raw = init_raw(shell, "exit");
  set_hist(raw, 1, 15);
  while (((shell->isa_tty == 1 &&
	   (line = get_line(raw, "$> ")))) || (line = get_next_line(0)))
    {
      ft_in_lauch(shell, raw, strdup(line));
      ft_free_tab(shell->path);
      if (strlen(raw->line->input->buffer))
	hist_add_str(raw, raw->line->input->buffer, shell);
      free(line);
    }
  raw_free(raw);
  return (0);
}
