#include "lexer.h"

using namespace std;

//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

Lexer::Lexer() {	
	
	input = &cin;
	
	/* Reserved keywords */
	keywords["namespace"]				= Token::T_NAMESPACE;
	keywords["import"]					= Token::T_IMPORT;
	keywords["function"]				= Token::T_FUNCTION;
	keywords["class"]					= Token::T_CLASS;
	keywords["interface"]				= Token::T_INTERFACE;
	keywords["var"]						= Token::T_VAR;
	keywords["const"]					= Token::T_CONST;
	keywords["if"]						= Token::T_IF;
	keywords["elseif"]					= Token::T_ELSEIF;
	keywords["else"]					= Token::T_ELSE;
	keywords["while"]					= Token::T_WHILE;
	keywords["do"]						= Token::T_DO;
	keywords["foreach"]					= Token::T_FOREACH;
	keywords["switch"]					= Token::T_SWITCH;
	keywords["case"]					= Token::T_CASE;
	keywords["default"]					= Token::T_DEFAULT;
	keywords["try"]						= Token::T_TRY;
	keywords["catch"]					= Token::T_CATCH;
	keywords["finally"]					= Token::T_FINALLY;
	keywords["throw"]					= Token::T_THROW;
	keywords["break"]					= Token::T_BREAK;
	keywords["continue"]				= Token::T_CONTINUE;
	keywords["return"]					= Token::T_RETURN;
	keywords["exit"]					= Token::T_EXIT;
	keywords["true"]					= Token::T_BOOLEAN;
	keywords["false"]					= Token::T_BOOLEAN;
	keywords["null"]					= Token::T_NULL;
	
	/* Logic Operators */
	binary_operators["&"]				= Token::T_LOGICAL_AND;
	binary_operators["|"]				= Token::T_LOGICAL_OR;
	binary_operators["^"]				= Token::T_LOGICAL_XOR;
	unary_operators["!"]				= Token::T_LOGICAL_NOT;
	
	/* Arithmetic Operators */
	binary_operators["+"]				= Token::T_ADD;
	unary_operators["++"]				= Token::T_INCREMENT;
	binary_operators["-"]				= Token::T_SUBTRACT;
	unary_operators["--"]				= Token::T_DECREMENT;	
	binary_operators["/"]				= Token::T_DIVIDE;
	binary_operators["%"]				= Token::T_MODULUS;
	binary_operators["*"]				= Token::T_MULTIPLY;
	
	/* Comparison Operators */
	binary_operators[">"]				= Token::T_GREATER_OR_EQUAL;
	binary_operators[">>"]				= Token::T_STRICTLY_GREATER;
	binary_operators["<"]				= Token::T_LESS_OR_EQUAL;
	binary_operators["<<"]				= Token::T_STRICTLY_LESS;	
	binary_operators["="]				= Token::T_EQUAL;
	binary_operators["=="]				= Token::T_IDENTICAL;
	binary_operators["!="]				= Token::T_NOT_EQUAL;
	binary_operators["!=="]				= Token::T_NOT_IDENTICAL;	
	
	/* Assignment Operators */
	binary_operators[":="]				= Token::T_ASSIGN;
	binary_operators["+="]				= Token::T_ASSIGN_ADD;
	binary_operators["-="]				= Token::T_ASSIGN_SUBTRACT;
	binary_operators["/="]				= Token::T_ASSIGN_DIVIDE;
	binary_operators["%="]				= Token::T_ASSIGN_MODULUS;
	binary_operators["*="]				= Token::T_ASSIGN_MULTIPLY;
	binary_operators["?="]				= Token::T_ASSIGN_DEFAULT;
	
	/* Misc Operators */
	binary_operators[":"]				= Token::T_CAST;
	binary_operators["."]				= Token::T_ACCESSOR;
	unary_operators["?"]				= Token::T_OPTIONAL;
	unary_operators["~"]				= Token::T_GENERIC;	
}

