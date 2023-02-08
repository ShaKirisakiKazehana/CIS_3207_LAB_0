#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Location: Temple University Computer Science
 * Programmer: Dongjue Xie
 * Class: CIS_3207
 * Assignment: Lab 0
 * Date: Jan 31, 2022
 * Version: 1
 * Description: A simple implementation of the
 * Unix binary "ls"
 */
char *file_type(int);
void recursiveDir(const char *, int);

int main(int argc, char *argv[]) {
  DIR *folder;
  struct dirent *entry;
  char *path = argv[1];
  int items = 0;

  if (argv[1] != NULL)
    folder = opendir(path);
  else
    folder = opendir(".");
  if (folder == NULL) {
    perror("tuls");
    puts("ERROR: EXIT_FAILURE");
    return (1);
  }
  while (path == NULL && (entry = readdir(folder))) {
    items++;
    printf("item %2d  %5s: %s\n", items, file_type(entry->d_type),
           entry->d_name);
  }

  if (path != NULL) {
    printf("Loading %s\n", path);
    recursiveDir(path, 0);
  }

  closedir(folder);
  return EXIT_SUCCESS;
}

/*
 * A simple function that will return type information
 * as a string
 */
char *file_type(int d_type) {
  if (d_type == 4)
    return "DIR";
  return "FILE";
}

/*
 * A function that prints dir, and if it encounters
 * a directory it changes path into it.
 */
void recursiveDir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char pathBuf[1024];
            if (strcmp(entry->d_name, ".") == 0 || 
                strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(pathBuf, sizeof(pathBuf), "%s/%s", name, entry->d_name);
            printf("%*s DIR [%s]\n", indent, "", entry->d_name);
            recursiveDir(pathBuf, indent + 2);
        } else {
            printf("%*s FILE %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}