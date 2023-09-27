#include "../include/threeAddressCodeList.h"



void createThreeAddressCodeList(TAst *ast, ThreeAddressCodeList *list){
    enum TTag treeTag = ast->data.tag;    
    if(isEmptyAst(*ast)){
        return ;
    }    
    if(treeTag == DECL){
        ThreeAddressCodeNode *node;
        if(isLeaf(ast->rs)){
            node = threeAddressCodeNodeFactory(MOV, &ast->ls->data, &ast->rs->data, newEmptyNodeInfo());
            addToTAC(list, node);
        }else{
            createTemporalNodeInfo(createTemportalID(list->size), EXPR_OP, &ast->data);
            createThreeAddressCodeList(ast->rs, list);
            ThreeAddressCodeNode *node = 
            threeAddressCodeNodeFactory(MOV, &ast->ls->data, &ast->data, newEmptyNodeInfo());
            addToTAC(list, node);
        }
    }else if(treeTag == EXPR_OP){
            createTemporalNodeInfo(createTemportalID(list->size), EXPR_OP, &ast->data);
            ThreeAddressCodeNode *node;

            if(isLeaf(ast->ls) && isLeaf(ast->rs)){
                node = threeAddressCodeNodeFactory(
                    getLabelFromOperator(ast->data.operator, ast->data.type), &ast->data, &ast->ls->data, &ast->rs->data);
            }else{    
                if(isLeaf(ast->ls) && !isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->rs, list);
                    node = threeAddressCodeNodeFactory(
                        getLabelFromOperator(ast->data.operator, ast->data.type), &ast->data, &ast->ls->data, 
                        getFirst(getFromTAC(list, list->size)));
               
                }else if(!isLeaf(ast->ls) && isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->ls, list);
                    node = threeAddressCodeNodeFactory(
                        getLabelFromOperator(ast->data.operator, ast->data.type), &ast->data, getFirst(getFromTAC(list, list->size)),
                            &ast->rs->data);
               
                }else if(!isLeaf(ast->ls) && !isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->ls, list);
                    createThreeAddressCodeList(ast->rs, list);
                    node = threeAddressCodeNodeFactory(
                        getLabelFromOperator(ast->data.operator, ast->data.type), &ast->data, getFirst(getFromTAC(list, list->size - 1)),
                        getFirst(getFromTAC(list, list->size)));
                }
            }
            addToTAC(list, node);
    }else if(treeTag == ASSIGNMENT_OP){
        ThreeAddressCodeNode *node;
        if(isLeaf(ast->rs)){
            node = malloc(sizeof(ThreeAddressCodeNode*));
            node = threeAddressCodeNodeFactory(MOV, &ast->ls->data, &ast->rs->data, newEmptyNodeInfo());       
            addToTAC(list, node);
        }else{
            createThreeAddressCodeList(ast->rs, list);
            node = threeAddressCodeNodeFactory(
                                            MOV, &ast->ls->data, getFromTAC(list, list->size)->first, newEmptyNodeInfo());
            addToTAC(list, node);
        }
    }else if(treeTag == RETURN){
        ThreeAddressCodeNode *node;
        if(isLeaf(ast->rs)){
            node = threeAddressCodeNodeFactory(RET, &ast->rs->data, 
                                                    newEmptyNodeInfo(), newEmptyNodeInfo());
        }else{
            createThreeAddressCodeList(ast->rs, list);
            node = threeAddressCodeNodeFactory(RET, getFromTAC(list, list->size)->first, 
                                                    newEmptyNodeInfo(), newEmptyNodeInfo());
        }
        addToTAC(list, node);
    } else if (treeTag == NONETAG) {
        return;
    }else{
        createThreeAddressCodeList(ast->ls, list);
        createThreeAddressCodeList(ast->rs, list);
    }

}

char* threeAddressListToString(ThreeAddressCodeList *list){

    ThreeAddressCodeNode *h = list->head->next;
    char *str = malloc(list->size*100);
    while(h != NULL)
    {   
        strcat(str, threeAddressCodeNodeToString(h));
        strcat(str, "\n");
        h = h->next;
    }
    strcat(str, "");   
    return str;
}



char *createTemportalID(int tempNumber){
    char* id = malloc(10);
    char* num = malloc(2);
    strcpy(id, "temp");
    sprintf(num, "%d", tempNumber);
    strcat(id, num);
    return id;
}

void addToTAC(ThreeAddressCodeList* list,ThreeAddressCodeNode* node){
    ThreeAddressCodeNode *h = list->head;
    while(h->next != NULL){
        h = h->next;
    }
    h->next = node;
    list->size++;
    node->next = NULL;
}

ThreeAddressCodeNode *getFromTAC(ThreeAddressCodeList *list, int index){
    ThreeAddressCodeNode *h = list->head;
    for (int i = 0; i < index; i++)
    {
        h = h->next;
    }
    return h;
}

ThreeAddressCodeList *createEmptyTAC(){
   ThreeAddressCodeList *list = malloc(sizeof(ThreeAddressCodeList*));

   list->head = newEmtyNodeTAC();
   list->size = 0;

    return list;
}