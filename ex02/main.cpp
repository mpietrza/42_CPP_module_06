#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base *generate(void) {
	std::srand(static_cast<unsigned int>(std::time(0)));
	int r = std::rand() % 3;
	if (r == 0)
		return new A;
	else if (r == 1)
		return new B;
	else
		return new C;
}

void identify(Base *p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
}

void identify(Base &p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return ;
	} 
	catch(const std::exception &e) {}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return ;
	}
	catch(const std::exception &e) {}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return ;
	}
	catch(const std::exception &e) {}
}

int main() {
	std::srand(static_cast<unsigned int>(std::time(0))); // Seed once here
	int countA = 0, countB = 0, countC = 0;
	const int iterations = 100; // Number of iterations to generate objects
	std::cout << "Generating " << iterations << " objects..." << std::endl;
	std::cout << "Identifying objects..." << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Type identification results:" << std::endl;

	for (int i = 0; i < iterations; ++i) {
		Base* obj = generate();
		if (dynamic_cast<A*>(obj))
			countA++;
		else if (dynamic_cast<B*>(obj))
			countB++;
		else if (dynamic_cast<C*>(obj))
			countC++;

		identify(obj);
		identify(*obj);
		delete obj;
	}

	std::cout << "A: " << countA
			  << " | B: " << countB
			  << " | C: " << countC
			  << std::endl;
	return 0;
}