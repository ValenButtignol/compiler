#ifndef CHECKTYPES_H
#define CHECKTYPES_H
int checkTypes(TAst* ast, ErrorNode** errors);
void setTypesInAst(TAst* ast, ErrorNode** errors);
enum TType getAstType(TAst* ast);
#endif