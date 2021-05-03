#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int,char *[]);

char * _strdup(char *);

bool doCmd(char *);

void background(char *[]);

int getTokenNum(char *,char *[]);

void innerCmd(char *[]);

int compareString(char *,char *);
