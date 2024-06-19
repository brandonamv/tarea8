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

static int generateRandomNumber(int N) {
    std::uniform_real_distribution<double> dis(0.0, 1.0); // Random number between 0 (inclusive) and 1 (exclusive)
    double randomNumber = dis(generator);
    int scaledNumber = static_cast<int>(randomNumber * N); // Scale to range (0, N)
    return scaledNumber;
}

static double getFin(std::chrono::steady_clock::time_point start_time) {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    double elapsed_ms = std::chrono::duration<double, std::micro>(elapsed_ns).count();
    return elapsed_ms;
}

int M[20][10][10]{};
int suma(int initX, int finX, int initY, int finY, int x) {
    int acum = 0;
    for (int i = initX; i <= finX; i++)
    {
        for (int j = initY; j <= finY; j++)
        {
            acum += M[x][i][j];
        }
    }
    return acum;
}

int main()
{
    int n = 10;
    
    for (int x = 0; x < 20; x++)
    {
        printf("%d:\n", x);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int num = generateRandomNumber(100);
                if (generateRandomNumber(20)>x)
                {
                    num *= -1;
                }
                M[x][i][j] = num;
                printf("%d\t|", num);
            }
            printf("\n");
        }
    }
    
    for (int i = 0; i < 20; i++)
    {
        int max = std::numeric_limits<int>::min();
        for (int xi = 0; xi < n; xi++)
        {
            for (int yi = 0; yi < n; yi++)
            {
                for (int xf = xi; xf < n; xf++)
                {
                    for (int yf = yi; yf < n; yf++)
                    {
                        int res = suma(xi, xf, yi, yf, i);
                        if (res > max)
                        {
                            max = res;
                        }
                    }
                }
            }
        }
        printf("%d:%d\n", i, max);
    }
    
    
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
