##
## Makefile for  in /home/stanislas/PSU_2015_minishell2
##
## Made by CUENAT
## Login   <stanislas@epitech.net>
##
## Started on  Tue Mar 29 11:16:42 2016 CUENAT
## Last update Sun Jun  5 22:17:20 2016 CUENAT
##

NAME	=	42sh

CC	=	gcc

SRCS	=	src/main.c \
		src/fill_struct.c \
		src/parse_string.c \
		src/split.c \
		src/get_next_line.c \
		src/launch_main_shell.c \
		src/launch_shell.c \
		src/epur.c \
		src/string_utils.c \
		src/check_input.c \
		src/fill_list.c \
		src/free_struct.c \
		src/execute_instruction.c \
		src/redirection.c \
		src/built_in/alias.c \
		src/built_in/alias_list.c \
		src/signal.c \
		src/config_file/42shconfig.c \
		src/choose_type_execution.c \
		src/my_getnbr.c \
		src/built_in/build_exit.c \
		src/built_in/build_echo.c \
		src/built_in/build_setenv.c \
		src/built_in/build_unsetenv.c \
		src/built_in/build_cd.c \
		src/built_in/build_env.c \
		src/built_in/build_source.c \
		src/built_in/build_alias.c \
		src/env_values.c \
		src/config_file/check_options.c \
		src/join.c \
		src/export.c \
		src/check_input2.c \
		src/globing.c \
		src/cmd_history.c \
		src/line_editing/get_input.c \
		src/line_editing/raw_char.c \
		src/line_editing/raw_history.c \
		src/line_editing/raw_history_serial.c \
		src/line_editing/raw_string.c \
		src/line_editing/raw_utils.c \
		src/line_editing/escape_char.c \
		src/line_editing/extended_esc.c \
		src/line_editing/input_signals.c \
		src/line_editing/raw_memfunc.c \
		src/line_editing/raw_free.c \
		src/autocompletion/autocomplete.c \
		src/magic_quotes.c \
		src/autocompletion/tabulation.c \
		src/execute_pipe.c \
		src/check_input3.c \
		src/fill_list2.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-I inc -W -Wall -Wextra -Wno-unused-parameter

all:		$(NAME)

$(NAME): 	$(OBJS)
	 	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
	 	rm -f $(OBJS)

fclean: 	clean
	 	rm -f $(NAME)

test: 	all clean

re:		fclean all

.PHONY:		all clean fclean re
