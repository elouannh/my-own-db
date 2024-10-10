/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:56:29 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/10 15:19:56 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
#define STRING_H

#include "../repl/inputs.h"
#include <stddef.h>

void ft_putstr(const char *s);
void ft_putnbr(ssize_t n);
void print_input_buffer(const InputBuffer *input_buffer);
void print_prompt(void);
ssize_t ft_strlen(const char *s);
ssize_t ft_strncmp(const char *s1, const char *s2, const ssize_t n);

#endif
