#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <climits>
#include <cfloat>
#include <cerrno>


class ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter(ScalarConverter const &other);
		ScalarConverter &operator=(ScalarConverter const &other);
		~ScalarConverter();

	public:
		static void convert(const std::string &str); 
		//Being `static` means that `convert` can be called without creating an instance of `ScalarConverter`;
		//you can invoke it directly using the class name, like `ScalarConverter::convert("123")`.
};

#endif
