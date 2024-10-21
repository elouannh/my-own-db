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

ssize_t ft_strlen(char *s) {
	ssize_t i = 0;

	while (s[i]) i++;
	return i;
}

ssize_t ft_strncmp(char *s1, char *s2, ssize_t n) {
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

int is_charset_member(char c, char *charset) {
	int i = 0;

	while (charset[i] && charset[i] != c)
		i++;
	return charset[i] != '\0';
}

size_t count_words(char *s, char *charset) {
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

char *ft_strncpy(char *dest, char *src, size_t n) {
	size_t i = 0;

	while (i < n && dest[i] && src[i]) {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

void ft_putchar(char c) {
	write(1, &c, 1);
}

void ft_putstr(char *s) {
	if (!*s) return;

	write(1, s, ft_strlen(s));
}

void ft_putuint(uint32_t n)
{
	if (n >= 10)
	{
		ft_putuint(n / 10);
		n = n % 10;
	}

	ft_putchar(n + '0');
	ft_putchar('\n');
}

void ft_putint(int32_t n)
{
	if (n <= INT32_MIN) {
		write(1, "-2147483648", 1);
		return ;
	}
	if (n < 0) {
		n *= -1;
		write(1, "-", 1);
	}
	if (n >= 10)
	{
		ft_putint(n / 10);
		n = n % 10;
	}

	ft_putchar(n + '0');
	ft_putchar('\n');
}

void print_row(Row *row)
{
	ft_putstr("(");
	ft_putuint(row->id);
	ft_putstr(", ");
	ft_putstr(row->username);
	ft_putstr(", ");
	ft_putstr(row->email);
	ft_putstr(")");
}

void print_parsed_args(ParsedArgs *parsed_args)
{
	size_t words = 0;

	while (words < parsed_args->parsed_args)
	{
		ft_putstr(parsed_args->args[words]);
		printf("%s", parsed_args->args[words]);
		ft_putstr("$\n");
		words++;
	}
}
