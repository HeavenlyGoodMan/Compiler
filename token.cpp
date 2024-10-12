#include "token.h"

token::token()
{
	type = "";
	lexem = "";
}

string token::getlex()
{
	return lexem;
}

string token::getType()
{
	return type;
}
