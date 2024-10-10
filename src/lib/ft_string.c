/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:56:12 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/10 16:46:53 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

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

int is_charset_member(const char c, const char *charset) {
    int i = 0;

    while (charset[i] && charset[i] != c)
        i++;

    return charset[i] != '\0';
}

size_t count_words(const char *s, const char *charset) {
    size_t count = 0;
    size_t i = 0;

    while (s[i]) {
        while (s[i] && is_charset_member(s[i], charset))
            i++;
        if (s[i] && !is_charset_member(s[i], charset))
            count++;
        while (s[i] && !is_charset_member(s[i], charset))
            i++;
    }

    return count;
}

char *ft_strncpy(char *dest, const char *src, const size_t n) {
    size_t i = 0;

    if (n == -1) {
        while (dest[i] && src[i]) {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';

        return dest;
    }

    while (i < n && dest[i] && src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';

    return dest;
}

char **ft_split(const char *s, const char *charset) {
    const size_t words_count = count_words(s, charset);
    char **words = malloc(words_count * sizeof(char *));

    if (!words)
        return NULL;

    size_t i = 0;
    while (i < words_count) {
        words[i] = malloc()
        i++;
    }

    return NULL;
}