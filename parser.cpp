#include "parser.h"
#include "lexer.h"
#include "engine.h"

using namespace std;

extern Engine& ENGINE;

//===----------------------------------------------------------------------===//
// Parser
//===----------------------------------------------------------------------===//

Parser::Parser(Lexer& lexer) : lexer(lexer) {
	this->_namespace = &(ENGINE.globalNamespace());
}

Parser::~Parser() {
	if (source.good()) {
		source.close();
	}	
}

void Parser::next() {
	token = lexer.scan();	
	
	printf("\nToken: %s '%s'", token.label().c_str(), token.value.c_str());	
	cout.flush();
}

void Parser::parse(string file) {
	source.open(file.c_str());
	if (!source.good()) {
		printf("test.mz not found in path: %s", getcwd(NULL, PATH_MAX));
	}
	lexer.setInput(&source);
	parse();
}

void Parser::parse() {
	next();
	
	try {
		while (token.type != Token::T_EOF and token.type != Token::T_UNKNOWN) {
			parseFile();
		}
	}
	catch (Exception& e) {
		cout << e.message.c_str();
	}

}

void Parser::parseFile() {
	switch (token.type) {
		case Token::T_NAMESPACE:
			parseNamespaceDeclaration();
			return;
						
		case Token::T_CONST:
			parseConstantDeclaration();
			return;			
			
		case Token::T_FUNCTION:
			parseFunctionDeclaration();
			return;	
			
		case Token::T_CLASS:
			parseClassDeclaration();
			return;	
			
		case Token::T_INTERFACE:
			parseInterfaceDeclaration();
			return;	
			
		default:
			parseStatement();
			return;
	}
}	

void Parser::parseStatement() {	
	switch (token.type) {
		case Token::T_VAR:
			parseVariableDeclaration();
			return;
			
		case Token::T_IF:
			parseIfStatement();
			return;
			
		case Token::T_WHILE:
			parseWhileStatement();
			return;			
			
		default:
			/* Expect an expression */
			parseExpression();
			
			/* Expect a terminator */
			if (token.type != Token::T_TERMINATOR) {
				throw Exception(token);
			}
			next();			
			return;
	}
}

void Parser::parseExpression() {

	/** 
	 * This is a recursive algorithm that will continue to parse more expressions 
	 * based on these rules: 
	 *  1: We encounter an operator, therefore anticipate a unary operation (ex. op <exp> )
	 *  2: We encounter a value, therefore anticipate either:
	 *		a. an optional unary expression (ex. <exp> op )
	 *		b. an optional binary operation (ex. <exp> op <exp> )
	 *		c. only a value, therefore the end of the expression	 
	 *  3: Anything else implies the end of the expression (ex. a comma or semicolon)
	 */
	
	/** Unary operation **/
	
	if (lexer.unary_operators.count(token.value)) {
		/* Expect a unary operator */
		if (!lexer.unary_operators.count(token.value)) {
			throw Exception(token);
		}
		next();
		
		/* Expect an expression (recursion) */
		parseExpression();
		return;
	}
	
	/** Binary operation **/
	
	/* Literal */
	if (isliteral()) {
		next();
	}
	
	/* Open backet (list) */
	else if (token.type == Token::T_LIST_OPEN) {
		parseList();
	}		
	
	/* Open parenthesis (sub-expression) */
	else if (token.type == Token::T_GROUP_OPEN) {
		next();
		
		/* Expect an expression */
		parseExpression();
		
		/* Expect close parenthesis */
		if (token.type != Token::T_GROUP_CLOSE) {
			throw Exception(token);
		}
		next();
	}		
	
	else {
		/* Optional namespace name */
		if (token.type == Token::T_NAMESPACE_NAME) {
			next();
		}
		
		/* Variable */
		if (token.type == Token::T_VARIABLE) {
			next();
		}
		
		/* Constant */
		else if (token.type == Token::T_CONSTANT) {
			next();
		}
		
		/* Class name */
		else if (token.type == Token::T_CLASS_NAME) {
			next();
		}
		
		/* Function name */
		else if (token.type == Token::T_FUNCTION_NAME) {
			next();
			
			/* Expect a parameters list */
			parseArguments();
		}			
		
		else {
			/** End of operation **/
			return;
		}
	}
	
	/* Optional unary operator */
	if (lexer.unary_operators.count(token.value)) {
		next();
	}	
	
	/* Optional binary operator */
	if (lexer.binary_operators.count(token.value)) {
		next();
		
		/* Expect an expression (recursion) */
		parseExpression();
	}
	
	/** End of operation **/
}

