
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstddef>
#include <vector>
#include <utility>

/*
	***** Task 1 *****
	
	Implement an algorithm that determines whether all 
	characters in a string occur only once. 
	Using of additional data structures is forbidden.
*/
bool isUniqueString(const std::string str)
{
    constexpr int MAX_SIZE_ALPHABET{128};
    bool res {true};
    bool boolAlphabet[MAX_SIZE_ALPHABET]{};
    
    if(MAX_SIZE_ALPHABET < str.size ())
    {
        res = false;
    }
    
    for(int i = 0;i < str.size() and res; ++i)
    {
        int asciiSymbol = str[i];
        
        if(boolAlphabet[asciiSymbol])
        {
            res = false;
        }
        else
        {
            boolAlphabet[asciiSymbol] = true;
        }
    }
    
    return res;
}

/*
	***** Task 2 *****

	For two strings, write a method to determine 
	if one string is a permutation of the other.
*/
bool isSimilar(const std::string str1, const std::string str2)
{
    std::map<char,int> str1Map{};
    bool res{true};
    
    if(str1.size() == str2.size())
    {
        for(int i = 0; i < str1.size(); ++i)
        {
            str1Map[str1[i]]++;
        }
        
        for(int i = 0; i < str2.size(); ++i )
        {
            if( 0 == str1Map[str2[i]] )
            {
                res = false;
                break;
            }
			str1Map[str2[i]]--;
        }
    }
    else
    {
        res = false;
    }
    return res;
}

/*
	***** Task 3 *****

	Write a method to replace all spaces in a string with '%20' characters
*/
std::string replaceSpace(const std::string str)
{
    std::string res {str};
    const std::string NEW_SUB_STR {"%20"};
    const char SPACE {' '};
    
    /* Check if string end is space. If yes delete it */
    while(SPACE == res[res.size() - 1])
    {
        res.pop_back();
    }
    
    /* Insert sub string */
    for(std::size_t i = 0; i < res.size(); ++i )
    {
        if(SPACE == res[i])
        {
            res.replace(i, 1, NEW_SUB_STR);
            i =+ 2;
        }
    }
    return res;
}

/*
	***** Task 4 *****
	
	Write a function that checks if a given string is a permutation of a palindrome.
	A palindrome is not limited to dictionary words.
*/
bool isPolindrom(const std::string str)
{
    bool res{true};
    
    for(std::size_t startIndex = 0, endIndex = (str.size() - 1) ; startIndex < str.size() / 2; ++startIndex, --endIndex)
    {
        if( str[startIndex] != str[endIndex] )
        {
            res = false;
            break;
        }
    }
    return res;
}

/*
	***** Task 5 *****
	
	There are three types of modifying operations on strings: 
	insertion, character, deleting a character, and replacing 
	a character. Write a function that checks if two strings 
	are one modification apart (or zero modifications).
	
	Example: 
	pale, ple -> true 
	pales, pale -> true 
	pale, bale -> true 
	pale, bake -> false
*/

bool hasModifyAction(const std::string str1, const std::string str2)
{
    constexpr uint8_t ISSUE_COUNT {2};
    uint8_t issue{0};
    bool res{true};
    std::map<char,std::size_t> mapStr1;
    
    for(std::size_t i = 0; i < str1.size(); ++i)
    {
        mapStr1[str1[i]]++;
    }
    
    for(std::size_t i = 0; i < str2.size(); ++i)
    {
        if( mapStr1[str2[i]] )
        {
            mapStr1[str2[i]]--;
        }
        else
        {
            ++issue;   
        }
        
        if( ISSUE_COUNT == issue )
        {
            res = false;
            break;
        }
    }
    return res;
}

/*
	***** Task 6 *****
	
	Implement a method to perform basic string compression 
	using a repeated character count. For example,
	the string aabccsssaaa becomes a2Yc5a3. If the "compressed" 
	string does not become shorter than the original string,
	then the method returns the original string. The string is 
	supposed to be only from upper and lower case letters (a-z)
*/
std::string suppressString(const std::string str)
{
    std::map<char,int> mapStr;
    std::string res;
    
    for(size_t i = 0; i < str.size(); ++i)
    {
        mapStr[str[i]]++;
    }
    
    for(const auto& [key, value] : mapStr)
    {
        if(value == 1)
        {
            res += key + "1";
        }
        else
        {
            const std::string howManySymbolAppear {std::to_string(value)};
            res += key + howManySymbolAppear;
        }
		
		if( res.size() > str.size())
		{
			return str;
		}
    }
    
    return res;
}

template<typename T>
void printMtx(std::vector<std::vector<T>>& vct2D )
{
    for(const auto& vct : vct2D )
    {
        for(const auto elem : vct)
        {
            std::cout << elem;
        }
        std::cout << "" << std::endl;
    }
}

