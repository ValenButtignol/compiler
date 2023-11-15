#include "../../include/dataStructures/threeAddressCodeList.h"

extern int getOffset(void);


void createThreeAddressCodeList(TAst *ast, ThreeAddressCodeList *list, int* offset, int* labelCounter){
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

            createThreeAddressCodeList(ast->rs, list, offset, labelCounter);
            createTemporalNodeInfo(createTemporalID(*offset), ast->data, *offset);
            ThreeAddressCodeNode *node = 
            threeAddressCodeNodeFactory(ASSIGNMENT, ast->ls->data, ast->data, newEmptyNodeInfo());
            addToTAC(list, node);
        }
    }else if(isArithmeticOrBooleanTag(treeTag) || isRelationalOperatorTag(treeTag)){

            *offset = *offset + 1;

            ThreeAddressCodeNode *node;

            if(isLeaf(ast->ls) && isLeaf(ast->rs)){
                createTemporalNodeInfo(createTemporalID(*offset), ast->data, *offset);
                createTemporalNodeInfo(createTemporalID(*offset), ast->data, *offset);
                node = threeAddressCodeNodeFactory(ast->data->tag, ast->data, ast->ls->data, ast->rs->data);
            }else{    
                if(isLeaf(ast->ls) && !isLeaf(ast->rs)){
                    // printf("ENTRE A ESTE CASO %s\n\n", operatorToString(ast->data->operatorVar));
                    createThreeAddressCodeList(ast->rs, list, offset, labelCounter);
                    createTemporalNodeInfo(createTemporalID(*offset), ast->data, *offset);
                    node = threeAddressCodeNodeFactory(
                        ast->data->tag, ast->data, ast->ls->data, getFirst(getFromTAC(list, list->size)));
                }else if(!isLeaf(ast->ls) && isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->ls, list, offset, labelCounter);
                    createTemporalNodeInfo(createTemporalID(*offset), ast->data, *offset);
                    node = threeAddressCodeNodeFactory(
                        ast->data->tag, ast->data, getFirst(getFromTAC(list, list->size)), ast->rs->data);
                }else if(!isLeaf(ast->ls) && !isLeaf(ast->rs)){
                    createThreeAddressCodeList(ast->ls, list, offset, labelCounter);
                    createThreeAddressCodeList(ast->rs, list, offset, labelCounter);
                    createTemporalNodeInfo(createTemporalID(*offset), ast->data, *offset);
                    node = threeAddressCodeNodeFactory(ast->data->tag, ast->data, 
                                                getFirst(getFromTAC(list, list->size - 1)),
                                                getFirst(getFromTAC(list, list->size-0))
                                            );
                }
            }
            addToTAC(list, node);
    } else if (isReturnTag(treeTag)) {
        ThreeAddressCodeNode *node;
        if(isLeaf(ast->ls)){
            node = threeAddressCodeNodeFactory(treeTag, ast->ls->data, 
                                                    newEmptyNodeInfo(), newEmptyNodeInfo());
        }else{
            createThreeAddressCodeList(ast->ls, list, offset, labelCounter);
            node = threeAddressCodeNodeFactory(treeTag, getFromTAC(list, list->size)->first, 
                                                    newEmptyNodeInfo(), newEmptyNodeInfo());
        }
        addToTAC(list, node);
    
    } else if (isIf(treeTag)) {

        *labelCounter = *labelCounter + 1;
        NodeInfo* endThen = createLabelNodeInfo("endthen", *labelCounter);

        createThreeAddressCodeList(ast->ls, list, offset, labelCounter);
        // Probably, a new tag called JUMPBYFALSE would be better.
        ThreeAddressCodeNode *node = threeAddressCodeNodeFactory(JFALSE, getFromTAC(list, list->size)->first, endThen, newEmptyNodeInfo());
        addToTAC(list, node);
        createThreeAddressCodeList(ast->rs, list, offset, labelCounter);
        ThreeAddressCodeNode* endThenTAC = threeAddressCodeNodeFactory(endThen->tag, endThen, newEmptyNodeInfo(), newEmptyNodeInfo());
        addToTAC(list, endThenTAC);
        // Agregas el nodo del label pregenerado a la lista de TAC.

    
    } else if (isIfElse(treeTag)) {
        *labelCounter = *labelCounter + 1;
        NodeInfo* endThen = createLabelNodeInfo("endthen", *labelCounter);
        *labelCounter = *labelCounter + 1;
        NodeInfo* endElse = createLabelNodeInfo("endelse", *labelCounter);

        // write condition
        createThreeAddressCodeList(ast->ls, list, offset, labelCounter);

        // Probably, a new tag called JUMPBYFALSE would be better.
        NodeInfo* condition = getFromTAC(list, list->size)->first;
        ThreeAddressCodeNode *jumpCond = threeAddressCodeNodeFactory(JFALSE, condition, endThen, newEmptyNodeInfo());
        addToTAC(list, jumpCond);
        
        // THEN block
        createThreeAddressCodeList(ast->rs->ls, list, offset, labelCounter);
        
        ThreeAddressCodeNode *jumpThenBlock = threeAddressCodeNodeFactory(JUMP, endElse, newEmptyNodeInfo(), newEmptyNodeInfo());
        addToTAC(list, jumpThenBlock);

        ThreeAddressCodeNode *endThenTAC = threeAddressCodeNodeFactory(endThen->tag, endThen, newEmptyNodeInfo(), newEmptyNodeInfo());
        addToTAC(list, endThenTAC);

        // ELSE block
        createThreeAddressCodeList(ast->rs->rs, list, offset, labelCounter);
        ThreeAddressCodeNode *jumpElseBlock = threeAddressCodeNodeFactory(endElse->tag, endElse, newEmptyNodeInfo(), newEmptyNodeInfo());
        addToTAC(list, jumpElseBlock);
    
    } else if (isWhile(treeTag)) {
        *labelCounter = *labelCounter + 1;
        NodeInfo* beginWhile = createLabelNodeInfo("beginwhile", *labelCounter);
        *labelCounter = *labelCounter + 1;
        NodeInfo* endWhile = createLabelNodeInfo("endwhile", *labelCounter);

        // Write beginwhile label.
        ThreeAddressCodeNode *beginWhileTAC = threeAddressCodeNodeFactory(beginWhile->tag, beginWhile, newEmptyNodeInfo(), newEmptyNodeInfo());
        addToTAC(list, beginWhileTAC);

        // Reduce cond.
        createThreeAddressCodeList(ast->ls, list, offset, labelCounter);
        //Get cond generated
        NodeInfo* condition = getFromTAC(list, list->size)->first;
        

        // Jump by false to endWhile.
        ThreeAddressCodeNode *jumpCond = threeAddressCodeNodeFactory(JFALSE, condition, endWhile, newEmptyNodeInfo());
        addToTAC(list, jumpCond);

        // WHILE block.
        createThreeAddressCodeList(ast->rs, list, offset, labelCounter);
        
        // Jump by true to beginWhile.
        ThreeAddressCodeNode *iterationCond = threeAddressCodeNodeFactory(JUMP, beginWhile, newEmptyNodeInfo(), newEmptyNodeInfo());
        addToTAC(list, iterationCond);

        ThreeAddressCodeNode *endWhileTAC = threeAddressCodeNodeFactory(endWhile->tag, endWhile, newEmptyNodeInfo(), newEmptyNodeInfo());
        addToTAC(list, endWhileTAC);
    
    
    } else if(isMethodDeclTag(treeTag)){
        // Write beginwhile label.
        ThreeAddressCodeNode *beginFunction = threeAddressCodeNodeFactory(ast->data->tag, ast->data, newEmptyNodeInfo(), newEmptyNodeInfo());
        addToTAC(list, beginFunction);
        createThreeAddressCodeList(ast->rs, list, offset, labelCounter);
        ThreeAddressCodeNode *endFunction = threeAddressCodeNodeFactory(END_LABEL, ast->data, newEmptyNodeInfo(), newEmptyNodeInfo());
        addToTAC(list, endFunction);



        // generar un temporal por cada parametro, y asignarles los valores de cada registro de activación. (los cargados por el "load").
        
        // escribir el cuerpo del método.

        // escribir epílogo. 

    
    
    } else if(isMethodCallTag(treeTag)){
        createThreeAddressCodeList(ast->ls, list, offset, labelCounter);
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
            *offset = *offset + 1;
            NodeInfo *nd = ast->rs->data;
            NodeInfo *temp = newNodeInfoTemporal(ast->data->tag);
            createTemporalNodeInfo(createTemporalID(*offset), temp, *offset);
            node = threeAddressCodeNodeFactory(
                    ast->data->tag,
                    nd,
                    temp,
                    NULL
            );
            addToTAC(list, node);

    }else if (isUnaryOperatorTag(treeTag)) {
        
        
        ThreeAddressCodeNode *node;
        *offset = *offset + 1;
        createTemporalNodeInfo(createTemporalID(*offset), ast->data, *offset);
        
        if(isLeaf(ast->ls)){
            node = threeAddressCodeNodeFactory(treeTag, ast->data, ast->ls->data, newEmptyNodeInfo());
        }else{
            createThreeAddressCodeList(ast->ls, list, offset, labelCounter);
            node = threeAddressCodeNodeFactory(treeTag, ast->data, getFromTAC(list, list->size)->first, newEmptyNodeInfo());
        }
        addToTAC(list, node);
    }else if (treeTag == NONETAG) {
        return;
    }else{
        if(ast->ls!=NULL)createThreeAddressCodeList(ast->ls, list, offset, labelCounter);
        if(ast->rs!=NULL)createThreeAddressCodeList(ast->rs, list, offset, labelCounter);
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