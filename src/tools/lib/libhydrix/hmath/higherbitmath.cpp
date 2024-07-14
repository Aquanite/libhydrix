#include <libhydrix/hmath/higherbitmath.h>
#include <libhydrix/hmath/intmath.h>
uint128_t Math128::Add(uint128_t a, uint128_t b) {
    uint128_t result;
    result.low = a.low + b.low;
    result.high = a.high + b.high;
    if (result.low < a.low) {
        result.high++;
    }
    return result;
}

uint128_t Math128::Sub(uint128_t a, uint128_t b) {
    uint128_t result;
    result.low = a.low - b.low;
    result.high = a.high - b.high;
    if (result.low > a.low) {
        result.high--;
    }
    return result;
}

uint128_t Math128::Mul(uint128_t a, uint128_t b) {
    uint128_t result;
    result.low = a.low * b.low;
    result.high = a.high * b.high;
    return result;
}

uint128_t Math128::Div(uint128_t a, uint128_t b) {
    uint128_t result;
    result.low = a.low / b.low;
    result.high = a.high / b.high;
    return result;
}

uint128_t Math128::Mod(uint128_t a, uint128_t b) {
    uint128_t result;
    result.low = a.low % b.low;
    result.high = a.high % b.high;
    return result;
}

uint128_t Math128::And(uint128_t a, uint128_t b) {
    uint128_t result;
    result.low = a.low & b.low;
    result.high = a.high & b.high;
    return result;
}

uint128_t Math128::Or(uint128_t a, uint128_t b) {
    uint128_t result;
    result.low = a.low | b.low;
    result.high = a.high | b.high;
    return result;
}

uint128_t Math128::Xor(uint128_t a, uint128_t b) {
    uint128_t result;
    result.low = a.low ^ b.low;
    result.high = a.high ^ b.high;
    return result;
}

uint128_t Math128::Not(uint128_t a) {
    uint128_t result;
    result.low = ~a.low;
    result.high = ~a.high;
    return result;
}

uint128_t Math128::LShift(uint128_t a, uint64_t b) {
    uint128_t result;
    result.low = a.low << b;
    result.high = a.high << b;
    return result;
}

uint128_t Math128::RShift(uint128_t a, uint64_t b) {
    uint128_t result;
    result.low = a.low >> b;
    result.high = a.high >> b;
    return result;
}

uint128_t Math128::Neg(uint128_t a) {
    uint128_t result;
    result.low = -a.low;
    result.high = -a.high;
    return result;
}

uint128_t Math128::Absolute(uint128_t a) {
    uint128_t result;
    result.low = a.low;
    result.high = a.high;
    return result;
}

uint128_t Math128::Pow(uint128_t a, uint64_t b) {
    uint128_t result;
    result.low = a.low ^ b;
    result.high = a.high ^ b;
    return result;
}

uint128_t Math128::SquareRoot(uint128_t a) {
    uint128_t result;
    result.low = MathI::SquareRoot(a.low);
    result.high = MathI::SquareRoot(a.high);
    return result;
}

uint256_t Math256::Add(uint256_t a, uint256_t b) {
    uint256_t result;
    result.low = Math128::Add(a.low, b.low);
    result.high = Math128::Add(a.high, b.high);
    return result;
}

uint256_t Math256::Sub(uint256_t a, uint256_t b) {
    uint256_t result;
    result.low = Math128::Sub(a.low, b.low);
    result.high = Math128::Sub(a.high, b.high);
    return result;
}

uint256_t Math256::Mul(uint256_t a, uint256_t b) {
    uint256_t result;
    result.low = Math128::Mul(a.low, b.low);
    result.high = Math128::Mul(a.high, b.high);
    return result;
}

uint256_t Math256::Div(uint256_t a, uint256_t b) {
    uint256_t result;
    result.low = Math128::Div(a.low, b.low);
    result.high = Math128::Div(a.high, b.high);
    return result;
}

uint256_t Math256::Mod(uint256_t a, uint256_t b) {
    uint256_t result;
    result.low = Math128::Mod(a.low, b.low);
    result.high = Math128::Mod(a.high, b.high);
    return result;
}

uint256_t Math256::And(uint256_t a, uint256_t b) {
    uint256_t result;
    result.low = Math128::And(a.low, b.low);
    result.high = Math128::And(a.high, b.high);
    return result;
}

uint256_t Math256::Or(uint256_t a, uint256_t b) {
    uint256_t result;
    result.low = Math128::Or(a.low, b.low);
    result.high = Math128::Or(a.high, b.high);
    return result;
}

uint256_t Math256::Xor(uint256_t a, uint256_t b) {
    uint256_t result;
    result.low = Math128::Xor(a.low, b.low);
    result.high = Math128::Xor(a.high, b.high);
    return result;
}

uint256_t Math256::Not(uint256_t a) {
    uint256_t result;
    result.low = Math128::Not(a.low);
    result.high = Math128::Not(a.high);
    return result;
}

uint256_t Math256::LShift(uint256_t a, uint64_t b) {
    uint256_t result;
    result.low = Math128::LShift(a.low, b);
    result.high = Math128::LShift(a.high, b);
    return result;
}

uint256_t Math256::RShift(uint256_t a, uint64_t b) {
    uint256_t result;
    result.low = Math128::RShift(a.low, b);
    result.high = Math128::RShift(a.high, b);
    return result;
}

uint256_t Math256::Neg(uint256_t a) {
    uint256_t result;
    result.low = Math128::Neg(a.low);
    result.high = Math128::Neg(a.high);
    return result;
}

uint256_t Math256::Absolute(uint256_t a) {
    uint256_t result;
    result.low = Math128::Absolute(a.low);
    result.high = Math128::Absolute(a.high);
    return result;
}

uint256_t Math256::Pow(uint256_t a, uint64_t b) {
    uint256_t result;
    result.low = Math128::Pow(a.low, b);
    result.high = Math128::Pow(a.high, b);
    return result;
}

uint256_t Math256::SquareRoot(uint256_t a) {
    uint256_t result;
    result.low = Math128::SquareRoot(a.low);
    result.high = Math128::SquareRoot(a.high);
    return result;
}
// End of file