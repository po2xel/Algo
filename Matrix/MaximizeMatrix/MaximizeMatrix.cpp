/*
 * Problem:
 Maximize matrix as per given condition
You are given a N*N matrix, where each element of matrix lies in the range 0 to M. You can apply the below operation on matrix any number of times:

Choose any two consecutive elements
Increment one of them by 1 and decrease other by 1
Note: The elements should remain within the range 0 to M after applying above operations.
The task is to find the maximum value of the expression shown below that can be obtained after performing the above operation on matrix if required:

res += (i+j)*A[i][j]

for 0 <= i, j < N
*/

/*
 * Algorithm :
Below is the step by step algorithm to do this:

First of all, calculate the sum of all elements of given matrix as SUM.
Start from last element that i.e. A(n, n) and move backward towards A(0,0) anti-diagonally as A(n, n), A(n, n-1), A(n-1, n), A(n, n-2), A(n-1, n-1), A(n-2, n)…..
Fill up each cell of matrix with M and update SUM = SUM- M for each element till SUM < M. Now, Fill the SUM value at next place in order if it is greater than zero
and all other remaining place as zero.
Finally you can calculate RESULT as per above mentioned formula.
 */



#include <array>
#include <iostream>
#include <numeric>
#include <random>



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


template <typename T, std::size_t N>
void PrintMatrixDiagonal(const Matrix<T, N, N>& /*aMatrix*/)
{
    constexpr auto M = static_cast<int>(N - 1);

    for (auto i = M; i >= 0; --i)
    {
        for (auto j = i; j <= M; ++j)
            std::cout << M + i - j << ',' << j << '\t';

        std::cout << '\n';
    }

    for (auto i = M; i >= 0; --i)
    {
        for (auto j = 0; j <= i; ++j)
            std::cout << i - j << ',' << j << '\t';

        std::cout << '\n';
    }
}



template <typename T, std::size_t N>
void MaximizeMatrix(Matrix<T, N, N>& aMatrix, T aLimit)
{
    T lSum{};

    for (const auto& lRow : aMatrix)
        lSum += std::accumulate(lRow.begin(), lRow.end(), 0);

    constexpr auto M = static_cast<int>(N - 1);

    // Diagonals below longest diagonal
    // starting from last element of the matrix
    for (auto i = M; i >= 0; --i)
    {
        for (auto j = i; j <= M; ++j)
        {
            if (lSum >= aLimit)
            {
                aMatrix[M + i - j][j] = aLimit;
                lSum -= aLimit;
            }
            else
            {
                aMatrix[M + i - j][j] = lSum;
                lSum = 0;
            }
        }
    }

    // Diagonals above longest diagonal
    for (auto i = M - 1; i >= 0; --i)
    {
        for (auto j = 0; j <= i; ++j)
        {
            if (lSum > aLimit)
            {
                aMatrix[i - j][j] = aLimit;
                lSum -= aLimit;
            }
            else
            {
                aMatrix[i - j][j] = lSum;
                lSum = 0;
            }
        }
    }
}



template <typename T, std::size_t N>
T Calculate(const Matrix<T, N, N>& aMatrix)
{
    T lRet{};

    for (std::size_t i = 0; i < N; ++i)
    {
        for (std::size_t j = 0; j < N; ++j)
            lRet += T((i + j) * aMatrix[i][j]);
    }

    return lRet;
}



int main(int /*argc*/, char* /*argv*/[])
{
    std::random_device lRndDev;
    std::mt19937 lRndEng(lRndDev());
    std::uniform_int_distribution<> lRndGen(1, 100);

    Matrix<int, 5, 5> lMatrix;
        /*{ {
            {3, 4},
            {5,4}
        } };*/

    for (auto& lRow : lMatrix)
        std::generate(lRow.begin(), lRow.end(), [&lRndGen, &lRndEng] { return lRndGen(lRndEng); });

    std::cout << "Before:\n";
    PrintMatrix(lMatrix);

    // PrintMatrixDiagonal(lMatrix);

    MaximizeMatrix(lMatrix, 100);

    std::cout << "\nAfter:\n";
    PrintMatrix(lMatrix);

    std::cout << "\nResult:\n" << Calculate(lMatrix) << '\n';

    return EXIT_SUCCESS;
}