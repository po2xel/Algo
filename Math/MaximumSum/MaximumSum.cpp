/*
Find maximum possible stolen value from houses
There are n houses build in a line, each of which contains some value in it. A thief is going to steal the maximal value of these houses, but he can’t steal in two adjacent houses because owner of the stolen houses will tell his two neighbour left and right side. What is the maximum stolen value.
Examples:

Input  : hval[] = {6, 7, 1, 3, 8, 2, 4}
Output : 19
Thief will steal 6, 1, 8 and 4 from house.

Input  : hval[] = {5, 3, 4, 11, 2}
Output : 16
Thief will steal 5 and 11
 */


/*
 While reaching house i thief has two options, either he robs it or leave it. Let dp[i] represents the maximum value stolen so far on reaching house i. We can calculate the value of dp[i] as following –

dp[i] = max (hval[i] + dp[i-2], dp[i-1])

hval[i] + dp[i-2] is the case when thief
decided to rob house i. In that situation
maximum value will be the current value of
house + maximum value stolen till last
robbery at house not adjacent to house
i which will be house i-2.

dp[i-1] is the case when thief decided not
to rob house i. So he will check adjacent
house for maximum value stolen till now.
Thief will consider both options and decide whether to rob or not and maximum of both values will be the maximum stolen value till reaching house i.
 */

#include <array>
#include <algorithm>
#include <iterator>
#include <random>
#include <iostream>
#include <cassert>



// We can prepare dp in bottom up manner instead of recursively.
template <std::size_t N>
int FindMaxSum(std::array<int, N>& aValues)
{
    static_assert(N > 1);

    aValues[1] = std::max(aValues[0], aValues[1]);

    for (std::size_t lIdx = 2; lIdx < N; ++lIdx)
        aValues[lIdx] = std::max(aValues[lIdx] + aValues[lIdx - 2], aValues[lIdx - 1]);

    return aValues[N - 1];
}


template <>
int FindMaxSum(std::array<int, 1>& aValues)
{
    return aValues[0];
}


// We can optimize extra space, by using two variables to store value dp[i-1] and dp[i-2]. 
template <std::size_t N>
int FindMaxSum3(const std::array<int, N>& aValues)
{
    static_assert(N > 1);

    int lIncl = aValues[0];
    int lExcl = 0;

    for (std::size_t lIdx = 1; lIdx < N; ++lIdx)
    {
        const auto lMax = std::max(aValues[lIdx] + lExcl, lIncl);
        lExcl = lIncl;
        lIncl = lMax;
    }

    return std::max(lIncl, lExcl);
}


template <>
int FindMaxSum3(const std::array<int, 1>& aValues)
{
    return aValues[0];
}



template <std::size_t N>
std::size_t FindMaxSum2(std::array<int, N>& aValues, std::size_t aIdx, std::vector<std::size_t>& aSelectedIdx)
{
    static_assert(N > 1);

    const auto lIncl = aValues[aIdx] + aValues[aIdx - 2];
    const auto lExcl = aValues[aIdx - 1];

    const bool lSelected = lIncl > lExcl;

    aValues[aIdx] = lSelected ? lIncl : lExcl;

    if (aIdx + 1 < N)
    {
        const auto lSelctIdx = FindMaxSum2(aValues, aIdx + 1, aSelectedIdx);

        if (lSelctIdx == aIdx)
        {
            if (lSelected)
            {
                aSelectedIdx.push_back(aIdx);
                return aIdx - 2;
            }

            return aIdx - 1;
        }

        return lSelctIdx;
    }

    if (lSelected)
        aSelectedIdx.push_back(aIdx);

    return lSelected ? aIdx - 2 : aIdx - 1;
}


template <std::size_t N>
std::vector<std::size_t> FindMaxSum2(std::array<int, N> aValues)
{
    static_assert(N > 1);

    aValues[1] = std::max(aValues[0], aValues[1]);
    std::vector<std::size_t> lSelectedIdx;
    
    const auto lSelIdx = FindMaxSum2(aValues, 2, lSelectedIdx);

    if (lSelIdx == 0)
        lSelectedIdx.push_back(0);
    else
        lSelectedIdx.push_back(aValues[0] != aValues[1] ? 1 : 0);

    std::cout << "\nFindMaxSum2: " << aValues[N - 1] << '\n';

    return lSelectedIdx;
}


template <>
std::vector<std::size_t> FindMaxSum2(std::array<int, 1> /*aValues*/)
{
    return { 0 };
}



template <typename T, std::size_t N>
void PrintArray(const std::array<T, N>& aValues)
{
    static_assert(N > 0);

    std::copy(aValues.begin(), aValues.end(), std::ostream_iterator<T>(std::cout, " "));
}


int main(int /*argc*/, char* /*argv*/[])
{
    std::random_device lRndDev;
    std::mt19937 lRndEng(lRndDev());
    std::uniform_int_distribution<> lRndGen(1, 100);

    constexpr std::size_t N = 10;
    std::array<int, N> lValues;
    std::generate(lValues.begin(), lValues.end(), [&lRndGen, &lRndEng] { return lRndGen(lRndEng); });

    PrintArray(lValues);
    std::cout << "\nFindMaxSum3: " << FindMaxSum3(lValues) << '\n';

    const auto lSelelctIdx = FindMaxSum2(lValues);

    int lSum{};

    for (auto lIdx : lSelelctIdx)
    {
        std::cout << "a[" << lIdx << "] = " << lValues[lIdx] << '\n';
        lSum += lValues[lIdx];
    }

    std::cout << "\nSelected sum: " << lSum << '\n';

    assert(lSum == FindMaxSum3(lValues));

    std::cout << "\nFindMaxSum: " << FindMaxSum(lValues) << '\n';

    std::cout << "\nAfter:\n";
    PrintArray(lValues);

    return EXIT_SUCCESS;
}