#include "../include/threeAddressCodeList.h"



void createThreeAddressCodeList(TAst *ast, ThreeAddressCodeList *list){
    enum TTag treeTag = ast->data.tag;    
    if(isEmptyAst(*ast)){
        return ;
    }    
    if(treeTag == DECL){
        if(isLeaf(ast->rs)){
            ThreeAddressCodeNode *node = threeAddressCodeNodeFactory(ASS, &ast->ls->data, &ast->rs->data, newEmptyNodeInfo());
            addToTAC(list, node);
        }else{
            createThreeAddressCodeList(ast->rs, list);
            NodeInfo *temp = createTemporalNodeInfo(createTemportalID(list->size), EXPR_OP);
            ThreeAddressCodeNode *node = threeAddressCodeNodeFactory(ASSIGN, &ast->ls->data, temp, newEmptyNodeInfo());
            addToTAC(list, node);
        }
    }else if(treeTag == EXPR_OP){
            if(isLeaf(ast->ls) && isLeaf(ast->rs)){
                NodeInfo *temp = createTemporalNodeInfo(createTemportalID(list->size), EXPR_OP);
                ThreeAddressCodeNode *node = threeAddressCodeNodeFactory(
                    getLabelFromID(ast->data.id, ast->data.type), temp, &ast->ls->data, &ast->rs->data);
                addToTAC(list, node);
            }else{
               
                NodeInfo *temp = createTemporalNodeInfo(createTemportalID(list->size), EXPR_OP);
                ThreeAddressCodeNode *node;
                
                if(isLeaf(ast->ls) && !isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->rs, list);
                    node = threeAddressCodeNodeFactory(
                        getLabelFromID(ast->data.id, ast->data.type), temp, &ast->ls->data, 
                        getFirst(getFromTAC(list, list->size)));
                }else if(!isLeaf(ast->ls) && isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->ls, list);
                    node = threeAddressCodeNodeFactory(
                        getLabelFromID(ast->data.id, ast->data.type), temp, getFirst(getFromTAC(list, list->size)),
                            &ast->rs->data);
                }else if(!isLeaf(ast->ls) && !isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->ls, list);
                    createThreeAddressCodeList(ast->rs, list);
                    node = threeAddressCodeNodeFactory(
                        getLabelFromID(ast->data.id, ast->data.type), temp, getFirst(getFromTAC(list, list->size - 1)),
                        getFirst(getFromTAC(list, list->size)));
                }
                
                addToTAC(list, node);
            }
    }else if(treeTag == ASSIGNMENT_OP){
        if(isLeaf(ast->rs)){
            ThreeAddressCodeNode *node = malloc(sizeof(ThreeAddressCodeNode*));
            node = threeAddressCodeNodeFactory(ASS, &ast->ls->data, &ast->rs->data, newEmptyNodeInfo());
            
            addToTAC(list, node);

        }else{
            createThreeAddressCodeList(ast->rs, list);
            ThreeAddressCodeNode *node = threeAddressCodeNodeFactory(
                                            ASS, &ast->ls->data, getFromTAC(list, list->size)->first, newEmptyNodeInfo());
            
            addToTAC(list, node);
        }
    }else if(treeTag == RETURN){
        if(isLeaf(ast->rs)){
            ThreeAddressCodeNode *node = threeAddressCodeNodeFactory(RET, &ast->rs->data, 
                                                    newEmptyNodeInfo(), newEmptyNodeInfo());
            addToTAC(list, node);
        }else{
            createThreeAddressCodeList(ast->rs, list);
            ThreeAddressCodeNode *node = threeAddressCodeNodeFactory(RET, getFromTAC(list, list->size)->first, 
                                                    newEmptyNodeInfo(), newEmptyNodeInfo());

            addToTAC(list, node);
        }
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

NodeInfo *createTemporalNodeInfo(char* id, enum TTag tag){
    NodeInfo *temp = newEmptyNodeInfo();
    temp->id = malloc(20);
    strcpy(temp->id, id);
    temp->tag = tag;
    return temp;
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