
#include <iostream>
#include <cstdint>
#include <vector>
#include <type_traits>
#include <array>
#include <cstdlib>
#include <algorithm>
#include <optional>
#include <string>
#include <limits>
#include <cassert>

using namespace std;


/*
	***** Task 1 ***** 
	
	Man up at staircase 1,2 or 3 steps. 
	Сount all possible combinations 
	of passage on the stairs.
*/

class CounterOfAllPossiblePassageOnStairs
{
public:
    CounterOfAllPossiblePassageOnStairs(const uint16_t stairsAmount)
    : stairsAmount(stairsAmount)
    {}
    
    uint64_t getAllPossiblePassageOnStairs()
    {
        uint64_t res{0u};
        if(0 == stairsAmount)
        {
            return 0u;
        }
        else if(1 == stairsAmount)
        {
            return 1;
        }
        else
        {
            std::vector<uint16_t> mnemonicPassageOnStairs(stairsAmount + 1,0);
            return getAllPossiblePassageOnStairs(mnemonicPassageOnStairs, stairsAmount);
        }
    }
private:

    uint64_t getAllPossiblePassageOnStairs(std::vector<uint16_t>& mnemonicPassageOnStairs, const int32_t currentStair)
    {
        uint64_t res{0u};
        const bool isStairOutOfBoundary{0 > currentStair};
        
        if(isStairOutOfBoundary)
        {
            /* Do nothing */
        }
        else if(0 < mnemonicPassageOnStairs.at(currentStair))
        {
            res = mnemonicPassageOnStairs.at(currentStair);
        }
        else
        {
            res = countMnemonicForCertainStairs(mnemonicPassageOnStairs, currentStair);
        }
        return res;
    }
    
    uint64_t countMnemonicForCertainStairs(std::vector<uint16_t>& mnemonicPassageOnStairs, const int32_t currentStair)
    {
        uint64_t res{0u};
        if(0u == currentStair)
        {
            res = mnemonicPassageOnStairs.at(currentStair) = 1u;
        }
        else
        {
            res = mnemonicPassageOnStairs.at(currentStair) = getAllPossiblePassageOnStairs(mnemonicPassageOnStairs, currentStair - 1) +
                                                        getAllPossiblePassageOnStairs(mnemonicPassageOnStairs, currentStair - 2) +
                                                        getAllPossiblePassageOnStairs(mnemonicPassageOnStairs, currentStair - 3);
        }
        return res;
    }
    
    uint16_t stairsAmount;
};


/*
	***** Task 2 *****

	Robot locate in left top corner of grid with R row and C columns.
	How to get to right bottom corner if some place in grid don't exist 
*/

template<uint32_t ROWS, uint32_t COLUMNS>
class NavigatorForRobot
{
public:
    NavigatorForRobot()
    {
        static_assert((0 < ROWS) and (0 < COLUMNS), "amount rows or columns can't have 0");
        fillGridWithRandomObstacles();
        fillNavigationMapWithDefaultValues();
    }
    
    void printGrid()
    {
        for(const auto& row : grid)
        {
            printGridRow(row);
        }
    }
    
    void printNavigationMap()
    {
        for(const auto& row : navigationMap)
        {
            for(const auto& elem : row)
            {
                std::cout << "[" << elem << "] ";
            }
            std::cout << std::endl;
        }
    }
    
    void prepareNavigationMap()
    {
        const Coordinate rightBottomCornerCoordinate {ROWS - 1, COLUMNS - 1};
        // check if 0,0 has obstacle
        prepareNavigationMapFromCoordinate(rightBottomCornerCoordinate, true);
    }
    
private:
    struct Coordinate
    {
        int32_t row{};
        int32_t column{};
    };
    
