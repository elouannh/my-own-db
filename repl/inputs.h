/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:04:37 by ehosta            #+#    #+#             */
/*   Updated: 2024/10/09 14:47:36 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
#define INPUTS_H
#include <stddef.h>

#define MAX_LEN 16384

int repl_inputs(void);

typedef struct {
    char *buffer;
    ssize_t input_length;
} InputBuffer;

#endif
