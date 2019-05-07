#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    uint64_t k = 0, N = 0, m = 0, result = 1;

    if (argc != 4)
    {
        cerr << "[ERROR] Wrong input format!" << endl;
        return 0;
    }

    //cin >> k >> N >> m;
    k = strtoull(argv[1], 0, 10);
    N = strtoull(argv[2], 0, 10);
    m = strtoull(argv[3], 0, 10);

    while(N > 0)
    {
        if (N & 1) // exponent is odd
            result = (result * k) % m;
        N >>= 1;
        k = (k * k) % m;
    }

    cout << result << endl;
    return 0;
}