void Parser::parseNamespaceDeclaration() {
	/* Expect label 'namespace' */
	if (token.type != Token::T_NAMESPACE) {
		throw Exception(token);
	}
	next();
		
	/* Expect a namespace name */
	if (token.type != Token::T_NAMESPACE_NAME) {
		throw Exception(token);
	}
//	this->_namespace = &this->_namespace->addNamespace(token.value);
	next();
			
	/* Expect a terminator */
	if (token.type != Token::T_TERMINATOR) {
		throw Exception(token);
	}
	next();
}

void Parser::parseFunctionDeclaration() {	
	/* Expect label 'function' */
	if (token.type != Token::T_FUNCTION) {
		throw Exception(token);
	}
	next();

	/* Expect a function name */
	if (token.type != Token::T_FUNCTION_NAME) {
		throw Exception(token);
	}
//	Function& _function = _scope.addFunction(token.value);
	next();
			
	/* Expect a parameter list */
	parseParameters();
			
	/* Expect a function body (closure) */
	parseClosure();
	
	/* Optional terminator */
	if (token.type == Token::T_TERMINATOR) {
		next();
	}
}

void Parser::parseClassDeclaration() {

	token.type = Token::T_UNKNOWN;
}

void Parser::parseInterfaceDeclaration() {
	
	token.type = Token::T_UNKNOWN;
}

void Parser::parseConstantDeclaration() {
	/* Expect label 'const' */
	if (token.type != Token::T_CONST) {
		throw Exception(token);
	}
	next();
			
	/* Expect a constant */
	if (token.type != Token::T_CONSTANT) {
		throw Exception(token);
	}
	next();
			
	/* Expect a terminator */
	if (token.type != Token::T_TERMINATOR) {
		throw Exception(token);
	}
	next();
}

void Parser::parseVariableDeclaration() {
	/* Expect label 'var' */
	if (token.type != Token::T_VAR) {
		throw Exception(token);
	}
	next();
		
	/* Optional namespace name (scope) */
	if (token.type == Token::T_NAMESPACE_NAME) {
		next();
	}
	
	/* Expect a variable */
	if (token.type != Token::T_VARIABLE) {
		throw Exception(token);
	}
	next();
			
	/* Optional assignment */
	if (token.type == Token::T_ASSIGN) {
		next();
		
		/* Expect an expression */
		parseExpression();
	}
	
	/* Expect a terminator */
	if (token.type != Token::T_TERMINATOR) {
		throw Exception(token);
	}
	next();
}

void Parser::parseIfStatement() {
	/* Expect label 'if' */
	if (token.type != Token::T_IF) {
		throw Exception(token);
	}
	next();
			
	/* Expect a condition */
	parseCondition();
			
	/* Expect a body (closure) */
	parseClosure();
			
	/* Optional elseif */
	if (token.type == Token::T_ELSEIF) {
		next();
		
		/* Expect a condition */
		parseCondition();
		
		/* Expect a body (closure) */
		parseClosure();		
	}			

			
	/* Optional else */
	if (token.type == Token::T_ELSE) {
		next();
		
		/* Expect a body (closure) */
		parseClosure();	
	}
	
	/* Optional terminator */
	if (token.type == Token::T_TERMINATOR) {
		next();
	}	
}

void Parser::parseWhileStatement() {
	/* Expect label 'while' */
	if (token.type != Token::T_WHILE) {
		throw Exception(token);
	}
	next();
			
	/* Expect a condition */
	parseCondition();
	
	/* Expect a body (closure) */
	parseClosure();
			
	/* Optional terminator */
	if (token.type == Token::T_TERMINATOR) {
		next();
	}
}

void Parser::parseCondition() {
	/* Expect open parenthesis */
	if (token.type != Token::T_GROUP_OPEN) {
		throw Exception(token);
	}
	next();
				
	/* Expect an expression */
	parseExpression();
		
	/* Expect a close parenthesis */
	if (token.type != Token::T_GROUP_CLOSE) {
		throw Exception(token);
	}
	next();
}