Token Lexer::scan() {
	skipWhitespace();
	char current = (*input).peek();
	Token token;
	
	/* Comments */
	if (current == '/') {
		(*input).get();
		if ((*input).peek() == '/') {
			(*input).ignore(256, '\n');
			scan();
			return token;
		}
		(*input).unget();
	}
	
	/* Extract a constant string */
	if (current == '\'') {
		token.type = Token::T_CONSTANT_STRING;
		token.value = extractEnclosure('\'');
		return token;
	}
	
	/* Extract a dynamic string */
	if (current == '"') {
		token.type = Token::T_DYNAMIC_STRING;
		token.value = extractEnclosure('"');
		return token;
	}
	
	/* Extract an executable string */
	if (current == '`') {
		token.type = Token::T_EXECUTABLE_STRING;
		token.value = extractEnclosure('`');
		return token;
	}
	
	/* Extract a variable name */
	if (current == '$') {
		(*input).ignore();
		token.type = Token::T_VARIABLE;
		token.value = extractLabel();
		return token;
	}	
	
	/* Extract a constant name */
	if (current == '#') {
		(*input).ignore();
		token.type = Token::T_CONSTANT;
		token.value = extractLabel();
		return token;
	}	
	
	/* Extract an open brace */
	if (current == '{') {
		token.type = Token::T_CLOSURE_OPEN;
		token.value = (*input).get();
		return token;
	}
	
	/* Extract a close brace */
	if (current == '}') {
		token.type = Token::T_CLOSURE_CLOSE;
		token.value = (*input).get();
		return token;
	}
	
	/* Extract an open bracket */
	if (current == '[') {
		token.type = Token::T_LIST_OPEN;
		token.value = (*input).get();
		return token;
	}
	
	/* Extract a close bracket */
	if (current == ']') {
		token.type = Token::T_LIST_CLOSE;
		token.value = (*input).get();
		return token;
	}
	
	/* Extract an open parenthesis */
	if (current == '(') {
		token.type = Token::T_GROUP_OPEN;
		token.value = (*input).get();
		return token;
	}
	
	/* Extract a close parenthesis */
	if (current == ')') {
		token.type = Token::T_GROUP_CLOSE;
		token.value = (*input).get();
		return token;
	}
	
	/* Extract a semicolon */
	if (current == ';') {
		token.type = Token::T_TERMINATOR;
		token.value = (*input).get();
		return token;
	}	
	
	/* Extract a comma parenthesis */
	if (current == ',') {
		token.type = Token::T_DELIMITER;
		token.value = (*input).get();
		return token;
	}	
	
	/* Extract a number */
	if (isdigit(current)) {
		token.value = extractInteger();
		token.type = Token::T_INTEGER;
		
		/* Look for a float */
		if ((*input).peek() == '.') {
			token.value += (*input).get();
			token.value += extractInteger();
			token.type = Token::T_FLOAT;
			return token;
		}
		
		/* Look for a scientific notation */
		if ((*input).peek() == 'e') {
			token.value += (*input).get();
			token.value += extractInteger();
			token.type = Token::T_SCIENTIC;
			return token;
		}		
		
		/* Look for a hexidecimal */
		if (token.value == "0" && (*input).peek() == 'x') {
			token.value += (*input).get();
			token.value += extractInteger();
			token.type = Token::T_HEXIDECIMAL;
			return token;
		}
		
		/* Look for a binary */
		if (token.value == "0" && (*input).peek() == 'b') {
			token.value += (*input).get();
			token.value += extractBinary();
			token.type = Token::T_BINARY;
			return token;
		}		
		return token;
	}
	
	/* Extract generic label */
	if (islabel(current)) {
		token.value = extractLabel();
		token.type = Token::T_CLASS_NAME;
		
		if (keywords.count(token.value)) {
			token.type = keywords[token.value];
			return token;
		}
		
		/* Look for a namespace name */
		if ((*input).peek() == ':') {
			token.type = Token::T_NAMESPACE_NAME;
			
			/* Check for subnamespaces */
			while ((*input).peek() == ':') {
				char separator = (*input).get();
				string label = extractLabel();
				
				// Correct if not a subnamespace
				if ((*input).peek() == ':' or (*input).peek() == ';') {
					token.value += separator + label;
				}
				else {
					for (string::reverse_iterator it=label.rbegin(); it!=label.rend(); ++it) {
						(*input).putback(*it);
					}
				}
			}
			return token;
		}
		
		/* Look for a function name */
		if ((*input).peek() == '(') {
			token.type = Token::T_FUNCTION_NAME;
			return token;
		}		
		return token;
	}	
	
	/* Extract an operator */
	if (isoperator(current)) {
		token.value = extractOperator();
		if (binary_operators.count(token.value)) {
			token.type = binary_operators[token.value];
			return token;
		}
		if (unary_operators.count(token.value)) {
			token.type = unary_operators[token.value];
			return token;
		}
	}
	
	/* End of File */
	if (current == EOF) {
		token.type = Token::T_EOF;
		token.value = (*input).get();
		return token;
	}
	
	/* Unknown Token */
	token.type = Token::T_UNKNOWN;
	
	return token;
}

void Lexer::setInput(istream* stream) {
	input = stream;
}

void Lexer::lowerCase(string str) {
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void Lexer::skipWhitespace() {	
	/* Skip over whitespace */
	while (isspace((*input).peek())) {
		(*input).ignore();
	}
}

bool Lexer::islabel(int c) {
	return isalnum(c) || c == '_';
}

bool Lexer::isnewline(int c) {
	return (c == '\n') || (c == '\r');
}

bool Lexer::isbinary(int c) {
	return (c == '0') || (c == '1');
}

bool Lexer::isoperator(int c) {
	return ( 
			c == '&' ||
			c == '|' ||
			c == '^' ||
			c == '!' ||
			c == '+' ||	
			c == '-' ||
			c == '/' ||
			c == '%' ||
			c == '*' ||
			c == '>' ||
			c == '<' ||
			c == '=' ||
			c == ':' ||
			c == '?' ||	
			c == '.' ||
			c == '~'
			);
}

bool Lexer::isbetween(int c, int min, int max) {
	return (min <= c && c <= max);
}

string Lexer::extractInteger() {
	string value;
	while (isdigit((*input).peek())) {
		value += (*input).get();
	}
	return value;	
}

string Lexer::extractBinary() {
	string value;
	while (isbinary((*input).peek())) {
		value += (*input).get();
	}
	return value;	
}

string Lexer::extractLabel() {
	string value;
	while (islabel((*input).peek())) {
		value += (*input).get();
	}
	return value;
}

string Lexer::extractOperator() {
	string value;
	while (isoperator((*input).peek())) {
		value += (*input).get();
	}
	return value;
}

string Lexer::extractLineComment() {
	string value;
	getline((*input), value);
	return value;
}

string Lexer::extractEnclosure(int terminator) {
	char current;
	string value;
	(*input).ignore();
	while ((*input).peek() != terminator) {
		current = (*input).get();
		value += isspace(current) ? ' ' : current;
	}
	(*input).ignore();
	return value;
}