    bool prepareNavigationMapFromCoordinate(const Coordinate currentCoordinate, const bool isRowBalance)
    {
        if(isCoordinateOutOfBoundery(currentCoordinate) or 
            hasCurrentCoordinateObstacle(currentCoordinate))
        {
            return false;
        }
        else if(existCoordinateInNavigationMap(currentCoordinate))
        {
            return true;
        }
        else if(isCurrentCoordinateLeftTopCorner(currentCoordinate))
        {
            setCoordinateToNavigationMap(currentCoordinate);
            return true;
        }
        else
        {
            return setCoordinateWithBalance(currentCoordinate, isRowBalance);
        }
        return false;
    }
    
    bool hasCurrentCoordinateObstacle(const Coordinate currentCoordinate) const
    {
        return false == grid.at(currentCoordinate.row).at(currentCoordinate.column);
    }
    
    bool existCoordinateInNavigationMap(const Coordinate currentCoordinate) const
    {
        return '@' == navigationMap.at(currentCoordinate.row).at(currentCoordinate.column);
    }
    
    bool isCoordinateOutOfBoundery(const Coordinate currentCoordinate) const
    {
        return (currentCoordinate.row < 0) or (currentCoordinate.column < 0);
    }
    
    bool isCurrentCoordinateLeftTopCorner(const Coordinate currentCoordinate) const
    {
        const Coordinate leftTopCornerCoordinate{0u, 0u};
        return (leftTopCornerCoordinate.row == currentCoordinate.row) and 
                (leftTopCornerCoordinate.column == currentCoordinate.column);
    }
    
    void setCoordinateToNavigationMap(const Coordinate currentCoordinate)
    {
        constexpr char navigationMarker{'@'};
        navigationMap.at(currentCoordinate.row).at(currentCoordinate.column) = navigationMarker;
    }
    
    bool setCoordinateWithBalance(const Coordinate currentCoordinate, const bool isRowBalance)
    {
        bool res{false};
        const bool nextBalance{isRowBalance ? false : true};
        const Coordinate rowShift{currentCoordinate.row - 1, currentCoordinate.column};
        const Coordinate columnShift{currentCoordinate.row, currentCoordinate.column - 1};
        
        if(prepareNavigationMapFromCoordinate(isRowBalance ? rowShift : columnShift, nextBalance) or
            prepareNavigationMapFromCoordinate(isRowBalance ? columnShift : rowShift, nextBalance))
        {
            setCoordinateToNavigationMap(currentCoordinate);
            res = true;
        }
        return res;
    }
    
    void printGridRow(const std::array<bool, COLUMNS>& row)
    {
        for(const auto& elem : row)
        {
            const auto elemToString{ elem ? "true" : "FALSE" };
            std::cout << "[" << elemToString << "] ";
        }
        std::cout << std::endl;
    }
    
    void fillGridWithRandomObstacles()
    {
        for(uint32_t i{0}; i < ROWS; ++i)
        {
            fillGridRowWithRandomObstacles(i);
        }
    }
    
    void fillGridRowWithRandomObstacles(const uint32_t currentRow)
    {
        const Coordinate obstacleCoordinate{3,3};
        
        for(uint32_t j{0}; j < COLUMNS; ++j)
        {
            const bool isObstacle{ (obstacleCoordinate.row == currentRow) and (obstacleCoordinate.column == j) };
            grid.at(currentRow).at(j) = isObstacle ? false : true;
        }
    }
    
    void fillNavigationMapWithDefaultValues()
    {
        for(auto& row : navigationMap)
        {
            for(auto& elem : row)
            {
                elem = '-';
            }
        }
    }
    
    std::array<std::array<bool, COLUMNS>, ROWS> grid{};
    std::array<std::array<char, COLUMNS>, ROWS> navigationMap{};
};

/*
	***** Task 3 *****
	
	There is Array with sorted don't repeted value. 
	To do: Find such array element which cover condition Array[i] == i
 
*/

template<uint32_t ARR_SIZE, bool UNIQUE_NUM>
class MagicElementInArray
{
public:
    MagicElementInArray()
    {
        if(ARR_SIZE > 0u)
        {
            fillArrayWithRandomValues();
        }
    }
    
    void printArray()
    {
        printf("\n");
        int i{0};
        for(const auto elem : arr)
        {
            printf("(%d)[%d] ", i, elem);
            ++i;
        }
    }
    
