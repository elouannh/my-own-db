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
#include <string.h>

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
const uint32_t PAGE_SIZE = 4096;
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

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

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement, ParsedArgs *parsed_args)
{
	if (parsed_args->parsed_args == 0)
		return PREPARE_EMPTY_COMMAND;
	printf("%s and %ld", parsed_args->args[0], ft_strncmp(parsed_args->args[0], "insert", -1));
	if (ft_strncmp(parsed_args->args[0], "insert", 6) == 0)
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

ExecuteResult execute_insert(Statement *statement, Table *table)
{
	if (table->num_rows >= TABLE_MAX_ROWS)
		return EXECUTE_TABLE_FULL;

	Row *row_to_insert = &(statement->row_to_insert);

	serialize_row(row_to_insert, row_slot(table, table->num_rows));
	table->num_rows += 1;

	return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Table *table)
{
	Row row;

	for (uint32_t i = 0; i < table->num_rows; i++)
	{
		deserialize_row(row_slot(table, i), &row);
		print_row(&row);
	}
	return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table *table)
{
	switch (statement->type)
	{
		case (STATEMENT_INSERT):
			return execute_insert(statement, table);
		break;
		case (STATEMENT_SELECT):
			return execute_select(table);
		break;
	}
	return EXECUTE_SUCCESS;
}

Table *new_table() {
	Table *table = (Table *)malloc(sizeof(Table));

	if (table == NULL)
		return NULL;

	table->num_rows = 0;

	for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
		table->pages[i] = NULL;
	return table;
}

void free_table(Table *table)
{
	for (int i = 0; table->pages[i]; i++)
		free(table->pages[i]);
	free(table);
}

void serialize_row(Row *source, void *destination)
{
	memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
	memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
	memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void *source, Row *destination)
{
	memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
	memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
	memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

void *row_slot(Table *table, uint32_t row_num)
{
	uint32_t page_num = row_num / ROWS_PER_PAGE;
	void *page = table->pages[page_num];

	if (page == NULL)
		page = table->pages[page_num] = malloc(PAGE_SIZE);

	uint32_t row_offset = row_num % ROWS_PER_PAGE;
	uint32_t byte_offset = row_offset * ROW_SIZE;
	return page + byte_offset;
}

int repl_inputs(void)
{
	Table *table = new_table();
	InputBuffer *input_buffer = create_input_buffer();

	while (input_buffer)
	{
		print_prompt();
		read_input_buffer(input_buffer);

		ParsedArgs parsed_args;
		ft_split_buffer(input_buffer->buffer, " ", &parsed_args);
		print_parsed_args(&parsed_args);

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

		switch (prepare_statement(input_buffer, &statement, &parsed_args))
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

		switch (execute_statement(&statement, table))
		{
		case (EXECUTE_SUCCESS):
			ft_putstr("Executed.\n");
			break;
		case (EXECUTE_TABLE_FULL):
			ft_putstr("Error: the table is full.\n");
			break;
		}
	}

	return EXIT_SUCCESS;
}
