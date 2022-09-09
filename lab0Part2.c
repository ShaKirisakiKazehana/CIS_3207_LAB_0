#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MODE 0755
#define BUF_SIZE 8192

int
main(int argc, char *argv[])
{
    int srcF, dstF, in, out;
    char buf[BUF_SIZE];

    if (argc != 3 || argv[1] == NULL) {
        printf("error: must provide a filename\n");
        exit(1);
    }
    srcF = open(argv[1], O_RDONLY); if (srcF < 0) exit(2);
    dstF = creat(argv[2], MODE); if (dstF < 0) exit(3);
    while (1) {
        in = read(srcF, buf, BUF_SIZE);
        if (in <= 0)
            break;
        out = write(dstF, buf, in);
        if (out <= 0)
            break;
    }
    printf("File copy done!\n");
    close(srcF);
    close(dstF); 

    return EXIT_SUCCESS;
}