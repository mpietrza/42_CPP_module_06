#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
    Data data = {42, 3.14f, 'A'};
    Data* ptr = &data;

    uintptr_t raw = Serializer::serialize(ptr);
    Data* result = Serializer::deserialize(raw);

    std::cout << "Original pointer: " << ptr << std::endl;
    std::cout << "Deserialized pointer: " << result << std::endl;
    std::cout << "Equal: " << (ptr == result ? "yes" : "no") << std::endl;

    std::cout << "Data: " << result->id << ", " << result->value << ", " << result->letter << std::endl;
    return 0;
}