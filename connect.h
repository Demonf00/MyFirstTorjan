#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> 
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <stdbool.h>
#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define CLIENTADDRESS "192.168.189.1"
#define SERVERPORT 200
#define CLIENTPORT 200
char *connected = "connected";
char *yes = "yes";
char *no = "no";