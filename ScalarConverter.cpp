#include "ScalarConverter.hpp"

//Constructors and destructors
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(ScalarConverter const &other) { (void)other; }

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

//Helper: check for char non-printable
static bool isCharNotImpossible(const std::string &str) {
	if (str.length() == 3 && str.front() == '\'' && str.back() == '\'' && str.at(1) > 0 && str.at(1) < 127)
		return true;
	return false;
}

//Helper: check for char literal
static bool isCharLiteral(const std::string &str) {
	if (isCharNotImpossible(str) && std::isprint(str.at(1)))
		return true;
	return false;
}

//Helper: check for pseudo-literals
static bool isPseudoLiteral(const std::string &str) {
	if (str == "nan" || str == "+inf" || str == "-inf" ||
		str == "nanf" || str == "+inff" || str == "+inff")
		return true;
	return false;
}

//Helper: print pseudo-literals
static void printPseudoLiteral(const std::string &str) {
	std::cout << "char:   impossible" << std::endl
			  << "int:    impossible" << std::endl;
	if (str == "nan" || str == "nanf") { 
		std::cout << "float:  nanf" << std::endl
				  << "double: nan" << std::endl;
	}
	else if (str == "+inf" || str == "+inff") {
		std::cout << "float:  +inff" << std::endl
				  << "double: +inf" << std::endl;
	}
	else if (str == "-inf" || str == "-inff") {
	    std::cout << "float:  -inff" << std::endl
				  << "double: -inf" << std::endl;
	}
}

//Helper: print imposible for all
static void printImpossible() {
	std::cout << "char:   impossible" << std::endl
			  << "int:    impossible" << std::endl
			  << "float:  impossible" << std::endl
			  << "double: impossible" << std::endl;
}

// Helper: print conversions for char
static void printCharConversions(char c) {
	std::cout << "char:   '" << c << std::endl
			  << "int:    " << static_cast<int>(c) << std::endl
			  << "float:  " << std::fixed << /*std::setprecision(1) << */static_cast<float>(c) << "f" << std::endl
			  << "double: " << std::fixed << /*std::setprecision(1) << */static_cast<double>(c) << std::endl;
}

// Helper: print conversions for numeric values
static void printNumericConversions(double d, bool isFloat, bool isLiteral, bool isNotImpossible) {
	//char
	if (isLiteral)
		std::cout << "char:   '" << static_cast<char>(d) << "'" << std::endl;
	else if (isNotImpossible)
		std::cout << "char:   Non displayable" << std::endl;
	else
		std::cout << "char:   impossible" << std::endl;
	
	//int
	if (d >= INT_MIN && d <= INT_MAX)
		std::cout << "int:    " << static_cast<int>(d) << std::endl;
	else
		std::cout << "int:    impossible" << std::endl;
	
	//float
	if (d >= -FLT_MAX && d <= FLT_MAX)
		std::cout << "float:  " << std::fixed << /*std::setprecision(1) << */static_cast<float>(d) << "f" << std::endl;
	else
		std::cout << "float:  impossible" << std::endl;

	//double
	std::cout << "double: " << std::fixed << /*std::setprecision(1) << */static_cast<float>(d) << std::endl;

}


