#include <iostream>
using namespace std;

uint64_t ExpBySq(uint64_t, uint64_t , const uint64_t &);

int main(int argc, char *argv[])
{
    uint64_t k = 0, N = 0, m = 0;

    if (argc != 4)
    {
        cerr << "[ERROR] Wrong input format!" << endl;
        return 0;
    }

    //cin >> k >> N >> m;
    k = strtoull(argv[1], 0, 10);
    N = strtoull(argv[2], 0, 10);
    m = strtoull(argv[3], 0, 10);
    cout << ExpBySq(k, N, m) << endl;

    return 0;
}

uint64_t ExpBySq(uint64_t base, uint64_t exponent, const uint64_t &mod)
{
    uint64_t r = 1;
    while(exponent > 0)
    {
        if (exponent & 1)
            r = (r * base) % mod;
        exponent >>= 1;
        base = (base * base) % mod;
    }
    return r;
}