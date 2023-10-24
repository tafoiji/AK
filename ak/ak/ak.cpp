#include <iostream>
#include <chrono>
#include <fstream>

int* randPermutation(int n)
{
    int* permutation = new int[n];
    int* unused = new int[n - 1];
    for (int i = 0; i < n - 1; i++)
    {
        unused[i] = i + 1;
    }

    int curr = 0;
    int len = n - 1;
    srand(time(NULL));
    for (int i = 0; i < n - 1; i++)
    {
        int delItem = rand() % len;
        int next = unused[delItem];
        permutation[curr] = next;
        curr = next;
        unused[delItem] = unused[--len];
    }

    permutation[curr] = 0;

    delete[] unused;
    return permutation;
}

double checkTime(int n, int cnt)
{
    int* arr = randPermutation(n);
    int p = 0;
    auto start = std::chrono::high_resolution_clock::now();
    double itCnt = cnt;
    for (; cnt > 0; cnt--)
    {
        p = arr[p];
        //std::cout << p << ' ';
    }

    auto finish = std::chrono::high_resolution_clock::now();
    delete[] arr;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / itCnt;
}

int main()
{
    std::ofstream out("output.txt");
    for (int i = 500; i < 5000000; i *= 1.1)
    {
        out << i * 4 << ' ' << checkTime(i, 100000000) << '\n';
    }
}