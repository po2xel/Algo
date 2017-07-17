/*\
* Problem:

Find median in row wise sorted matrix
We are given a row wise sorted matrix of size r*c, we need to find the median of the matrix given. It is assumed that r*c is always odd.

Examples:

Input : 1 3 5
        2 6 9
        3 6 9
Output : Median is 5

Input: 1 4 3
       2 5 6
       7 8 9
Output: Median is 5
 */

/*
 * Algorithm:
 
 An efficient approach for this problem is to use binary search algorithm.
 The idea is that for a number to be median there should be exactly (n/2) numbers which are less than this number.
 So, we try to find the count of numbers less than all the numbers. Below is the step by step algorithm for this approach:

    1. First we find the minimum and maximum elements in the matrix.
       Minimum element can be easily found by comparing the first element of each row, 
       and similarly the maximum element can be found by comparing the last element of each row.
    2. Then we use binary search on our range of numbers from minimum to maximum,
      we find the mid of the min and max, and get count of numbers less than our mid. And accordingly change the min or max.
    3. For a number to be median, there should be (r*c)/2 numbers smaller than that number.
       So for every number, we get the count of numbers less than that by using upper_bound() in each row of matrix,
       if it is less than the required count, the median must be greater than the selected number, else the median must be less than or equal to the selected number.
 */



#include <algorithm>
#include <array>
#include <iostream>



template <typename T, std::size_t R, std::size_t C>
using Matrix = std::array<std::array<T, C>, R>;



template <typename T, std::size_t R, std::size_t C>
void PrintMatrix(const Matrix<T, R, C>& aMatrix)
{
    for (auto& lRow : aMatrix)
    {
        for (auto& lElem : lRow)
            std::cout << lElem << '\t';

        std::cout << '\n';
    }
}



template <typename T, std::size_t R, std::size_t C>
T FindMatrixMedian(const Matrix<T, R, C>& aMatrix)
{
    T lMin{ INT_MAX }, lMax{ INT_MIN };

    // Find the min-max element in the matrix
    for (std::size_t lRowIdx = 0; lRowIdx < R; ++lRowIdx)
    {
        if (aMatrix[lRowIdx][0] < lMin)
            lMin = aMatrix[lRowIdx][0];

        if (aMatrix[lRowIdx][C - 1] > lMax)
            lMax = aMatrix[lRowIdx][C - 1];
    }

    constexpr auto lExpected = (R * C + 1) >> 1;

    while(lMin < lMax)
    {
        const auto lMid = (lMax + lMin) / 2;

        std::size_t lCount{ 0 };

        // Calculate the number of element <= lMid.
        for (std::size_t lRowIdx = 0; lRowIdx < R; ++lRowIdx)
            lCount += std::distance(&aMatrix[lRowIdx][0], std::upper_bound(&aMatrix[lRowIdx][0], &aMatrix[lRowIdx][0] + C, lMid));

        if (lCount < lExpected)
            lMin = lMid + 1;
        else
            lMax = lMid;
    }

    return lMin;
}



int main(int /*argc*/, char* /*argv*/[])
{
    constexpr Matrix<int, 3, 3> lMatrix1
    { {
        { 1, 2, 4 },
        { 2, 6, 9 },
        { 3, 6, 9 }
    } };

    PrintMatrix(lMatrix1);

    std::cout << "Matrix Median: " << FindMatrixMedian(lMatrix1) << "\n\n";

    constexpr Matrix<int, 3, 3> lMatrix2
    { {
        { 1, 4, 3 },
        { 2, 5, 6 },
        { 7, 8, 9 }
    } };

    PrintMatrix(lMatrix2);

    std::cout << "Matrix Median: " << FindMatrixMedian(lMatrix2) << "\n\n";


    constexpr Matrix<int, 3, 5> lMatrix3
    { {
        { 1, 3, 4, 8, 9 },
        { 2, 5, 18, 25, 50 },
        { 6, 7, 22, 45, 55 }
    } };

    PrintMatrix(lMatrix3);

    std::cout << "Matrix Median: " << FindMatrixMedian(lMatrix3) << "\n\n";

    return EXIT_SUCCESS;
}
