/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:22:05 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/18 23:01:04 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define MAX_LEN 16384
# define USER_USERNAME_SIZE 32
# define USER_EMAIL_SIZE 255

#include <stdint.h>
#include <stdio.h>

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_BAD_SYNTAX,
    PREPARE_EMPTY_COMMAND,
} PrepareResult;
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
    char *buffer;
    ssize_t input_length;
} InputBuffer;
typedef struct {
    StatementType type;
} Statement;
typedef struct {
    char **args;
    size_t parsed_args;
} ParsedArgs;
typedef struct {
    uint32_t id;
    char username[USER_USERNAME_SIZE];
    char email[USER_EMAIL_SIZE];
} UserRow;

InputBuffer* create_input_buffer(void);
void read_input_buffer(InputBuffer* input_buffer);
MetaCommandResult do_meta_command(InputBuffer* input_buffer);
PrepareResult prepare_statement(const InputBuffer *input_buffer, Statement *statement, ParsedArgs *parsed_args);
void execute_statement(const Statement* statement);
int repl_inputs(void);
ssize_t ft_strncmp(const char *s1, const char *s2, const ssize_t n);
int is_charset_member(const char c, const char *charset);
size_t count_words(const char *s, const char *charset);
char *ft_strncpy(char *dest, const char *src, const size_t n);
void ft_split_buffer(const char *s, const char *charset, ParsedArgs *parsed_args);
void ft_putchar(char c);
void ft_putstr(const char *s);
void ft_sst_putnbr(ssize_t n);
void ft_st_putnbr(size_t n);
void print_input_buffer(const InputBuffer *input_buffer);
void print_prompt(void);

#endif //MAIN_H
