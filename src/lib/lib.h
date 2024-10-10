/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:56:29 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/10 16:47:04 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
#define STRING_H

#include "../repl/inputs.h"
#include <stddef.h>

void ft_putstr(const char *s);
void ft_sst_putnbr(ssize_t n);
void ft_st_putnbr(size_t n);
void print_input_buffer(const InputBuffer *input_buffer);
void print_prompt(void);
ssize_t ft_strlen(const char *s);
ssize_t ft_strncmp(const char *s1, const char *s2, const ssize_t n);
int is_charset_member(const char c, const char *charset);
size_t count_words(const char *s, const char *charset);
char *ft_strncpy(char *dest, const char *src, const size_t n);
char **ft_split(const char *s, const char *charset);

#endif
