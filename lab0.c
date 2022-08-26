#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
/*
 * Location: Temple University Computer Science
 * Programmer: Dongjue Xie
 * Class: CIS_3207
 * Assignment: Lab 0
 * Date: August 25, 2022
 * Version: 0
 * Description: A simple implementation of the
 * Unix binary "ls"
 */
int
main(int argc, char *argv[])
{
	DIR *folder;
	struct dirent *entry;

	char *path = argv[1];

	int files = 0;
	if (argv[1] != NULL)
        	folder = opendir(path);
    	else
        	folder = opendir(".");
    	if (folder == NULL)
    	{
        	perror("Unable to read directory");
        	return(1);
	}

    	while ( (entry = readdir(folder)) )
    	{
        	files++;
        	printf("File %2d: %s\n", files,
                entry->d_name);
    	}

	closedir(folder);
	return EXIT_SUCCESS;
}
