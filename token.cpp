#include "token.h"

using namespace std;

//===----------------------------------------------------------------------===//
// Token
//===----------------------------------------------------------------------===//

Token::Token() { }

string Token::label() {
	switch (type) {
		case T_UNKNOWN:
			return "T_UNKNOWN";
			break;
		case T_CLOSURE_OPEN:
			return "T_CLOSURE_OPEN";
			break;
		case T_CLOSURE_CLOSE:
			return "T_CLOSURE_CLOSE";
			break;
		case T_LIST_OPEN:
			return "T_LIST_OPEN";
			break;
		case T_LIST_CLOSE:
			return "T_LIST_CLOSE";
			break;
		case T_GROUP_OPEN:
			return "T_GROUP_OPEN";
			break;
		case T_GROUP_CLOSE:
			return "T_GROUP_CLOSE";
			break;
		case T_INTEGER:
			return "T_INTEGER";
			break;
		case T_FLOAT:
			return "T_FLOAT";
			break;
		case T_SCIENTIC:
			return "T_SCIENTIC";
			break;
		case T_HEXIDECIMAL:
			return "T_HEXIDECIMAL";
			break;
		case T_BINARY:
			return "T_BINARY";
			break;
		case T_CONSTANT_STRING:
			return "T_CONSTANT_STRING";
			break;
		case T_DYNAMIC_STRING:
			return "T_DYNAMIC_STRING";
			break;
		case T_EXECUTABLE_STRING:
			return "T_EXECUTABLE_STRING";
			break;
		case T_BOOLEAN:
			return "T_BOOLEAN";
			break;
		case T_NULL:
			return "T_NULL";
			break;
		case T_COMMENT:
			return "T_COMMENT";
			break;	
		case T_NAMESPACE_NAME:
			return "T_NAMESPACE_NAME";
			break;
		case T_FUNCTION_NAME:
			return "T_FUNCTION_NAME";
			break;
		case T_CLASS_NAME:
			return "T_CLASS_NAME";
			break;
		case T_VARIABLE:
			return "T_VARIABLE";
			break;
		case T_CONSTANT:
			return "T_CONSTANT";
			break;
		case T_EXIT:
			return "T_EXIT";
			break;
		case T_RETURN:
			return "T_RETURN";
			break;
		case T_BREAK:
			return "T_BREAK";
			break;
		case T_CONTINUE:
			return "T_CONTINUE";
			break;
		case T_TRY:
			return "T_TRY";
			break;
		case T_CATCH:
			return "T_CATCH";
			break;
		case T_FINALLY:
			return "T_FINALLY";
			break;
		case T_THROW:
			return "T_THROW";
			break;
		case T_IF:
			return "T_IF";
			break;
		case T_ELSE:
			return "T_ELSE";
			break;
		case T_ELSEIF:
			return "T_ELSEIF";
			break;
		case T_WHILE:
			return "T_WHILE";
			break;
		case T_DO:
			return "T_DO";
			break;
		case T_FOREACH:
			return "T_FOREACH";
			break;
		case T_SWITCH:
			return "T_SWITCH";
			break;
		case T_CASE:
			return "T_CASE";
			break;
		case T_DEFAULT:
			return "T_DEFAULT";
			break;
		case T_NAMESPACE:
			return "T_NAMESPACE";
			break;
		case T_IMPORT:
			return "T_IMPORT";
			break;
		case T_FUNCTION:
			return "T_FUNCTION";
			break;
		case T_CLASS:
			return "T_CLASS";
			break;
		case T_INTERFACE:
			return "T_INTERFACE";
			break;
		case T_VAR:
			return "T_VAR";
			break;
		case T_CONST:
			return "T_CONST";
			break;
		case T_CLOSURE:
			return "T_CLOSURE";
			break;
		case T_EXTENDS:
			return "T_EXTENDS";
			break;
		case T_IMPLEMENTS:
			return "T_IMPLEMENTS";
			break;
		case T_USES:
			return "T_USES";
			break;
		case T_ABSTRACT:
			return "T_ABSTRACT";
			break;
		case T_FINAL:
			return "T_FINAL";
			break;
		case T_PRIVATE:
			return "T_PRIVATE";
			break;
		case T_PROTECTED:
			return "T_PROTECTED";
			break;
		case T_PUBLIC:
			return "T_PUBLIC";
			break;
		case T_LOGICAL_AND:
			return "T_LOGICAL_AND";
			break;
		case T_LOGICAL_OR:
			return "T_LOGICAL_OR";
			break;
		case T_LOGICAL_XOR:
			return "T_LOGICAL_XOR";
			break;
		case T_LOGICAL_NOT:
			return "T_LOGICAL_NOT";
			break;
		case T_ADD:
			return "T_ADD";
			break;
		case T_INCREMENT:
			return "T_INCREMENT";
			break;
		case T_SUBTRACT:
			return "T_SUBTRACT";
			break;
		case T_DECREMENT:
			return "T_DECREMENT";
			break;
		case T_DIVIDE:
			return "T_DIVIDE";
			break;
		case T_MODULUS:
			return "T_MODULUS";
			break;
		case T_MULTIPLY:
			return "T_MULTIPLY";
			break;
		case T_GREATER_OR_EQUAL:
			return "T_GREATER_OR_EQUAL";
			break;
		case T_STRICTLY_GREATER:
			return "T_STRICTLY_GREATER";
			break;
		case T_LESS_OR_EQUAL:
			return "T_LESS_OR_EQUAL";
			break;
		case T_STRICTLY_LESS:
			return "T_STRICTLY_LESS";
			break;
		case T_EQUAL:
			return "T_EQUAL";
			break;
		case T_IDENTICAL:
			return "T_IDENTICAL";
			break;
		case T_NOT_EQUAL:
			return "T_NOT_EQUAL";
			break;
		case T_NOT_IDENTICAL:
			return "T_NOT_IDENTICAL";
			break;
		case T_ASSIGN:
			return "T_ASSIGN";
			break;
		case T_ASSIGN_ADD:
			return "T_ASSIGN_ADD";
			break;
		case T_ASSIGN_SUBTRACT:
			return "T_ASSIGN_SUBTRACT";
			break;
		case T_ASSIGN_DIVIDE:
			return "T_ASSIGN_DIVIDE";
			break;
		case T_ASSIGN_MODULUS:
			return "T_ASSIGN_MODULUS";
			break;
		case T_ASSIGN_MULTIPLY:
			return "T_ASSIGN_MULTIPLY";
			break;
		case T_ASSIGN_DEFAULT:
			return "T_ASSIGN_DEFAULT";
			break;
		case T_CAST:
			return "T_CAST";
			break;
		case T_TERMINATOR:
			return "T_TERMINATOR";
			break;
		case T_DELIMITER:
			return "T_DELIMITER";
			break;
		case T_ACCESSOR:
			return "T_ACCESSOR";
			break;
		case T_ANNOTATION:
			return "T_ANNOTATION";
			break;
		case T_OPTIONAL:
			return "T_OPTIONAL";
			break;
		case T_TERNARY:
			return "T_TERNARY";
			break;
		case T_GENERIC:
			return "T_GENERIC";
			break;
		case T_EOF:
			return "T_EOF";
			break;
		default:
			return "INVALID";
	}
}