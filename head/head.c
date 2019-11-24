#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE* f, long nlines);

int main(int argc, char* argv[]) {
    int nlines;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s n [file fles...]\n", argv[0]);
        exit(1);
    }
    nlines = atol(argv[1]);
    if (argc == 2) {
        do_head(stdin, atol(argv[1]));
    } else {
        int i;
        for (i = 2; i < argc; i++) {
            FILE* f;
            f = fopen(argv[i], "r");
            if (!f) {
                perror(argv[i]);
                exit(1);
            }

            do_head(f, nlines);
            fclose(f);
        }
    }

    exit(0);
}

static void do_head(FILE* f, long nlines) {
    int c;
    if (nlines <= 0) return;
    while ((c = getc(f)) != EOF) {
        if (putchar(c) < 0) exit(0);
        if (c == '\n')  nlines--;
        if (nlines == 0) return;
    }
}