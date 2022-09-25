#include <stdio.h>
#include <string.h>

enum Input
{
    BUF_SIZE = 100,
};

int
main(int argc, char **argv)
{
    char string[BUF_SIZE] = { 0 };
    char *res = fgets(string, sizeof(string), stdin);

    if (res == NULL) {
        return 0;
    }

    size_t len = strlen(string);
    if (string[len - 1] == '\n') {
        string[--len] = '\0';
    }

    printf("Hello, %s!\n", string);

    return 0;
}
