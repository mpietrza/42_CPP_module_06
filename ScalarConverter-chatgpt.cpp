#include "ScalarConverter.hpp"
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cfloat>
#include <stdexcept>

// Constructors and destructor
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(ScalarConverter const &other) { (void)other; }
ScalarConverter &ScalarConverter::operator=(ScalarConverter const &other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {}

// Helper: check for char literal
static bool isCharLiteral(const std::string &literal) {
    return literal.length() == 3 && literal.front() == '\'' && literal.back() == '\'';
}

// Helper: check for pseudo-literals
static bool isPseudoLiteral(const std::string &literal) {
    return literal == "nan" || literal == "+inf" || literal == "-inf" ||
           literal == "nanf" || literal == "+inff" || literal == "-inff";
}

// Helper: print pseudo-literals
static void printPseudoLiteral(const std::string &literal) {
    if (literal == "nan" || literal == "nanf") {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: nanf\n";
        std::cout << "double: nan\n";
    } else if (literal == "+inf" || literal == "+inff") {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: +inff\n";
        std::cout << "double: +inf\n";
    } else if (literal == "-inf" || literal == "-inff") {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: -inff\n";
        std::cout << "double: -inf\n";
    }
}

// Helper: print conversions for char
static void printCharConversions(char c) {
    std::cout << "char: '" << c << "'\n";
    std::cout << "int: " << static_cast<int>(c) << "\n";
    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(c) << "f\n";
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << "\n";
}

// Helper: print impossible for all
static void printImpossible() {
    std::cout << "char: impossible\n";
    std::cout << "int: impossible\n";
    std::cout << "float: impossible\n";
    std::cout << "double: impossible\n";
}

// Helper: print conversions for numeric values
static void printNumericConversions(double d, bool isFloat, bool isInt) {
    // Char
    if (isInt && d >= 0 && d <= 127 && std::isprint(static_cast<char>(d)))
        std::cout << "char: '" << static_cast<char>(d) << "'\n";
    else if (isInt && d >= 0 && d <= 127)
        std::cout << "char: Non displayable\n";
    else
        std::cout << "char: impossible\n";

    // Int
    if (d >= INT_MIN && d <= INT_MAX)
        std::cout << "int: " << static_cast<int>(d) << "\n";
    else
        std::cout << "int: impossible\n";

    // Float
    if (d >= -FLT_MAX && d <= FLT_MAX)
        std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(d) << "f\n";
    else
        std::cout << "float: impossible\n";

    // Double
    std::cout << "double: " << std::fixed << std::setprecision(1) << d << "\n";
}

void ScalarConverter::convert(const std::string &literal) {
    try {
        if (isCharLiteral(literal)) {
            printCharConversions(literal[1]);
            return;
        }
        if (isPseudoLiteral(literal)) {
            printPseudoLiteral(literal);
            return;
        }

        // Try int
        try {
            size_t idx;
            int i = std::stoi(literal, &idx);
            if (idx == literal.length()) {
                printNumericConversions(static_cast<double>(i), false, true);
                return;
            }
        } catch (...) {}

        // Try float
        try {
            size_t idx;
            float f = std::stof(literal, &idx);
            if (idx == literal.length() - 1 && literal.back() == 'f') {
                printNumericConversions(static_cast<double>(f), true, false);
                return;
            }
        } catch (...) {}

        // Try double
        try {
            size_t idx;
            double d = std::stod(literal, &idx);
            if (idx == literal.length()) {
                printNumericConversions(d, false, false);
                return;
            }
        } catch (...) {}

        printImpossible();
    } catch (...) {
        printImpossible();
    }
}


