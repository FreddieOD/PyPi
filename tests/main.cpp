#include <Parser.h>
#include <TestScanner.h>
#include <TestParser.h>
#include <TestAST.h>
#include <TestParseTree.h>
#include <TestSemantics.h>

int main(int argc, char** argv){
	scanner_suite();
	parser_suite();
	AST_suite();
	parse_tree_suite();
	semantics_suite();
}