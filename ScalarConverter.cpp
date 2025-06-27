#include "ScalarConverter.hpp"

//Constructors and destructors
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(ScalarConverter const &other) { (void)other; }

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

//Helper: check for char literal
static bool isCharLiteral(const std::string &literal) {
	if (literal.lenght() == 3 && literal.front() == '\'' && literal.back() = '\'')
		return true;
	return false;
}

//Helper:check for pseudo-literals
static bool isPseudoLiteral(const std::string &literal) {
	if (literal == "nan" || literal == "+inf" || 