    std::optional<int32_t> getMagicNumber()
    {
        return findMagicNumberIfExist(0, ARR_SIZE - 1);
    }
    
private:
    
    std::optional<int32_t> findMagicNumberIfExist(const int32_t start, const int32_t end)
    {
        std::optional<int32_t> res;
        if(end < start)
        {
            res = std::nullopt;
        }
        else
        {
            const int32_t avarageIndex{(start + end) / 2};
            if(avarageIndex == arr.at(avarageIndex))
            {
                return avarageIndex;
            }
            
            const int32_t endForLeftPartArr{std::min(avarageIndex - 1, arr.at(avarageIndex))};
            res = findMagicNumberIfExist(start, endForLeftPartArr);
            if(std::nullopt == res)
            {
                const int32_t startForRightPartArr{std::max(avarageIndex + 1, arr.at(avarageIndex))};
                res = findMagicNumberIfExist(startForRightPartArr, end);
            }
        }
        return res;
    }

    void fillArrayWithRandomValues()
    {
        for(auto& elem : arr)
        {
            elem = getUniqueRandomValue();
        }
        
        // Set magic number
        if(UNIQUE_NUM)
        {
            const auto magicNumber{ (ARR_SIZE - 1) - (ARR_SIZE / 4) };
            arr.at(magicNumber) = magicNumber;
        }
        else
        {
            for(int i{7}; i < 13; ++i)
            {
                arr.at(i) = 7;
            }
        }
        //
        std::sort(arr.begin(), arr.end());
    }
    
    int32_t getUniqueRandomValue()
    {
        constexpr int16_t lowerNumberBoundary{ARR_SIZE};
        constexpr int16_t higerNumberBoundary{ARR_SIZE * 4};
        
        while(true)
        {
            const int32_t randomNum{(rand() % higerNumberBoundary) - lowerNumberBoundary};
            if(UNIQUE_NUM)
            {
                const auto it{std::find(arr.begin(), arr.end(), randomNum)};
                if(it == arr.end())
                {
                    return randomNum;
                }
            }
            else
            {
                return randomNum;
            }
        }
    }
    
    std::array<int32_t, ARR_SIZE> arr{};
};

/*
	***** Task 4 *****
	
	Find and print Fibonachi numbers
*/
template<uint64_t NUM_AMOUNT>
class GenerateFibonachiNumber
{
public:
    GenerateFibonachiNumber()
    {
        generateNumbers();
    }
    
    void printFibonachiNumbers()
    {
        for(const auto& elem : fibonachiNumbers)
        {
            printf("[%lu] ", elem);
        }
    }
    
private:

    void generateNumbers()
    {
        fibonachiNumbers.at(0) = 0;
        fibonachiNumbers.at(1) = 1;
        const uint8_t currentElem{2};
        generateNumbers(currentElem);
    }
    
    void generateNumbers(const uint64_t currentElem)
    {
        if(NUM_AMOUNT == currentElem)
        {
            return;
        }
        fibonachiNumbers.at(currentElem) = fibonachiNumbers.at(currentElem - 2) + fibonachiNumbers.at(currentElem - 1);
        generateNumbers(currentElem + 1);
    }
    
    std::array<uint64_t, NUM_AMOUNT> fibonachiNumbers{};
};

/*
	***** Task 5 *****
	
	Multiplicate two numbers without multiplication. 
	You may use addition/subtraction/ division.
	
*/
 
class MultiplicateTwoNumbers
{
public:
    MultiplicateTwoNumbers(const uint64_t firstNumber, const uint64_t secondNumber)
    : firstNumber(firstNumber), secondNumber(secondNumber)
    {}
    
    uint64_t getRes()
    {
        if((0u == firstNumber) or (0u == secondNumber))
        {
            return 0u;
        }
        
        const auto smaller{firstNumber < secondNumber ? firstNumber : secondNumber};
        const auto bigger{firstNumber > secondNumber ? firstNumber : secondNumber};
        
        std::vector<uint64_t> mnemo(smaller + 1, 0u);
        return getResAfterMultiplication(smaller, bigger, mnemo);
    }
private:

