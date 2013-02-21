#ifndef token_H
#define token_H

#include <string>

using namespace std;

class Token {
public:
	enum Type {
		T_UNKNOWN,
		
		/* Enclosures */
		T_CLOSURE_OPEN,		// {
		T_CLOSURE_CLOSE,	// }
		T_LIST_OPEN,		// [
		T_LIST_CLOSE,		// ]		
		T_GROUP_OPEN,		// (
		T_GROUP_CLOSE,		// )
		
		/* Literals */
		T_INTEGER,			// [0-9]+
		T_FLOAT,			// [0-9]+.[0-9]+
		T_SCIENTIC,			// [0-9]+e[0-9]+
		T_HEXIDECIMAL,		// 0x[0-9]+
		T_BINARY,			// 0b[0-1]+
		T_CONSTANT_STRING,	// ''
		T_DYNAMIC_STRING,	// ""
		T_EXECUTABLE_STRING,// ``
		T_BOOLEAN,			// true | false
		T_NULL,				// null
		T_COMMENT,
		
		/* Labels */
		T_NAMESPACE_NAME,
		T_FUNCTION_NAME,
		T_CLASS_NAME,
		
		/* Variables & Constants */
		T_VARIABLE,			// $[a-zA-Z0-0_]
		T_CONSTANT,			// #		
		
		/* Execution Control */
		T_EXIT,				// exit
		T_RETURN,			// return
		T_BREAK,			// break
		T_CONTINUE,			// continue
		T_TRY,				// try
		T_CATCH,			// catch
		T_FINALLY,			// finally
		T_THROW,			// throw
		
		/* Conditional Control */
		T_IF,				// if
		T_ELSE,				// else
		T_ELSEIF,			// elseif
		T_WHILE,			// while
		T_DO,				// do
		T_FOREACH,			// foreach
		T_SWITCH,			// switch
		T_CASE,				// case
		T_DEFAULT,			// default
		
		/* Definitions */
		T_NAMESPACE,		// namespace
		T_IMPORT,			// import
		T_FUNCTION,			// function
		T_CLASS,			// class
		T_INTERFACE,		// interface
		T_VAR,				// var
		T_CONST,			// const
		T_CLOSURE,			// {}
		
		/* Modifiers */
		T_EXTENDS,			// extends
		T_IMPLEMENTS,		// implements
		T_USES,				// uses
		T_ABSTRACT,			// abstract
		T_FINAL,			// final
		
		/* Visibility */
		T_PRIVATE,			// private
		T_PROTECTED,		// protected
		T_PUBLIC,			// public
		
		/* Logic Operators */
		T_LOGICAL_AND,		// &
		T_LOGICAL_OR,		// | 
		T_LOGICAL_XOR,		// ^		
		T_LOGICAL_NOT,		// !		
		
		/* Arithmetic Operators */
		T_ADD,				// +
		T_INCREMENT,		// ++
		T_SUBTRACT,			// -
		T_DECREMENT,		// --		
		T_DIVIDE,			// /
		T_MODULUS,			// %
		T_MULTIPLY,			// *
		
		/* Comparison Operators */
		T_GREATER_OR_EQUAL,	// >
		T_STRICTLY_GREATER,	// >>
		T_LESS_OR_EQUAL,	// <
		T_STRICTLY_LESS,	// <<
		T_EQUAL,			// =
		T_IDENTICAL,		// ==
		T_NOT_EQUAL,		// !=
		T_NOT_IDENTICAL,	// !==
		
		/* Assignment Operators */
		T_ASSIGN,			// :=
		T_ASSIGN_ADD,		// +=
		T_ASSIGN_SUBTRACT,	// -=
		T_ASSIGN_DIVIDE,	// /=
		T_ASSIGN_MODULUS,	// %=
		T_ASSIGN_MULTIPLY,	// *=
		T_ASSIGN_DEFAULT,	// ?=
		
		/* Misc Operators */	
		T_CAST,				// :
		T_TERMINATOR,		// ;
		T_DELIMITER,		// ,
		T_ACCESSOR,			// .
		T_ANNOTATION,		// @
		T_OPTIONAL,			// ?
		T_TERNARY,			// ?
		T_GENERIC,			// ~
		
		T_EOF,
	};
	
	Token::Type type;
	string value;
	
	Token();
	string label();
};

#endif