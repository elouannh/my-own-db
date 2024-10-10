/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:38:03 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/10 16:24:06 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

void ft_putchar(const char c) {
    write(1, &c, 1);
}

void ft_putstr(const char *s) {
    if (!*s) return;
    write(1, s, ft_strlen(s));
}

void ft_sst_putnbr(ssize_t n) {
    if (n <= LONG_LONG_MIN)
        return ft_putstr("-9223372036854775808");
    if (n < 0) {
        n = -n;
        ft_putstr("-");
    }
    if (n >= 10) {
        ft_sst_putnbr(n / 10);
        n = n % 10;
    }
    ft_putchar(n + '0');
    ft_putchar('\n');
}

void ft_st_putnbr(size_t n) {
    if (n >= 10) {
        ft_st_putnbr(n / 10);
        n = n % 10;
    }
    ft_putchar(n + '0');
    ft_putchar('\n');
}

void print_input_buffer(const InputBuffer *input_buffer) {
    ft_putstr("buffer:\t");
    ft_putstr(input_buffer->buffer);
    ft_putstr("\nlength:\t");
    ft_sst_putnbr(input_buffer->input_length);
    ft_putstr("\n");
}

void print_prompt(void) { ft_putstr("my-own-db > "); }