// tarea8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <limits>

std::random_device rd;
std::mt19937 generator(rd());

#define TAM 20

std::vector < std::vector<int>> M;
int kadane(int* arr, int* start, int* finish, int n)
{
    // initialize sum, maxSum and
    int sum = 0, maxSum = INT_MIN, i;

    // Just some initial value to check
    // for all negative values case
    *finish = -1;

    // local variable
    int local_start = 0;

    for (i = 0; i < n; ++i) {
        sum += arr[i];
        if (sum < 0) {
            sum = 0;
            local_start = i + 1;
        }
        else if (sum > maxSum) {
            maxSum = sum;
            *start = local_start;
            *finish = i;
        }
    }

    // There is at-least one
    // non-negative number
    if (*finish != -1)
        return maxSum;

    // Special Case: When all numbers
    // in arr[] are negative
    maxSum = arr[0];
    *start = *finish = 0;

    // Find the maximum element in array
    for (i = 1; i < n; i++) {
        if (arr[i] > maxSum) {
            maxSum = arr[i];
            *start = *finish = i;
        }
    }
    return maxSum;
}

// The main function that finds
// maximum sum rectangle in M[][]
static void findMaxSum(int n)
{
    // Variables to store the final output
    int maxSum = INT_MIN, finalLeft, finalRight, finalTop,
        finalBottom;

    int left, right, i;
    int temp[TAM], sum, start, finish;

    // Set the left column
    for (left = 0; left < n; ++left) {
        // Initialize all elements of temp as 0
        memset(temp, 0, sizeof(temp));

        // Set the right column for the left
        // column set by outer loop
        for (right = left; right < n; ++right) {

            // Calculate sum between current left
            // and right for every row 'i'
            for (i = 0; i < n; ++i)
                temp[i] += M[i][right];

            // Find the maximum sum subarray in temp[].
            // The kadane() function also sets values
            // of start and finish. So 'sum' is sum of
            // rectangle between (start, left) and
            // (finish, right) which is the maximum sum
            // with boundary columns strictly as left
            // and right.
            sum = kadane(temp, &start, &finish, 10);

            // Compare sum with maximum sum so far.
            // If sum is more, then update maxSum and
            // other output values
            if (sum > maxSum) {
                maxSum = sum;
                finalLeft = left;
                finalRight = right;
                finalTop = start;
                finalBottom = finish;
            }
        }
    }


}


static int generateRandomNumber(int N) {
    std::uniform_real_distribution<double> dis(0.0, 1.0); // Random number between 0 (inclusive) and 1 (exclusive)
    double randomNumber = dis(generator);
    int scaledNumber = static_cast<int>(randomNumber * N); // Scale to range (0, N)
    return scaledNumber;
}

static double getFin(std::chrono::steady_clock::time_point start_time) {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    double elapsed_ms = std::chrono::duration<double, std::milli>(elapsed_ns).count();
    return elapsed_ms;
}


static int suma(int initX, int finX, int initY, int finY) {
    int acum = 0;
    for (int i = initX; i <= finX; i++)
    {
        for (int j = initY; j <= finY; j++)
        {
            acum += M[i][j];
        }
    }
    return acum;
}
static void bruteForceMax(int n) {
    int max = INT_MIN;
    for (int xi = 0; xi < n; xi++)
    {
        for (int yi = 0; yi < n; yi++)
        {
            for (int xf = 0; xf < n; xf++)
            {
                for (int yf = 0; yf < n; yf++)
                {
                    int res = suma(xi, xf, yi, yf);
                    if (res > max)
                    {
                        max = res;
                    }
                }
            }
        }
    }
}

int main()
{
    int n = TAM;
    std::vector<int> aux;
    aux.assign(n, 0);
    M.assign(n, aux);
    
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int x = 0; x < 20; x++)
    {
        double timeBF = 0;
        double timeK = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int num = generateRandomNumber(100);
                if (generateRandomNumber(20)>x)
                {
                    num *= -1;
                }
                M[i][j] = num;
            }
        }
        start_time = std::chrono::high_resolution_clock::now();
        findMaxSum(n);
        timeK = getFin(start_time);

        start_time = std::chrono::high_resolution_clock::now();
        bruteForceMax(n);
        timeBF = getFin(start_time);
        
        std::cout << x << ";" << timeBF << ";" << timeK << "\n";
    }
    /*double timeBF;
    double timeK;
    for (int i = 0; i < 20; i++)
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        int max = std::numeric_limits<int>::min();
        for (int xi = 0; xi < cols; xi++)
        {
            for (int yi = 0; yi < rows; yi++)
            {
                for (int xf = xi; xf < cols; xf++)
                {
                    for (int yf = yi; yf < rows; yf++)
                    {
                        int res = suma(xi, xf, yi, yf);
                        if (res > max)
                        {
                            max = res;
                        }
                    }
                }
            }
        }
        timeBF = getFin(start_time);
        start_time = std::chrono::high_resolution_clock::now();
        findMaxSum(i);
        timeK = getFin(start_time);
        printf("%d;%lf;%lf\n", i, timeBF, timeK);
    }*/
    
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
