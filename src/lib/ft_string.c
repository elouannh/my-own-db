/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:56:12 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/10 15:24:28 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

ssize_t ft_strlen(const char *s) {
    ssize_t i = 0;

    while (s[i]) i++;

    return i;
}

ssize_t ft_strncmp(const char *s1, const char *s2, const ssize_t n) {
    if (n == -1) {
        while (*s1 && *s1 == *s2) {
            s1++;
            s2++;
        }

        return *s1 - *s2;
    }

    ssize_t i = 0;

    while (*s1 && *s1 == *s2 && i < n) {
        s1++;
        s2++;
        i++;
    }

    return *s1 - *s2;
}