/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char *name) {
  // Todo
  Scope* currentScope = symtab->currentScope;
  Object* result;

  // Tìm kiếm trong scope chain
  while (currentScope != NULL) {
    result = findObject(currentScope->objList, name);
    if (result != NULL) {
      return result;
    }
    currentScope = currentScope->outer; // Chuyển sang scope bên ngoài
  }

  // Tìm trong global objects
  result = findObject(symtab->globalObjectList, name);
  return result; // NULL hoặc ọbject
}

void checkFreshIdent(char *name) {
  // TODO
  Object* obj = findObject(symtab->currentScope->objList, name);
  if (obj != NULL) {
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
  }

  return;
}

Object* checkDeclaredIdent(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
  {
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}

Object* checkDeclaredConstant(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  // Kiểm tra khai báo
  if (obj == NULL) {
    error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
  }

  // Kiểm tra loại đối tượng constant
  if (obj->kind != OBJ_CONSTANT) {
    error(ERR_INVALID_CONSTANT, currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}

Object* checkDeclaredType(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
  {
    error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
  }

  if (obj->kind != OBJ_TYPE)
  {
    error(ERR_INVALID_TYPE, currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}

Object* checkDeclaredVariable(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
  {
    error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
  }

  // var hoặc param 
  if (obj->kind != OBJ_VARIABLE && obj->kind != OBJ_PARAMETER) {
    error(ERR_INVALID_VARIABLE, currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}

Object* checkDeclaredFunction(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
  {
    error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
  }

  if (obj->kind != OBJ_FUNCTION)
  {
    error(ERR_INVALID_FUNCTION, currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}

Object* checkDeclaredProcedure(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
  {
    error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);
  }

  if (obj->kind != OBJ_PROCEDURE)
  {
    error(ERR_INVALID_PROCEDURE, currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}

Object* checkDeclaredLValueIdent(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL) {
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  }
  
  // Kiểm tra Object là LValue không
  // VARIABLE, PARAMETER, FUNCTION (hàm hiện tại)
  if (obj->kind != OBJ_VARIABLE && 
      obj->kind != OBJ_PARAMETER && 
      obj->kind != OBJ_FUNCTION) {
    error(ERR_INVALID_LVALUE, currentToken->lineNo, currentToken->colNo);
  }
  
  return obj;
}

