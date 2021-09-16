void normalize(int* a) {
   while ((*a % 2 == 0) && (*a > 0)) {
       *a = *a / 2;
   }
}
