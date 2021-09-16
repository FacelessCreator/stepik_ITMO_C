int is_positive_prime(int n) {
    if ((n == 1) || (n == 0))
        return 0;
    for (int i = 2; i < n; ++i) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int is_prime(int n) {
    if (n >= 0)
        return is_positive_prime(n);
    else
        return 0;
}