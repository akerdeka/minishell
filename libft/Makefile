# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/14 14:02:44 by pbesson           #+#    #+#              #
#    Updated: 2021/02/10 15:43:22 by akerdeka         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


SRC = 		ft_conversion/ft_atoi.c\
			ft_mem/ft_bzero.c\
			ft_mem/ft_calloc.c\
			ft_mem/ft_memccpy.c\
			ft_mem/ft_memchr.c\
			ft_mem/ft_memcmp.c\
			ft_mem/ft_memcpy.c\
			ft_mem/ft_memmove.c\
			ft_mem/ft_memset.c\
			ft_is/ft_isalnum.c\
			ft_is/ft_isalpha.c\
			ft_is/ft_isascii.c\
			ft_is/ft_isdigit.c\
			ft_is/ft_isprint.c\
			ft_is/ft_is_set.c\
			ft_conversion/ft_itoa.c\
			ft_str/ft_split.c\
			ft_str/ft_strchr.c\
			ft_str/ft_strcmp.c\
			ft_str/ft_strdup.c\
			ft_str/ft_strjoin.c\
			ft_str/ft_strlcat.c\
			ft_str/ft_strlcpy.c\
			ft_str/ft_strlen.c\
			ft_str/ft_strmapi.c\
			ft_str/ft_strncmp.c\
			ft_str/ft_strnstr.c\
			ft_str/ft_strrchr.c\
			ft_str/ft_strtrim.c\
			ft_str/ft_strtrim_free.c\
			ft_str/ft_substr.c\
			ft_str/ft_strremove_chr.c\
			ft_change_char/ft_tolower.c\
			ft_change_char/ft_toupper.c\
			ft_put_fd/ft_putchar_fd.c\
			ft_put_fd/ft_putstr_fd.c\
			ft_put_fd/ft_putendl_fd.c\
			ft_put_fd/ft_putnbr_fd.c\
			ft_put/ft_putchar.c\
			ft_put/ft_putstr.c\
			ft_put/ft_putnbr.c\
			ft_conversion/ft_itoa_base.c\
			ft_conversion/ft_convert_base.c\
			ft_mem/ft_memdel.c\
			ft_str/ft_strjoin_free.c\
			ft_str/ft_strjoin_free_s1.c\
			ft_str/ft_strjoin_free_s2.c\
			ft_str/ft_strjoin_tab_free.c\
			ft_str/ft_strdel.c\
			ft_str/ft_strchr_count.c\
			ft_str/ft_strchr_set.c\
			ft_str/ft_strchr_all.c\
			ft_conversion/ft_itoa_base_ll.c\
			ft_conversion/ft_itoa_ll.c\
			ft_str/ft_substr_free.c\
			ft_printf/ft_itoa_base_flag_x.c\
			ft_printf/ft_printf.c\
			ft_printf/ft_init.c\
			ft_printf/ft_find_flags.c\
			ft_printf/ft_flags_process.c\
			ft_printf/ft_init_2.c\
			get_next_line/get_next_line.c

BUFFER_SIZE = -D BUFFER_SIZE=1000

HEADERS = ft_printf/ft_printf.h
OBJ = ${SRC:.c=.o}
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
RM = rm
$(NAME) :	$(OBJ) $(HEADERS)
				@ar rc $(NAME) $(OBJ) 
all :		${NAME}
%.o: %.c $(HEADERS)
			@$(CC) $(LIB) $(CFLAGS) -o $@ -c $<
clean :
				@${RM} -f $(OBJ)
fclean :     clean
				@rm -f ${NAME}
re : fclean all
.PHONY : all clean fclean re
