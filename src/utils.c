/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:19:26 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/18 23:02:22 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/main.h"
#include <limits.h>
#include <unistd.h>
#include <string.h>

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

	if (n == (size_t)-1) {
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

void ft_split_buffer(const char *s, const char *charset, ParsedArgs *parsed_args) {
	const size_t words_count = count_words(s, charset);
	char **words = malloc(words_count * sizeof(char *));

	if (!words)
		return ;

	size_t i = 0;
	size_t w = 0;
	ssize_t current_word_len = 0;
	while (w < words_count && s[i]) {
		current_word_len = 0, i = 0;

		while (*s && is_charset_member(*s, charset))
			s++;
		while (s[current_word_len] && !is_charset_member(s[current_word_len], charset))
			current_word_len++;

		words[w] = malloc(sizeof(char) * (current_word_len + 1));

		if (!words[w]) {
			size_t clearmem = 0;

			while (clearmem < w) free(words[clearmem++]);
			free(words);
			return ;
		}

		ft_strncpy(words[w], s, current_word_len);
		words[w][current_word_len] = '\0';
		s += current_word_len;
		w++;
	}

	parsed_args->args = words;
	parsed_args->parsed_args = words_count;
}

void ft_putchar(const char c) {
	write(1, &c, 1);
}

void ft_putstr(const char *s) {
	if (!*s) return;

	write(1, s, ft_strlen(s));
}

void ft_sst_putnbr(ssize_t n) {
	if (n <= LLONG_MIN)
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
