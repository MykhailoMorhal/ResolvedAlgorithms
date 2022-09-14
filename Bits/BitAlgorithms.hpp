/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <map>
#include <cstddef>
#include <vector>
#include <utility>
#include <cstdint>
#include <type_traits>
#include<bits/stdc++.h>
#include <queue>
#include <algorithm>
#include <list>
#include <cmath>
#include <optional>
#include <limits>
#include <cmath>
#include <utility>

/*
 * Utils
 */
template<typename T>
std::string convertToBinary(T arg)
{
    std::string res;
    while(arg)
    {
        const bool addOne{arg % 2};
        arg /= 2;
        res.push_back( addOne ? '1' : '0' );
    }
    std::reverse(res.begin(), res.end());
    return res;
}

uint64_t findMaxBinarySequence(const std::string strBinary)
{
    uint64_t maxBinarySequence{0u};
    constexpr char zero{'0'};
    auto pos = std::find(strBinary.begin(), strBinary.end(), zero);
    if(pos != strBinary.end())
    {
        uint64_t startPosition{0u};
        uint64_t endPosition{0u};
        uint64_t firstBinarySequence{0u};
        uint64_t secondBinarySequence{0u};
        bool firstIni{true};

        for(uint64_t i{0}; i < strBinary.size(); ++i)
        {
            const bool isLastElem{(i + 1) == strBinary.size()};
            if((zero == strBinary[i]) or isLastElem)
            {
                endPosition = i;
                if(firstIni)
                {
                    firstBinarySequence = endPosition - startPosition;
                    firstIni = false;
                }
                else
                {
                    if(isLastElem)
                    {
                        endPosition = strBinary[i] == '1' ? endPosition + 1 : endPosition;
                    }
                    secondBinarySequence = endPosition - startPosition;
                    uint64_t binarySequence{firstBinarySequence + secondBinarySequence};
                    maxBinarySequence = binarySequence > maxBinarySequence ? binarySequence : maxBinarySequence;
                    firstBinarySequence = (secondBinarySequence - 1);
                }
                startPosition = endPosition;
            }
        }
    }
    else
    {
        std::cout << "Zero bit don't find" << std::endl;
        return 0u;
    }
    return maxBinarySequence;
}
/**********/

/* 	
	***** Task 1 *****

	Insert number M into N. M must be in
	interval from j to i.
*/
 uint32_t mergeTwoNumbers(const uint32_t N, const uint32_t M,
 const uint8_t i, const uint8_t j)
 {
    uint32_t emptyValue{0u};
    uint32_t firstMaskPart{emptyValue | ((1 << i) -1)};
    uint32_t secondMaskPart{emptyValue | ((1 << 1 + j) - 1)};
    uint32_t mask{firstMaskPart ^ secondMaskPart};
    uint32_t saveOverlapPart{N & firstMaskPart}; 
    uint32_t res{N & (~mask)};
    res = res | (M << i);
    return res | saveOverlapPart;
 }
 
 /* 
	***** Task 2 *****
	
	Given double number from 0 to 1. 
	You must print this number in binary representation.
	If number is bigger 32 bits, generate error
 */
std::bitset<32> convertToBinary(const double arg)
{
    double movedArg{arg};
    std::bitset<32> res{};
    constexpr double invalidValue{1.0};
    
    if((arg >= invalidValue) or (arg < 0.0))
    {
        std::cout << "Get incorrect double value" << std::endl;
        return res;
    }
    std::string str{std::to_string(arg)};
    auto iteartion{str.size() - 2};
    while(iteartion--)
    {
        movedArg = movedArg * 10;
    }
    
    const uint64_t resInUint = movedArg;
    std::cout << "resInUint: " << resInUint << std::endl;
    if(UINT32_MAX >= resInUint)
    {
        res = resInUint;
    }
    else
    {
        std::cout << "Binary representation of value is bigger as 32Bit" << std::endl;
    }
    return res;
}

