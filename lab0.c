#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
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
char* file_type(int);

int
main(int argc, char *argv[])
{
	DIR *folder;
	struct dirent *entry;
	char *path = argv[1];
	int items = 0;
    
	if (argv[1] != NULL)
        	folder = opendir(path);
    	else
        	folder = opendir(".");
    	if (folder == NULL)
    	{
        	perror("tuls");
            puts("ERROR: EXIT_FAILURE");
        	return(1);
	}
    if(path != NULL)
        printf("Loading %s\n", path);
    while ( (entry = readdir(folder)) )
    {
        items++;
        printf("item %2d  %5s: %s\n", items, 
		file_type(entry->d_type), entry->d_name);
    }

	closedir(folder);
	return EXIT_SUCCESS;
}

/*
 * A simple function that will return type information
 * as a string
 */
char*
file_type(int d_type)
{
	if(d_type == 4)
		return "DIR";
	return "FILE";
}