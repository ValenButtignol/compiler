#include "../../include/dataStructures/threeAddressCodeList.h"

extern int getOffset(void);


void createThreeAddressCodeList(TAst *ast, ThreeAddressCodeList *list, int* offset){
    enum TTag treeTag = ast->data->tag;    
    if(isEmptyAst(*ast) || treeTag == NONETAG){
        return ;
    }    
    if(isAssignTag(treeTag)){
        ThreeAddressCodeNode *node;
        if(isLeaf(ast->rs)){
            node = threeAddressCodeNodeFactory(ASSIGNMENT, ast->ls->data, ast->rs->data, newEmptyNodeInfo());
            addToTAC(list, node);
        }else{

            *offset = *offset + 1;

            createThreeAddressCodeList(ast->rs, list, offset);
            createTemporalNodeInfo(createTemportalID(*offset), ast->data, *offset);

            ThreeAddressCodeNode *node = 
            threeAddressCodeNodeFactory(ASSIGNMENT, ast->ls->data, ast->data, newEmptyNodeInfo());
            addToTAC(list, node);
        }
    }else if(isArithmeticOrBooleanTag(treeTag)){

            *offset = *offset + 1;

            ThreeAddressCodeNode *node;

            if(isLeaf(ast->ls) && isLeaf(ast->rs)){
                createTemporalNodeInfo(createTemportalID(*offset), ast->data, *offset);
                node = threeAddressCodeNodeFactory(ast->data->tag, ast->data, ast->ls->data, ast->rs->data);
            }else{    
                if(isLeaf(ast->ls) && !isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->rs, list, offset);
                    createTemporalNodeInfo(createTemportalID(*offset), ast->data, *offset);
                    node = threeAddressCodeNodeFactory(
                        ast->data->tag, ast->data, ast->ls->data, getFirst(getFromTAC(list, list->size)));
                }else if(!isLeaf(ast->ls) && isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->ls, list, offset);
                    createTemporalNodeInfo(createTemportalID(*offset), ast->data, *offset);
                    node = threeAddressCodeNodeFactory(
                        ast->data->tag, ast->data, getFirst(getFromTAC(list, list->size)), ast->rs->data);
                }else if(!isLeaf(ast->ls) && !isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->ls, list, offset);
                    createThreeAddressCodeList(ast->rs, list, offset);
                    createTemporalNodeInfo(createTemportalID(*offset), ast->data, *offset);
                    node = threeAddressCodeNodeFactory(ast->data->tag, ast->data, 
                                                getFirst(getFromTAC(list, list->size - 1)),
                                                getFirst(getFromTAC(list, list->size-0))
                                            );
                }
            }
            addToTAC(list, node);
    }else if(isReturnTag(treeTag) || isUnaryOperatorTag(treeTag)){
        ThreeAddressCodeNode *node;
        if(isLeaf(ast->ls)){
            node = threeAddressCodeNodeFactory(RETURN, ast->ls->data, 
                                                    newEmptyNodeInfo(), newEmptyNodeInfo());
        }else{
            createThreeAddressCodeList(ast->ls, list, offset);
            node = threeAddressCodeNodeFactory(RETURN, getFromTAC(list, list->size)->first, 
                                                    newEmptyNodeInfo(), newEmptyNodeInfo());
        }
        addToTAC(list, node);
    // } else if(isIf(treeTag)){
        
    
    
    // } else if(isIfElse(treeTag)){

    
    
    // } else if(isWhile(treeTag)){

    
    
    // } else if(isMethodDecl(treeTag)){

    
    
    } else if(isMethodCallTag(treeTag)){
        createThreeAddressCodeList(ast->ls, list, offset);
        TAst *params = ast->ls;
        int registerNumber = 1;
        while(params != NULL){
            ThreeAddressCodeNode *node;
            NodeInfo *ni = newNodeInfoRegisterNumber(registerNumber);
            NodeInfo *nd = params->rs->data;
            node = threeAddressCodeNodeFactory(
                    LOAD,
                    nd,
                    ni,
                    NULL
            );
            addToTAC(list, node);
            params = params->ls;
            registerNumber++;
        }
        ThreeAddressCodeNode *node;
            NodeInfo *nd = ast->rs->data;
            node = threeAddressCodeNodeFactory(
                    ast->data->tag,
                    nd,
                    NULL,
                    NULL
            );
            addToTAC(list, node);

    }else if (treeTag == NONETAG) {
        return;
    }else{
        if(ast->ls!=NULL)createThreeAddressCodeList(ast->ls, list, offset);
        if(ast->rs!=NULL)createThreeAddressCodeList(ast->rs, list, offset);
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