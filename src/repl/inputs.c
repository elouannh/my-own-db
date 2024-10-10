/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:59:53 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/10 15:22:37 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"
# include "../lib/lib.h"
#include <stdio.h>
#include <stdlib.h>

InputBuffer* create_input_buffer(void) {
    InputBuffer* buffer = malloc(sizeof(InputBuffer));

    if (!buffer)
        return NULL;

    buffer->buffer = NULL;
    buffer->input_length = 0;
    return buffer;
}

void read_input_buffer(InputBuffer* input_buffer) {
    if(input_buffer->buffer == NULL)
        input_buffer->buffer = malloc(sizeof(char) * MAX_LEN);

    int i = MAX_LEN;
    int j = 0;
    int c;

    while(i && (c = fgetc(stdin)) != EOF && c != '\n') {
        input_buffer->buffer[j] = (char)c;
        i--;
        j++;
    }
    input_buffer->buffer[j] = '\0';
    input_buffer->input_length = j;
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    if (ft_strncmp(input_buffer->buffer, ".exit", -1) == 0) {
        free(input_buffer->buffer);
        free(input_buffer);
        ft_putstr("See you later. ;)\n\n");
        exit(EXIT_SUCCESS);
    }

    return META_COMMAND_UNRECOGNIZED_COMMAND;
}

MetaCommandResult prepare_statement(const InputBuffer *input_buffer, Statement *statement) {
    if (ft_strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (ft_strncmp(input_buffer->buffer, "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            ft_putstr("This is where we would do an insert.\n");
        break;
        case (STATEMENT_SELECT):
            ft_putstr("This is where we would do a select.\n");
        break;
    }
}

int repl_inputs(void) {
    InputBuffer* input_buffer = create_input_buffer();

    while (input_buffer) {
        print_prompt();
        read_input_buffer(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    ft_putstr("Unrecognized command: ");
                    ft_putstr(input_buffer->buffer);
                    ft_putstr("\n");
                    continue;
            }
        }

        Statement statement;

        switch(prepare_statement(input_buffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                ft_putstr("Unrecognized keyword at start of '");
                ft_putstr(input_buffer->buffer);
                ft_putstr("'.\n");
                continue;
        }

        execute_statement(&statement);
    }

    return EXIT_SUCCESS;
}