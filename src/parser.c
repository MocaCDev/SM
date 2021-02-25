#include "parser.h"

Parser_* init_parser(Lexer_* lexer)
{
	Parser_* parser = calloc(1,sizeof(*parser));

	parser->lexer = lexer;
	return parser;
}

void get_next_token(Parser_* parser)
{
	parser->tokens = next_token(parser->lexer);
}

void print_err(Parser_* parser)
{
	if(parser->tokens->TokenId == EOF)
	{
		fprintf(stderr,"Unexpected EOF while parsing. Line %d.\n", parser->lexer->line-1);
		exit(EXIT_FAILURE);
	}
	fprintf(stderr,"Unexpected '%s' while parsing. Line %d.\n", parser->tokens->token_value, parser->lexer->line-1);
	exit(EXIT_FAILURE);
}

Parser_* parse_user_define(Parser_* parser)
{
	// save variable name to syntax tree here
	get_next_token(parser);
	if(!(parser->tokens->TokenId == Colon))
	{
		fprintf(stderr,"Expected ':', got %s\n", parser->tokens->token_value);
		exit(EXIT_FAILURE);
	}
	get_next_token(parser);
	switch(parser->tokens->TokenId)
	{
		case String:
		{
			get_next_token(parser);
			break;
		}
		default:
		{
			print_err(parser);
		}
	}
	return parser;
}

Parser_* check_value(Parser_* parser)
{
	if(parser->tokens->TokenId == 0) return parse_user_define(parser);
	return parser;
}

Parser_* parse(Parser_* parser)
{
	parser->tokens = next_token(parser->lexer);
	
	return check_value(parser);
}
