/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:27:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/11/11 11:41:44 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *extract_word( char *command, int start, int end )
{
	char *word = calloc(end - start + 1, sizeof(char));
	if ( !word )
		exit(1);
	
	int i = 0;
	while ( start < end )
	{
		word[i] = command[start];
		i++;
		start++;
	}
	
	return word;
}

static char** add_word( char **words, char *word )
{
	/* Check number of current words */
	size_t words_size = 0;
	while ( words && words[words_size] )
		words_size++;
	/* Alloc the new array */
	char **new_words = ft_calloc( words_size + 2, sizeof( char* ));
	if ( !new_words )
		exit(1);
	/* Copy the words and add the new one */
	int i = 0;
	while ( words && words[i] )
	{
		new_words[i] = words[i];
		i++;
	}
	new_words[i] = word;
	/* Free and return the new data */
	free(words);
	return new_words;
}

int	handle_split(t_token *tokens, char *command)
{
	int		counter;
	char	*word;

	tokens->tokens = NULL;
	printf("Start loop: [%s]\n", command);
	for ( int i = 0; command && command[i]; i++ )
	{
		while ( command[i] == ' ' )
			i++;
		/* Check characters (alphanumeric or just comillas (ns como se pone en ingles)) */
		counter = i + 1;
		printf("\t- Checking '%c'\n", command[i]);
		if ( command[i] == '\'' || command[i] == '\"' )
		{
			printf("\t\t· Comilla (%c)\n", command[i]);
			jump_character( command, &counter, command[i], FALSE );
			if ( command[counter] && command[counter] != ' ' )
			{
				counter++;
				jump_character( command, &counter, ' ', FALSE );
			}
			word = extract_word( command, i, counter );
			printf("\t\t· Extracted [%d-%d][%c-%c]: [%s]\n", i, counter, command[i], command[counter], word);
			tokens->tokens = add_word( tokens->tokens, word );
			i = counter - 1;
		}
		else
		{
			printf("\t\t· Letter. Getting the next space\n");
			jump_character( command, &counter, ' ', FALSE ); /* i=inicio cadena, j=caracter siguiente al final*/
			if ( command[counter] )
				counter--;
			word = extract_word( command, i, counter );
			printf("\t\t· Extracted [%d-%d][%c-%c]: [%s]\n", i, counter, command[i], command[counter], word);
			tokens->tokens = add_word( tokens->tokens, word );
			printf("\t\t· Added\n");
			i = counter - 1;
		}
	}
	printf("[X] Out\n");
	if (!tokens->tokens)
	{
		free(tokens->command);
		free(tokens);
		return (0);
	}
	return (1);
}
