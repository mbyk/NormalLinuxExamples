#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int do_wc(const char* path);
static void die(const char* s);
static int lineCount = 0;

int main(int argc, char* argv[]) {
    int i;
    if (argc < 2) {
        fprintf(stderr, "%s: file name not given\n", argv[0]);
        exit(1);
    }

    for (i = 1; i < argc; i++) {
        lineCount += do_wc(argv[i]);
    }
    printf("%d\n", lineCount);
    exit(0);
}

#define BUFFER_SIZE 2048

static int do_wc(const char* path) {
   FILE* fp;
   unsigned char buf[BUFFER_SIZE] ;
   int count = 0;

   if ((fp = fopen(path, "r")) == NULL) {
       die(path);
   }
   while (fgets(buf, sizeof buf, fp) != NULL) {
       count += 1;
   }

    fclose(fp);
    return count;
}

static void die(const char* s) {
    perror(s);
    exit(1);
}