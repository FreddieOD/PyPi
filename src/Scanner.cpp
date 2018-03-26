#include <Scanner.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <regex>

struct TOKEN {
	std::string type;
	std::string value;
};

std::ostream& operator << (std::ostream& o, const TOKEN& a){
	return o << a.type;
}

TOKEN getToken(std::vector<char> tokenBuffer){
	TOKEN token;
	// std::cout << tokenBuffer.size() << std::endl;
	std::string terminal = "";
	for(int i = 0; i < tokenBuffer.size(); i++){
		terminal += tokenBuffer[i];
	}
	// std::cout << terminal << std::endl;
	if (terminal == "float"){
		token.type = "floatDcl";
	}else if (terminal == "int"){
		token.type = "intDcl";
	}else if (terminal == "print"){
		token.type = "print";
	}else if (std::regex_match(terminal, std::regex("[a-z]+"))){
		token.type = "id";
		token.value = terminal;
	}else if (terminal == "="){
		token.type = "assign";
	}else if (terminal == "+"){
		token.type = "plus";
	}else if (terminal == "-"){
		token.type = "minus";
	}else if (std::regex_match(terminal, std::regex("[1-9][0-9]*"))){
		token.type = "intNum";
		token.value = terminal;
	}else if(std::regex_match(terminal, std::regex("[0-9]+[.][0-9]+"))){
		token.type = "floatNum";
		token.value = terminal;
	}
	return token;
};

void printVector(std::vector<TOKEN> tokens){
	std::vector<TOKEN>::iterator tokensIterator;
	for(tokensIterator = tokens.begin(); tokensIterator != tokens.end(); tokensIterator++){
		std::cout << *tokensIterator << std::endl;
	}
}

void scan(std::string source) {
	std::ifstream sourceIn(source.c_str());
	std::vector<TOKEN> tokens;
	std::vector<char> tokenBuffer;
	while(char nextChar = sourceIn.get()){
		std::cout << nextChar << std::endl;
		if(sourceIn.eof()){
			tokens.push_back(getToken(tokenBuffer));
			tokenBuffer.clear();
			break;
		}
		if((int)nextChar == 10 || (int)nextChar == 32){
			tokens.push_back(getToken(tokenBuffer));
			tokenBuffer.clear();
			continue;
		}
		tokenBuffer.push_back(nextChar);
	}
	printVector(tokens);
	return;
}

