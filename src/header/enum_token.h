/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_token.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:56:14 by thibault          #+#    #+#             */
/*   Updated: 2023/10/10 23:22:04 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ENUM_TOKEN_H
# define ENUM_TOKEN_H

typedef enum
{
	// First level token
	TK_UNCLASSIFIED = -1,
	TK_NULL = 0,
	TK_BLANK,
	TK_PIPE = 10,
	TK_IN_CHEVRON = 31,
	TK_OUT_CHEVRON = 32,
	TK_APP_CHEVRON = 33,
	TK_HERE_DOC = 40,
	// Second level token
	TK_CMD = 100,
	TK_CMD_BUILT_IN = 300,
	TK_FILE = 200,
	TK_HD_ARG = 400,
	// Third level token
	TK_ARG = 1000,
	TK_BUILT_IN = 1001,
	TK_BIN = 1002,
	TK_HD_DELIM = 4002,
	/*
	TOKEN_WORD,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_PARANTHESIS,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_WILDCARD,
	TOKEN_BOOLEAN,
	TOKEN_LIMITER,
	TOKEN_STRING,
	TOKEN_NOT_FINISH,
	TOKEN_FLAGS,
	TOKEN_ARGUMENT
	TOKEN_VARIABLE,
	*/
}
TokenType;

typedef enum
{
	SUCCESS,
	FAILURE
} 
ReturnCode;
#endif



