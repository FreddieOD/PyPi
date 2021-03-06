#ifndef _ASTNODE_H
#define _ASTNODE_H
#include <Scanner.h>

class AstNode{
    public:
        TOKEN token;
        std::vector<AstNode*> childNodes;
        AstNode* theParentNode = NULL;
    
    AstNode(const AstNode&);
    // ~AstNode();
    AstNode(TOKEN);
    AstNode();
    void setNextChild(AstNode*);
    void setTheParenNode(AstNode&);
    void accept(void (*processor)(AstNode));
};
#endif