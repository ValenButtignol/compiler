#include "../../include/algorithms/checktypes.h"

int checkTypes(TAst* ast, ErrorNode** errors) {
    setTypesInAst(ast, errors);

    if (*errors != NULL) {
        return 0;
    }

    return 1;
}   
enum TType currentMethodType;

void setTypesInAst(TAst* ast, ErrorNode** errors) {

    if (ast == NULL || isEmptyAst(*ast)) {
        printf("isNULL == %s ", ast==NULL?"YES":"NO");
        if(ast!=NULL){
            printf("TAG BASE == %s ", tagToString(ast->data->tag));
            printf("isEMPTY == %s ", isEmptyAst(*ast)?"YES":"NO");
            printf("TYPE = %s ", typeToString(ast->data->type));
            printf("ID = %s ", ast->data->id==NULL?"NO ID":ast->data->id);
        }
        printf("BASE CASE \n");
        return;
    }


    printf("TAG == %s TYPE == %s ID == %s\n", 
    tagToString(ast->data->tag), 
    typeToString(ast->data->type), 
    ast->data->id!=NULL&&strcmp(ast->data->id, "")!=0?ast->data->id:"NO ID");
    
    if(ast->data->type != NONETYPE){
        enum TType lsType = getAstType(ast->ls);
        enum TType rsType = getAstType(ast->rs);
        if(isAssignTag(ast->data->tag)){
            if(lsType == rsType && lsType==ast->data->type){
                printf("\033[1;32mAssign CHEQUEO DE TIPOS CORRECTO\033[0m\n");
            }else{
                printf("\033[1;31mAssign CHEQUEO DE TIPOS INCORRECTO \033[0m%s %s %s\n", typeToString(ast->data->type), typeToString(lsType), typeToString(rsType));
            }
        }
        if(isBooleanOperatorTag(ast->data->tag)){
            if(lsType == rsType && lsType==ast->data->type){
                printf("\033[1;32mBoolean CHEQUEO DE TIPOS CORRECTO \033[0m\n");
            }else{
                printf("\033[1;31mBoolean CHEQUEO DE TIPOS INCORRECTO \033[0m %s %s %s\n", typeToString(ast->data->type), typeToString(lsType), typeToString(rsType));
            }
        }
        if(isComparatorTag(ast->data->tag)){
            int i = 0;
            if(lsType == rsType){
                printf("\033[1;32mComparator CHEQUEO DE TIPOS CORRECTO %d \033[0m\n", i);
                i++;
            }else{
                printf("\033[1;31mComparator CHEQUEO DE TIPOS INCORRECTO \033[0m %s %s %s %d\n", typeToString(ast->data->type), typeToString(lsType), typeToString(rsType), i);
            }
        }
        if(isArithmeticOperatorTag(ast->data->tag)){
            if(lsType == rsType && lsType==ast->data->type){
                printf("\033[1;32mArithmetic CHEQUEO DE TIPOS CORRECTO \033[0m\n");
            }else{
                printf("\033[1;31mArithmetic CHEQUEO DE TIPOS INCORRECTO \033[0m %s %s %s\n", typeToString(ast->data->type), typeToString(lsType), typeToString(rsType));
            }
        }
        if(isUnaryOperatorTag(ast->data->tag)){
            if(lsType == rsType && lsType==ast->data->type){
                printf("\033[1;32mUnary CHEQUEO DE TIPOS CORRECTO \033[0m\n");
            }else{
                printf("\033[1;31mUnary CHEQUEO DE TIPOS INCORRECTO \033[0m %s %s %s\n", typeToString(ast->data->type), typeToString(lsType), typeToString(rsType));
            }
        }if(ast->data->tag == RETURN){
            if(lsType==ast->data->type){
                printf("\033[1;32mReturn CHEQUEO DE TIPOS CORRECTO \033[0m\n");
            }else if(VOID==ast->data->type && ast->ls==NULL && lsType==NONETYPE){
                printf("\033[1;32mReturn CHEQUEO DE TIPOS CORRECTO \033[0m\n");
            }
            else{
                printf("\033[1;31mReturn CHEQUEO DE TIPOS INCORRECTO \033[0m %s %s\n", typeToString(ast->data->type), typeToString(lsType));
            }
        }
        // printf("TYPE = %s\n", typeToString(ast->data->type));
        if(ast->data->tag==METHOD_CALL){
            printf("METHOD NAME == %s\n", ast->rs->data->id);
            NodeInfo* currentParameters = ast->data->nextParams;
            NodeInfo* formalParameters = ast->rs->data->nextParams;
            while(currentParameters != NULL && formalParameters != NULL ){
                printf("\033[1;34mParametro %s %s\033[0m\n",tagToString(currentParameters->tag), typeToString(currentParameters->type));
                printf("\033[1;34mParametro %s %s\033[0m\n",tagToString(formalParameters->tag), typeToString(formalParameters->type));
                if(currentParameters->type == formalParameters->type){
                    printf("\033[1;32mParametros CHEQUEO DE TIPOS CORRECTO \033[0m\n");
                }else{
                    printf("\033[1;31mParametros CHEQUEO DE TIPOS INCORRECTO \033[0m %s %s\n",typeToString(formalParameters->type), typeToString(currentParameters->type));
                }
                currentParameters = currentParameters->nextParams;
                formalParameters = formalParameters->nextParams;
            }
            if(currentParameters != NULL){//dividir el if para diferenciar el error
                printf("\033[1;31mParametros Demasiado parametros %s %s\033[0m\n",tagToString(currentParameters->tag), typeToString(currentParameters->type));
            }
            if(formalParameters != NULL){//dividir el if para diferenciar el error
                printf("\033[1;31mParametros faltan parametros \033[0m\n");
            }
            printf("\033[1;34mFINALIZE CHEQUEO PARAMETROS\033[0m\n");

        }
    }
    setTypesInAst(ast->ls, errors);
    setTypesInAst(ast->rs, errors);
}

enum TType getAstType(TAst* ast) { 
    if(ast==NULL) return NONETYPE;
    if ((ast->data)->type != NONETYPE) {
        return (ast->data)->type;
    }
    enum TType lsType = getAstType(ast->ls);
    enum TType rsType = getAstType(ast->rs);
    if (lsType != rsType) {
        return ERROR;
    }
    (ast->data)->type = lsType;
    return lsType;

}