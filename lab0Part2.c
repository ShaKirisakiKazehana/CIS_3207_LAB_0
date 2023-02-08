#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
/*
 * Location: Temple University Computer Science
 * Programmer: Dongjue Xie
 * Class: CIS_3207
 * Assignment: Lab 0
 * Date: Feb 8, 2022
 * Version: 2
 * Description: A simple implementation of the
 * Unix binary "cp"
 */
#define MODE 0755
#define BUF_SIZE 8192

void copyFile(char* src, char* dst){
    int srcF, dstF, in, out;
    char buf[BUF_SIZE];
       srcF = open(src, O_RDONLY);
    if (srcF < 0)
        exit(2);
    dstF = creat(dst, MODE);
    if (dstF < 0)
        exit(3);
    while (1) {
        in = read(srcF, buf, BUF_SIZE);
        if (in <= 0)
            break;
        out = write(dstF, buf, in);
        if (out <= 0)
            break;
    }
    close(srcF);
    close(dstF);
}

int copyFiletoDir(char* infilename, char* outfileDir) {
    FILE* infile;
    FILE* outfile;
    char outfilename[102400];

    infile = fopen(infilename, "r"); // Open the input and output files.
    if (infile == NULL) {
      perror(infilename);
      return 1;
    }
    sprintf(outfilename, "%s/%s", outfileDir, basename(infilename));
    outfile = fopen(outfilename, "w");
    copyFile(infilename, outfilename);
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc < 2){
        printf("Usage:\n./tucp file1 file2\n");
        printf("./tucp file1 file2 file3 /anyDir\n");        
        exit(EXIT_SUCCESS);
    }
    if (argv[1] == NULL){
        perror("No arguments provided");
        exit(EXIT_FAILURE);
    }
    //printf("%s %s %d\n", argv[1], argv[2], argc);
    if (argc == 3)
        copyFile(argv[1], argv[2]);

    if (argc > 2){
        for(int i = 1; i < (argc-1); i++){
            //printf("argv = %s\n", argv[i]);
            //printf("argc = %d\n", argc);
            //printf("i = %d\n", i);
            //printf("argv at end = %s\n", argv[argc-1]);
            copyFiletoDir(argv[i], argv[argc-1]);
        }
    }

    printf("File copy done!\n");

    return EXIT_SUCCESS;
}