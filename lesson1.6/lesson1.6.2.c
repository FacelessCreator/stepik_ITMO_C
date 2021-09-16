int is_square(int a) {
    int i = 0;
    int square = i*i;
    while (square < a) {
        i ++;
        square = i*i;
    }
    return square == a ? 1 : 0;
}