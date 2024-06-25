#ifndef SHA_1_H
#define SHA_1_H
#include <string> // Для использования std::string
#include <cstdint> // Для использования типа данных uint32_t
#include <cstddef> // Для использования типа данных size_t

class SHA1 {
public:
    std::string calculate(const std::string& input);
    std::string calculatePasswordHash(const std::string& password);

private:
    uint32_t rotateLeft(uint32_t value, size_t count);
};

#endif // SHA_1_H