/* 	
	***** Task 3 *****
	
	You have int value. In binary representation you can change only
	one bit from 0 to 1. You  must find the most sequence of 1 after
	you change.
	Exemple: 1775 (11010101111). Res = 8.
 */
uint64_t getMaxBinarySequence(uint64_t arg)
{
    const std::string argInBin{convertToBinary(arg)};
    std::cout << argInBin << std::endl;
    return findMaxBinarySequence(argInBin);
}

std::pair<unsigned int,unsigned int> 
calculateFirstBinaryIndexAndCounter(const std::string str, const char binArg)
{
    std::size_t firstIndex{str.size() - 1};
    std::size_t counter{1u};
    auto startCheck{false};
    
    while(firstIndex)
    {
        if(binArg == str[firstIndex])
        {
            if(not startCheck)
            {
                --firstIndex;
                continue;
            }
            else
            {
                break;
            }
        }
        
        startCheck = true;
        --firstIndex;
    }
    
    for(auto i{firstIndex + 1}; i < str.size(); ++i)
    {
        counter += (str[i] == binArg) ? 1u : 0u;
    }
    
    return std::make_pair(firstIndex, counter);
}

uint64_t getNearestMaxVal(uint64_t arg)
{
    const std::string str{convertToBinary(arg)};
    auto res {calculateFirstBinaryIndexAndCounter(str, '0')};
    auto firstZeroIndex{res.first};
    auto zeroCounter{res.second};
    if(not firstZeroIndex)
    {
        std::cout << "Number too big and can't be find bigger number" << std::endl;
        return 0u;
    }
    auto shift{(str.size() - 1) - firstZeroIndex};
    arg = (arg | (1 << shift)) & (0xffffffffffffffff << shift);
    if((shift - zeroCounter) > 0)
    {
        auto numberOfOne{shift - zeroCounter};
        arg |= ((1 << (numberOfOne)) - 1);
    }
    return arg;
}

uint64_t getNearestMinVal(uint64_t arg)
{
    const std::string str{convertToBinary(arg)};
    auto res {calculateFirstBinaryIndexAndCounter(str, '1')};
    auto firstOneIndex{res.first};
    auto oneCounter{res.second};
    if(not firstOneIndex)
    {
        std::cout << "Number too small and can't be find smaller number" << std::endl;
        return 0u;
    }
    
    auto mask{0xffffffffffffffff};
    auto shift{(str.size() - 1) - firstOneIndex};
    arg &= mask << (shift + 1);
    arg |= (shift == 1) ? 1 : (1 << shift) - 1;
    arg &= mask << (shift - oneCounter);
    
    return arg;
}

/* 
	***** Task 4 *****
	
	You have uint value. You must return nearest min and max
	representation of this value.
 */
std::pair<uint64_t, uint64_t> getMinMaxNearestRepresentation(const uint64_t arg)
{
    std::pair<uint64_t, uint64_t> res{};
    if(0u != arg)
    {
        const std::string argInBin{convertToBinary(arg)};
        res = std::make_pair(getNearestMaxVal(arg), getNearestMinVal(arg));
    }
    else
    {
        std::cout << "Given arg=0. Do nothing" << std::endl;
    }
    return res;
}

***** Task 4 *****

/* 
	***** Task 5 *****
	
	Given A and B values. Count how many bits must be change
	for transform value A to value B.
 */
 uint64_t amountBitsMustBeChangeForTransformFromOneValToAnothe(const uint64_t val1, const uint64_t val2)
 {
    const uint64_t mask{val1 ^ val2};
    auto strVal{convertToBinary(mask)};
    return std::count(strVal.begin(), strVal.end(), '1');
 }
 
 /* Exchange odd and pair bits in given value */
 uint64_t exchangeOddWithPairBits(const uint64_t val)
 {
    constexpr uint64_t maskShiftRight{0x5555555555555555};
    constexpr uint64_t maskShiftLeft{0xAAAAAAAAAAAAAAAA};
    return ((val >> 1) & maskShiftRight) | ((val << 1) & maskShiftLeft);
 }

int main()
{
    uint64_t arg{0xAA};
    
    return 0;
}
