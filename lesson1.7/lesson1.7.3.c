void factorize( int n, int* a, int* b )
{
    if (n == 1) {
        *a = 1;
        *b = n;
        return;
    }
    for (int c = 2; c <= n/2; ++c) {
        if (n % c == 0) {
            *a = c;
            *b = n / c;
            return;
        }
    }
    *a = 1;
    *b = n;
}