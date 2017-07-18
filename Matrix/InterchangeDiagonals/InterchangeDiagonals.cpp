/*
 * Problem:
Program to Interchange Diagonals of Matrix
Given a square matrix of order n*n, you have to interchange the elements of both diagonals.

Examples:

Input : matrix[][] = {1, 2, 3,
                      4, 5, 6,
                      7, 8, 9}
Output : matrix[][] = {3, 2, 1,
                       4, 5, 6,
                       9, 8, 7}

Input : matrix[][] = {4,  2,  3,  1,
                      5,  7,  6,  8,
                      9, 11, 10, 12,
                     16, 14, 15, 13}
Output : matrix[][] = {1,  2,  3,  4,
                       5,  6,  7,  8,
                       9, 10, 11, 12,
                      11, 14, 15, 16}
 */



#include <array>
#include <algorithm>
#include <random>
#include <iostream>



template <typename T, std::size_t R, std::size_t C>
using Matrix = std::array<std::array<T, C>, R>;



template <typename T, std::size_t R, std::size_t C>
void InterchangeMatrix(Matrix<T, R, C>& aMatrix)
{
    std::size_t lRowIdx{ 0 };

    for (auto& lRow : aMatrix)
    {
        std::swap(lRow[lRowIdx], lRow[C - lRowIdx - 1]);
        ++lRowIdx;
    }
}



template <typename T, std::size_t R, std::size_t C>
void PrintMatrix(const Matrix<T, R, C>& aMatrix)
{
    for (std::size_t lRowIdx = 0; lRowIdx < R; ++lRowIdx)
    {
        for (std::size_t lColIdx = 0; lColIdx < C; ++lColIdx)
            std::cout << aMatrix[lRowIdx][lColIdx] << '\t';

        std::cout << '\n';
    }
}



int main(int /*argc*/, char* /*argv*/[])
{
    std::random_device lRndDev;
    std::mt19937 lRndEng(lRndDev());
    std::uniform_int_distribution<> lRndGen(1, 1000);

    Matrix<int, 11, 11> lMatrix;

    for (std::size_t lIdx = 0; lIdx < 11; ++lIdx)
        std::generate(&lMatrix[lIdx][0], &lMatrix[lIdx][0] + 11, [&lRndGen, &lRndEng] { return lRndGen(lRndEng); });

    PrintMatrix(lMatrix);

    std::cout << "\nAfter interchanging diagonals:\n";
    InterchangeMatrix(lMatrix);

    PrintMatrix(lMatrix);

    return EXIT_SUCCESS;
}