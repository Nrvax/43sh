/*
** redirection.c for  in /home/stanislas/clone/PSU_2015_42sh
**
** Made by CUENAT
** Login   <stanislas@epitech.net>
**
** Started on  Tue May 24 13:59:30 2016 CUENAT
** Last update Tue May 31 12:24:04 2016 CUENAT
*/

#include "shell.h"

void	ft_inredirect(char *file)
{
  int fd0;

  if ((fd0 = open(file, O_RDONLY, 0)) == -1)
    {
      printf("%s: %s\n", strerror(errno), file);
      return ;
    }
  dup2(fd0, STDIN_FILENO);
  close(fd0);
}

void    ft_rewrite(char *file)
{
  int   fd;

  if ((fd = open(file , O_CREAT | O_RDWR | O_TRUNC, 0666)) == -1)
    {
      dprintf(2, "%s: ", file);
      perror("");
      exit(EXIT_FAILURE);
    }
  dup2(fd, 1);
  close(fd);
}

void    ft_write_at_end(char *file)
{
  int   fd;

  if ((fd = open(file, O_CREAT | O_APPEND | O_RDWR, S_IRWXU)) == -1)
    {
      dprintf(2, "%s: ", file);
      perror("");
      exit(EXIT_FAILURE);
    }
  dup2(fd, 1);
  close(fd);
}
