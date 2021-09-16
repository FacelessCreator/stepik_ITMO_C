void greet() {
   printf("Hello, ");
}

void b() {
   printf("Boris");
}

void v() {
   printf("Vladimir");
}

void print_newline() {
   printf("\n");
}

int main() {
    greet(); b(); print_newline();
    greet(); v(); print_newline();
    greet(); b();
}
