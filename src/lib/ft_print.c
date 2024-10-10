/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:38:03 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/10 15:20:03 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <unistd.h>
#include <limits.h>

void ft_putstr(const char *s) {
    if (!*s) return;
    write(1, s, ft_strlen(s));
}

void ft_putnbr(ssize_t n) {
    if (n <= LONG_LONG_MIN)
        return ft_putstr("-9223372036854775808");
    if (n < 0) {
        n = -n;
        ft_putstr("-");
    }
    if (n >= 10)
        ft_putnbr(n / 10);

    ft_putnbr(n % 10);
}

void print_input_buffer(const InputBuffer *input_buffer) {
    ft_putstr("buffer:\t");
    ft_putstr(input_buffer->buffer);
    ft_putstr("\nlength:\t");
    ft_putnbr(input_buffer->input_length);
    ft_putstr("\n");
}

void print_prompt(void) { ft_putstr("my-own-db > "); }