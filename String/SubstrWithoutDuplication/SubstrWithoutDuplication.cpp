/*
 * Longest Substring without Duplication
Problem: Given a string, please get the length of the longest substring which does not have duplicated characters.
Supposing all characters in the string are in the range from ‘a’ to ‘z’.

Analysis: It’s not difficult to get all substrings of a string, and to check whether a substring has duplicated characters.
The only concern about this brute-force strategy is performance. A string with n characters has O(n2) substrings,
and it costs O(n) time to check whether a substring has duplication. Therefore, the overall cost is O(n3).

We may improve the efficiency with dynamic programming. Let’s denote the length of longest substring ending with the ith character by L(i).

We scan the string one character after another. When the ith character is scanned, L(i-1) is already know. If the ith character has not appeared before,
L(i) should be L(i-1)+1. It’s more complex when the ith character is duplicated. Firstly we get the distance between the ith character and its previous occurrence.
If the distance is greater than L(i-1), the character is not in longest substring without duplication ending with the (i-1)th character,
so L(i) should also be L(i-1)+1. If the distance is less than L(i-1), L(i) is the distance, and it means between the two occurrence of the ith character
there are no other duplicated characters.
 */



#include <string>
#include <array>
#include <algorithm>
#include <iostream>
#include <cassert>



std::string FindLongestSubstrWithoutDuplication(const std::string& aStr)
{
    assert(!aStr.empty());

    constexpr std::size_t CHAR_COUNT = 256;
    std::array<int, CHAR_COUNT> lVisited;
    std::fill_n(lVisited.begin(), CHAR_COUNT, -1);

    auto lCurLen{ 0 }, lMaxLen{ 0 }, lFinalStart{ 0 };
    for (auto lIdx = 0; lIdx < aStr.length(); ++lIdx)
    {
        const auto lPreIdx = lVisited[aStr[lIdx]];

        if (lPreIdx == -1 || lIdx - lPreIdx > lCurLen)
        {
            ++lCurLen;
        }
        else
        {
            if (lCurLen > lMaxLen)
            {
                lMaxLen = lCurLen;
                lFinalStart = lIdx - lCurLen;
            }

            lCurLen = lIdx - lPreIdx;
        }

        lVisited[aStr[lIdx]] = lIdx;
    }

    return aStr.substr(lFinalStart, std::max(lMaxLen, lCurLen));
}



int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "The NRCS\n" 
        // << "  ====> " << FindLongestSubstrWithoutDuplication("") << '\n'
        << "abcdcba  ====> " << FindLongestSubstrWithoutDuplication("abcdcba") << '\n'
        << "AA  ====> " << FindLongestSubstrWithoutDuplication("AA") << '\n'
        << "AB  ====> " << FindLongestSubstrWithoutDuplication("AB") << '\n'
        << "abcacfrar  ====> " << FindLongestSubstrWithoutDuplication("abcacfrar") << '\n'
        << "acfrarabc  ====> " << FindLongestSubstrWithoutDuplication("acfrarabc") << '\n'
        << "aaabbbccc  ====> " << FindLongestSubstrWithoutDuplication("aaabbbccc") << '\n'
        << "abcdcba  ====> " << FindLongestSubstrWithoutDuplication("abcdcba") << '\n'
        << "ABDEFGABEF  ====> " << FindLongestSubstrWithoutDuplication("ABDEFGABEF") << '\n';

    return EXIT_SUCCESS;
}