void Parser::parseClosure() {
	/* Expect open braces */
	if (token.type != Token::T_CLOSURE_OPEN) {
		throw Exception(token);
	}
	next();
					
	/* Expect any number of statements */
	while (token.type != Token::T_CLOSURE_CLOSE) {
		parseStatement();
	}
			
	/* Expect close braces */
	if (token.type != Token::T_CLOSURE_CLOSE) {
		throw Exception(token);
	}
	next();
}

void Parser::parseParameters() {
	/* Expect open parenthesis */
	if (token.type != Token::T_GROUP_OPEN) {
		throw Exception(token);
	}
	next();
			
	/* Expect any number of parameters */
	while (token.type != Token::T_GROUP_CLOSE) {
		
		/* Expect a variable */
		if (token.type != Token::T_VARIABLE) {
			throw Exception(token);
		}
//		Parameter parameter(token.value);
		next();
			
		/* Optional optional (?) operator */
		if (token.type == Token::T_OPTIONAL) {
			//parameter.isOptional = true;
			next();
		}
			
		/* OR an optional default assignment (?:) operator */
		else if (token.type == Token::T_ASSIGN_DEFAULT) {
			next();
			
			/* Expect a literal */
			if (!isliteral()) {
				throw Exception(token);
			}
			next();
		}	
			
		/* Optional cast (:) operator */
		if (token.type == Token::T_CAST) {
			next();
			
			/* Optional namespace name */
			if (token.type == Token::T_NAMESPACE_NAME) {
				next();
			}
			
			/* Expect a class name label */
			if (token.type != Token::T_CLASS_NAME) {
				throw Exception(token);
			}	
			next();
		}
//		_function.addParameter(parameter);
			
		/* Expect delimiter if not end of parameters */
		if (token.type != Token::T_GROUP_CLOSE) {
			
			if (token.type != Token::T_DELIMITER) {
				throw Exception(token);
			}
			next();
		}		
	}

	/* Expect close parenthesis */
	if (token.type != Token::T_GROUP_CLOSE) {
		throw Exception(token);
	}			
	next();
}

void Parser::parseArguments() {
	/* Expect open parenthesis */
	if (token.type != Token::T_GROUP_OPEN) {
		throw Exception(token);
	}
	next();
	
	/* Expect any number of arguments */
	while (token.type != Token::T_GROUP_CLOSE) {
		
		/* Expect an expression */
		parseExpression();
		
		/* Expect delimiter if not end of parameters */
		if (token.type != Token::T_GROUP_CLOSE) {
			
			if (token.type != Token::T_DELIMITER) {
				throw Exception(token);
			}
			next();
		}		
	}
	
	/* Expect close parenthesis */
	if (token.type != Token::T_GROUP_CLOSE) {
		throw Exception(token);
	}			
	next();
}

void Parser::parseList() {
	/* Expect open bracket */
	if (token.type != Token::T_LIST_OPEN) {
		throw Exception(token);
	}
	next();
		
	/* Expect any number of expressions */
	while (token.type != Token::T_LIST_CLOSE) {
		
		/* Expect an expression */
		parseExpression();
		
		/* Expect delimiter if not end of list */
		if (token.type != Token::T_LIST_CLOSE) {
			
			if (token.type != Token::T_DELIMITER) {
				throw Exception(token);
			}
			next();
		}
	}

	/* Expect close bracket */
	if (token.type != Token::T_LIST_CLOSE) {
		throw Exception(token);
	}
	next();
}

bool Parser::isliteral() {	
	switch (token.type) {
		case Token::T_INTEGER:
		case Token::T_FLOAT:
		case Token::T_SCIENTIC:
		case Token::T_HEXIDECIMAL:
		case Token::T_BINARY:
		case Token::T_CONSTANT_STRING:
		case Token::T_DYNAMIC_STRING:
		case Token::T_BOOLEAN:
		case Token::T_NULL:
			return true;
	}
	
	return false;
}

Parser::Exception::Exception(Token token) throw() {
	message = "Syntax Error: Expected token " + token.label() + " '" + token.value + "' in file () on line ()";
}

Parser::Exception::~Exception() throw() {

}