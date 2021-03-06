#include <Testpp.h>
#include <Scanner.h>
#include <TokenStream.h>
#include <Parser.h>
#include <Testpp.h>
#include <AstNode.h>
#include <AbstractSyntaxTree.h>
#include <SemanticAnalyser.h>
#include <utility>
#include <map>

bool testSimpleTypeCheck(){
    try{
        // Scanner
        std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/semantic_analyser/sourceTest1"));
        TokenStream* tokenStream = new TokenStream(tokens);

        // parser and AST construction
        AbstractSyntaxTree tree = initialiseAST(tokenStream);
        AbstractSyntaxTree* treePtr = &tree;
        
        // Semantic analysis - type checking and symbol table construction
        SemanticAnalyser semanticAnalyser;
        semanticAnalyser.typeChecking(treePtr);
        std::map<const std::string, std::string[2]>::iterator itA;
        std::map<const std::string, std::string[2]>::iterator itB;
        itA = SemanticAnalyser::symbolTable.find("numA");
        itB = SemanticAnalyser::symbolTable.find("numB");

        if(itA != SemanticAnalyser::symbolTable.end() &&
            itB != SemanticAnalyser::symbolTable.end()){
            if(std::get<1>(*itA)[0] == "float" && 
                std::get<1>(*itB)[0] == "int"){
                return true;
            }
        }
    }catch(std::runtime_error e){
        std::cerr <<  e.what() << std::endl;
    }
    return false;
}

bool testAssign(){
    try{
        // Scanner
        std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/semantic_analyser/sourceTest2"));
        TokenStream* tokenStream = new TokenStream(tokens);

        // parser and AST construction
        AbstractSyntaxTree tree = initialiseAST(tokenStream);
        AbstractSyntaxTree* treePtr = &tree;
        
        // Semantic analysis - type checking and symbol table construction
        SemanticAnalyser semanticAnalyser;
        semanticAnalyser.typeChecking(treePtr);
        std::map<const std::string, std::string[2]>::iterator itA;
        itA = SemanticAnalyser::symbolTable.find("numA");
        // std::cout << std::get<1>(*itA)[0] << std::endl;
        // std::cout << std::get<1>(*itA)[1] << std::endl;

        if(itA != SemanticAnalyser::symbolTable.end()){
            if(std::get<1>(*itA)[0] == "float"){
                return true;
            }
        }
    }catch(std::runtime_error e){
        std::cerr <<  e.what() << std::endl;
    }
    return false;
}

bool testSumAssign(){
    try{
        // Scanner
        std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/semantic_analyser/sourceTest3"));
        TokenStream* tokenStream = new TokenStream(tokens);

        // parser and AST construction
        AbstractSyntaxTree tree = initialiseAST(tokenStream);
        AbstractSyntaxTree* treePtr = &tree;
        
        // Semantic analysis - type checking and symbol table construction
        SemanticAnalyser semanticAnalyser1;
        semanticAnalyser1.typeChecking(treePtr);

        return true;
    }catch(std::runtime_error e){
        std::cerr <<  e.what() << std::endl;
    }
    return false;
}

bool testSumWithMismatchTypes_shouldThrowVariableMismatchException(){
    try{
        // Scanner
        std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/semantic_analyser/sourceTest4"));
        TokenStream* tokenStream = new TokenStream(tokens);

        // parser and AST construction
        AbstractSyntaxTree tree = initialiseAST(tokenStream);
        AbstractSyntaxTree* treePtr = &tree;
        
        // Semantic analysis - type checking and symbol table construction
        SemanticAnalyser semanticAnalyser;        
        semanticAnalyser.typeChecking(treePtr);

    }catch(std::runtime_error e){
        std::string errorMessage = "type mismatch for operator";
        if(errorMessage.compare(e.what()) == 0) return true;        
    }
    return false;
}

bool testAssignWithFalseTypes_shouldThrowAssignMismatchException(){
    try{
        // Scanner
        std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/semantic_analyser/sourceTest5"));
        TokenStream* tokenStream = new TokenStream(tokens);

        // parser and AST construction
        AbstractSyntaxTree tree = initialiseAST(tokenStream);
        AbstractSyntaxTree* treePtr = &tree;
        
        // Semantic analysis - type checking and symbol table construction
        SemanticAnalyser semanticAnalyser;        
        semanticAnalyser.typeChecking(treePtr);

    }catch(std::runtime_error e){
        std::string errorMessage = "type mismatch";
        if(errorMessage.compare(e.what()) == 0) return true;        
    }
    return false;
}

bool testSumMultipleAssign(){
    try{
        // Scanner
        std::vector<TOKEN> tokens = scan(std::string("./tests/test_sources/semantic_analyser/sourceTest6"));
        TokenStream* tokenStream = new TokenStream(tokens);

        // parser and AST construction
        AbstractSyntaxTree tree = initialiseAST(tokenStream);
        AbstractSyntaxTree* treePtr = &tree;
        
        // Semantic analysis - type checking and symbol table construction
        SemanticAnalyser semanticAnalyser1;
        semanticAnalyser1.typeChecking(treePtr);

        return true;
    }catch(std::runtime_error e){
        std::cerr <<  e.what() << std::endl;
    }
    return false;
}

void test_semantics(){
    VERIFY("SourceTest1 - test simple type check", testSimpleTypeCheck());
    VERIFY("SourceTest2 - test assign", testAssign());
    VERIFY("SourceTest3 - test sum assign", testSumAssign());
    VERIFY("SourceTest4 - invalid variable add throws exception", testSumWithMismatchTypes_shouldThrowVariableMismatchException());
    VERIFY("SourceTest5 - invalid variable assign throws exception", testAssignWithFalseTypes_shouldThrowAssignMismatchException());
    VERIFY("SourceTest6 - test sum multiple assign", testSumMultipleAssign());
}

// register suite
void semantics_suite(){
    TEST_SUITE("SEMANTIC SUITE", &test_semantics);
}