    uint64_t getResAfterMultiplication(const uint64_t smaller, const uint64_t bigger, std::vector<uint64_t> &mnemo)
    {
        if(0u == smaller)
        {
            mnemo.at(smaller) = 0;
            return mnemo.at(smaller);
        }
        
        if(1u == smaller)
        {
            mnemo.at(smaller) = bigger;
            return mnemo.at(smaller);
        }
        
        if(0u != mnemo.at(smaller))
        {
            return mnemo.at(smaller);
        }
        
        const auto dividedSmaller{smaller >> 1};
        const auto firstPart{getResAfterMultiplication(dividedSmaller, bigger, mnemo)};
        mnemo.at(dividedSmaller) = firstPart;
        auto secondPart{firstPart};
        uint64_t indexForSecondPart {dividedSmaller};
        
        if(1u == (smaller % 2))
        {
            indexForSecondPart = smaller - dividedSmaller;
            secondPart = getResAfterMultiplication(indexForSecondPart, bigger, mnemo);
            mnemo.at(indexForSecondPart) = secondPart;
        }
        
        return mnemo.at(dividedSmaller) + mnemo.at(indexForSecondPart);
    }
    
    uint64_t firstNumber{};
    uint64_t secondNumber{};
};

/*
	***** Task 6 *****
	
	As imput you have string with non duplicated symbols.
	You need generate all posible symbols combination
*/
class GetAllPossibleStringCombination
{
public:
    GetAllPossibleStringCombination(const std::string str)
    : str(str)
    {}
    
    std::vector<std::string> getAllPossibleStringCombination()
    {
        std::vector<std::string> res;
        if(not str.empty())
        {
            res = genetateAllPossibleStringCombination(str);
        }
        return res;
    }
private:
    std::vector<std::string> genetateAllPossibleStringCombination(std::string str)
    {
        std::vector<std::string> combinations;
        
        if(str.empty())
        {
            combinations.push_back(" ");
            return combinations;
        }
        
        const auto elem{str.back()};
        str.pop_back();
        auto previousCombinations{genetateAllPossibleStringCombination(str)};
        for(const auto& combination : previousCombinations)
        {
            for(size_t i{0u}; i < combination.length(); ++i)
            {
                auto newCombination{generateNewCombination(combination, elem, i)};
                combinations.push_back(newCombination);
            }
        }
        return combinations;
    }
    
    
    
    std::string generateNewCombination(const std::string& combination, const char elem, std::size_t i)
    {
        
        const auto firstPart{combination.substr(0u,i)};
        const auto secondPart{combination.substr(i)};
        return firstPart + elem + secondPart;
    }
    
    std::string str{};
};

/*
	***** Task 7 *****
	
	As input you have number of brackets pairs.
	Generate all possible brackets pairs combinations
*/

class BracketsPairsGenerator
{
public:
    BracketsPairsGenerator(const uint32_t bracketsAmount)
    : bracketsAmount(bracketsAmount)
    , leftBracketsCounter(bracketsAmount)
    {
        constexpr auto uint64MaxValue{std::numeric_limits<uint64_t>::max()};
        assert((bracketsAmount * 2) < uint64MaxValue);
    }
    
    std::vector<std::string> getBracketsCombination()
    {
        constexpr uint8_t startIndex{(bracketsAmount * 2) - 1};
        return generateBracketsCombinationWithIndex(startIndex);
    }
    
private:
    std::vector<std::string> generateBracketsCombinationWithIndex(const uint64_t index)
    {
        std::vector<std::string> combination{};
        if(0u == index)
        {
            combination.push_back("(");
            --leftBracketsCounter;
            return combination;
        }
        
        auto previousCombinations{generateBracketsCombinationWithIndex(--index)};
    }

    const uint32_t bracketsAmount;
    uint32_t leftBracketsCounter{};
};

int main()
{
    BracketsPairsGenerator bracketsPairsGenerator(3u);

    return 0;
}