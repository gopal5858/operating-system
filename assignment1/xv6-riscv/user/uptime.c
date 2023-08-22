#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int i = uptime();
    printf("uptime : %d\n", i);
    exit(0);
}