/*
	***** Task 7 *****
	
	There is an image represented by an NxN matrix;
	Write a method to rotate an image 90 degrees.
	Will you be able to perform this operation "on the spot"?
*/
void rotateMatrixMemorySave(std::vector<std::vector<char>>& vct2D )
{
    size_t sizeVctForRotate = vct2D.size();
    size_t lastElem = vct2D.size() - 1;
    
    for(size_t level = 0; level < (vct2D.size() / 2); ++level, sizeVctForRotate -= 2, --lastElem)
    {
        for(size_t elem = 0; elem < (sizeVctForRotate - 1); ++elem)
        {
            if( (1 == sizeVctForRotate) or ( (2 == sizeVctForRotate) and (1 == elem) ) )
            {
                return;
            }
            
            // save top
            const char top = vct2D[level][elem + level];
            
            // move left => to top
            vct2D[level][elem + level] = vct2D[lastElem - elem][level];
            
            // move bottom => to left
            vct2D[lastElem - elem][level] = vct2D[lastElem][lastElem - elem];
            
            // move right => to bottom
            vct2D[lastElem][lastElem - elem] = vct2D[level + elem][lastElem];
            
            // top => to right
            vct2D[level + elem][lastElem] = top;
        }
    }
}

/*
	***** Task 8 *****
	
	Write an algorithm that implements the following condition: 
	if an element of the matrix MxN is 0, then the entire column
	and the entire row are set to zero
*/

void zeroInMatrix(std::vector<std::vector<int>>& vct2D)
{
    std::map<size_t, bool> rowWhereLocateZero;
    std::map<size_t, bool> colWhereLocateZero;
    
    // find location where are 0
    for(size_t row = 0; row < vct2D.size(); ++row)
    {
        for(size_t col = 0; col < vct2D[0].size(); ++col)
        {
            if(0 == vct2D[row][col])
            {
                // save row
                if( false == rowWhereLocateZero[row] )
                {
                    rowWhereLocateZero[row] = true;
                }
                
                //save col
                if( false == colWhereLocateZero[col] )
                {
                    colWhereLocateZero[col] = true;
                }
            }
        }
    }
    
    // write 0 to row
    for(const auto& [key, value] : rowWhereLocateZero)
    {
        for(size_t i = 0; i < vct2D[key].size(); ++i)
        {
            vct2D[key][i] = 0;
        }
    }
    
    // write 0 to col
    for(const auto& [key, val] : colWhereLocateZero)
    {
        for(size_t i = 0; i < vct2D.size(); ++i)
        {
            vct2D[i][key] = 0;
        }
    }
}

/*
	***** Task 9 *****
	
	Suppose there is an isSubstring method that checks whether
	one word is a substring of another. Given two strings sl and s2, 
	write code that checks whether string s2 was obtained by rotating s1 using
	only one call to the isSubstring method.
	
	Example: the word waterbottle received
	cyclic shift erbottlewat).
*/

/* first solution */
bool isSubString(const std::string str1, const std::string str2)
{
    const auto str = str1 + str1;
    printf("Debug str=%s\n", str.c_str());
    return str.find(str2) != std::string::npos;
}

/* second solution */
bool isSubstring(const std::string str, const std::string str2)
{
    bool res {true};
    std::multimap<char, size_t> strMultiMap;
    
    if(str.size() != str2.size())
    {
        return false;
    }

    for(size_t i = 0; i < str2.size(); ++i)
    {
        strMultiMap.insert( std::pair<char, size_t>(str2[i], i) );
    }
    
    const size_t latestElemInStr{static_cast<size_t>(str.size()) - 1};
    size_t currentStrSymbol {0};
    size_t currentMapStrSymbol {0};
    size_t margineseBetweenTwoStrings{0};
    bool firstElem {true};
    bool goCurrentStrSymboToBegin{false};
    
    for(const auto elem : str)
    {
        const auto range = strMultiMap.equal_range(str[currentStrSymbol]);
        
        // check is exist elements in range
        if(range.first == range.second)
        {
            res = false;
            break;
        }
        else // check if has element certain position
        {
            bool findSymbolInCertainPositionInMap {false};
            for (auto i = range.first; i != range.second; ++i)
            {
                if(firstElem)
                {
                    margineseBetweenTwoStrings = i->second;
                    firstElem = false;
                }
                
                
                if(margineseBetweenTwoStrings >= i->second and goCurrentStrSymboToBegin)
                {
                    if( (i->second - margineseBetweenTwoStrings)  == currentStrSymbol)
                    {
                        findSymbolInCertainPositionInMap = true;
                        break;
                    }
                }
                else
                {
                    if(i->second == currentStrSymbol + margineseBetweenTwoStrings)
                    {
                        currentMapStrSymbol = i->second;
                        findSymbolInCertainPositionInMap = true;
                        break;
                    }
                }
            }
            
            if(not findSymbolInCertainPositionInMap)
            {
                res = false;
                break;
            }
            
            ++currentStrSymbol;
            
            if( currentMapStrSymbol == latestElemInStr and currentStrSymbol < latestElemInStr )
            {
                currentStrSymbol = 0;
                goCurrentStrSymboToBegin = true;
            }
        }
    }
    
    return res;
}

int main()
{
    std::string str {"waterbottle"};
    std::string str2 {"bottlewater"};
    std::cout<< isSubstring(str, str2) << std::endl;

    return 0;
}
