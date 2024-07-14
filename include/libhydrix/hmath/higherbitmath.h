#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct _uint128_t {
    uint64_t low;
    uint64_t high;
} uint128_t;
//int128_t
typedef struct _int128_t {
    int64_t low; // 8 bytes
    int64_t high; // 8 bytes
} int128_t; // 16 bytes
//uint256_t
typedef struct _uint256_t {
    uint128_t low;
    uint128_t high;
} uint256_t;
//int256_t
typedef struct _int256_t {
    int128_t low;
    int128_t high;
} int256_t;

// Bits: 128 Bytes: 16
typedef int128_t quad_t;
// Bits: 256 Bytes: 32
typedef uint128_t uquad_t;
// Bits: 256 Bytes: 32
typedef int256_t octa_t;
// Bits: 512 Bytes: 64
typedef uint256_t uocta_t;

/// @brief Math class for 128-bit integers
class Math128
{
    public:
        /// @brief Add two 128-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The sum
        static uint128_t Add(uint128_t a, uint128_t b);
        /// @brief Subtract two 128-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The difference
        static uint128_t Sub(uint128_t a, uint128_t b);
        /// @brief Multiply two 128-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The product
        static uint128_t Mul(uint128_t a, uint128_t b);
        /// @brief Divide two 128-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The quotient
        static uint128_t Div(uint128_t a, uint128_t b);
        /// @brief Modulus of two 128-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The modulus
        static uint128_t Mod(uint128_t a, uint128_t b);
        /// @brief Bitwise AND of two 128-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The result
        static uint128_t And(uint128_t a, uint128_t b);
        /// @brief Bitwise OR of two 128-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The result
        static uint128_t Or(uint128_t a, uint128_t b);
        /// @brief Bitwise XOR of two 128-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The result
        static uint128_t Xor(uint128_t a, uint128_t b);
        /// @brief Bitwise NOT of a 128-bit integer
        /// @param a The integer
        /// @return The result
        static uint128_t Not(uint128_t a);
        /// @brief Left shift a 128-bit integer
        /// @param a The integer
        /// @param b The shift amount
        /// @return The result
        static uint128_t LShift(uint128_t a, uint64_t b);
        /// @brief Right shift a 128-bit integer
        /// @param a The integer
        /// @param b The shift amount
        /// @return The result
        static uint128_t RShift(uint128_t a, uint64_t b);
        /// @brief Negate a 128-bit integer
        /// @param a The integer
        /// @return The result
        static uint128_t Neg(uint128_t a);
        /// @brief Absolute value of a 128-bit integer
        /// @param a The integer
        /// @return The result
        static uint128_t Absolute(uint128_t a);
        /// @brief Power of a 128-bit integer
        /// @param a The integer
        /// @param b The power
        /// @return The result
        static uint128_t Pow(uint128_t a, uint64_t b);
        /// @brief Square root of a 128-bit integer
        /// @param a The integer
        /// @return The result
        static uint128_t SquareRoot(uint128_t a);
};

/// @brief Math class for 256-bit integers
class Math256
{
    public:
        /// @brief Add two 256-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The sum
        static uint256_t Add(uint256_t a, uint256_t b);
        /// @brief Subtract two 256-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The difference
        static uint256_t Sub(uint256_t a, uint256_t b);
        /// @brief Multiply two 256-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The product
        static uint256_t Mul(uint256_t a, uint256_t b);
        /// @brief Divide two 256-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The quotient
        static uint256_t Div(uint256_t a, uint256_t b);
        /// @brief Modulus of two 256-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The modulus
        static uint256_t Mod(uint256_t a, uint256_t b);
        /// @brief Bitwise AND of two 256-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The result
        static uint256_t And(uint256_t a, uint256_t b);
        /// @brief Bitwise OR of two 256-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The result
        static uint256_t Or(uint256_t a, uint256_t b);
        /// @brief Bitwise XOR of two 256-bit integers
        /// @param a The first integer
        /// @param b The second integer
        /// @return The result
        static uint256_t Xor(uint256_t a, uint256_t b);
        /// @brief Bitwise NOT of a 256-bit integer
        /// @param a The integer
        /// @return The result
        static uint256_t Not(uint256_t a);
        /// @brief Left shift a 256-bit integer
        /// @param a The integer
        /// @param b The shift amount
        /// @return The result
        static uint256_t LShift(uint256_t a, uint64_t b);
        /// @brief Right shift a 256-bit integer
        /// @param a The integer
        /// @param b The shift amount
        /// @return The result
        static uint256_t RShift(uint256_t a, uint64_t b);
        /// @brief Negate a 256-bit integer
        /// @param a The integer
        /// @return The result
        static uint256_t Neg(uint256_t a);
        /// @brief Absolute value of a 256-bit integer
        /// @param a The integer
        /// @return The result
        static uint256_t Absolute(uint256_t a);
        /// @brief Power of a 256-bit integer
        /// @param a The integer
        /// @param b The power
        /// @return The result
        static uint256_t Pow(uint256_t a, uint64_t b);
        /// @brief Square root of a 256-bit integer
        /// @param a The integer
        /// @return The result
        static uint256_t SquareRoot(uint256_t a);
};

