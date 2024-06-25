#include "sha_1.h"
#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>

// Преобразование строки в массив байтов
std::vector<uint8_t> stringToBytes(const std::string& str) {
    std::vector<uint8_t> bytes(str.begin(), str.end());
    return bytes;
}

// Преобразование массива байтов в строку
std::string bytesToString(const std::vector<uint8_t>& bytes) {
    std::string str(bytes.begin(), bytes.end());
    return str;
}

// Дополнение сообщения для алгоритма SHA-1
std::vector<uint8_t> padMessage(const std::vector<uint8_t>& message) {
    // Реализация дополнения сообщения в соответствии с алгоритмом SHA-1
    // Здесь нужно добавить код для дополнения сообщения
    // ...
    return message;
}

// Вычисление хэш-значения SHA-1
std::vector<uint8_t> calculateSHA1(const std::vector<uint8_t>& input) {
    // Преобразование входных данных согласно алгоритму SHA-1
    std::vector<uint8_t> paddedMessage = padMessage(input);

    // Вычисление хэш-значения SHA-1
    // Здесь нужно добавить код для вычисления хэш-значения
    // ...

    // Возвращаем хэш-значение
    return paddedMessage;
}

std::string SHA1::calculatePasswordHash(const std::string& password) {
    // Преобразование пароля в массив байтов
    std::vector<uint8_t> bytes = stringToBytes(password);

    // Вычисление хэш-значения SHA-1 для пароля
    std::vector<uint8_t> hashBytes = calculateSHA1(bytes);

    // Преобразование хэш-значения в строку
    std::string hashString = bytesToString(hashBytes);

    return hashString;
}

uint32_t SHA1::rotateLeft(uint32_t value, size_t count) {
    return (value << count) | (value >> (32 - count));
}
