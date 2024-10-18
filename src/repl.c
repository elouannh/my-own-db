/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:18:34 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/18 16:18:46 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/main.h"

InputBuffer* create_input_buffer(void)
{
	InputBuffer* buffer = malloc(sizeof(InputBuffer));

	if (!buffer)
		return NULL;

	buffer->buffer = NULL;
	buffer->input_length = 0;
	return buffer;
}

void read_input_buffer(InputBuffer* input_buffer)
{
	if (input_buffer->buffer == NULL)
		input_buffer->buffer = malloc(sizeof(char) * MAX_LEN);

	int i = MAX_LEN;
	int j = 0;
	int c;

	while(i && (c = fgetc(stdin)) != EOF && c != '\n')
	{
		input_buffer->buffer[j] = (char)c;
		i--;
		j++;
	}

	input_buffer->buffer[j] = '\0';
	input_buffer->input_length = j;
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer)
{
	if (ft_strncmp(input_buffer->buffer, ".exit", -1) == 0)
	{
		free(input_buffer->buffer);
		free(input_buffer);
		ft_putstr("See you later. ;)\n\n");
		exit(EXIT_SUCCESS);
	}
	return META_COMMAND_UNRECOGNIZED_COMMAND;
}

PrepareResult prepare_statement(const InputBuffer *input_buffer, Statement *statement, ParsedArgs *parsed_args)
{
	if (parsed_args->parsed_args == 0)
		return PREPARE_EMPTY_COMMAND;
	if (ft_strncmp(input_buffer->buffer, "insert", 6) == 0)
	{
		statement->type = STATEMENT_INSERT;
		if (parsed_args->parsed_args != 4)
			return PREPARE_BAD_SYNTAX;
		return PREPARE_SUCCESS;
	}
	if (ft_strncmp(input_buffer->buffer, "select", 6) == 0)
	{
		statement->type = STATEMENT_SELECT;
		return PREPARE_SUCCESS;
	}

	return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(const Statement* statement)
{
	switch (statement->type)
	{
		case (STATEMENT_INSERT):
			ft_putstr("This is where we would do an insert.\n");
		break;
		case (STATEMENT_SELECT):
			ft_putstr("This is where we would do a select.\n");
		break;
	}
}

int repl_inputs(void)
{
	InputBuffer* input_buffer = create_input_buffer();

	while (input_buffer)
	{
		print_prompt();
		read_input_buffer(input_buffer);

		ParsedArgs parsed_args;
		ft_split_buffer(input_buffer->buffer, " ", &parsed_args);

		if (input_buffer->buffer[0] == '.')
		{
			switch (do_meta_command(input_buffer))
			{
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

		switch(prepare_statement(input_buffer, &statement, &parsed_args))
		{
			case (PREPARE_SUCCESS):
				break;
			case (PREPARE_BAD_SYNTAX):
				ft_putstr("Bad syntax of arguments.\n");
				continue;
			case (PREPARE_EMPTY_COMMAND):
				continue;
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
