/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:59:53 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/09 15:20:56 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_prompt(void) { write(1, "$ my-own-db:\n", 13); }

void print_input_buffer(const InputBuffer *input_buffer) {
    printf("buffer:\t%s\n", input_buffer->buffer);
    printf("length:\t%lld\n", input_buffer->input_length);
}

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

int repl_inputs(void) {
    InputBuffer* input_buffer = create_input_buffer();

    while (input_buffer) {
        print_prompt();
        read_input_buffer(input_buffer);

        if (strcmp(input_buffer->buffer, "exit") == 0) {
            free(input_buffer->buffer);
            free(input_buffer);
            printf("See you later. ;)\n\n");
            exit(EXIT_SUCCESS);
        }

        printf("Unrecognized command: %s", input_buffer->buffer);
        break;
    }

    return EXIT_SUCCESS;
}