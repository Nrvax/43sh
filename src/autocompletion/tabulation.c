/*
** tabulation.c for 42sh in /home/qwebify/rendu/PSU/PSU_2015_42sh/src/
**
** Made by maire_q
** Login   <maire_q@epitech.eu>
**
** Started on  %cdate maire_q
** Last update %udate maire_q
*/

#include "shell.h"

int	is_sep(char *sep)
{
  if (strcmp(sep, "&&") == 0 || strcmp(sep, "||") == 0 ||
      strcmp(sep, ";") == 0)
    return (1);
  return (0);
}
