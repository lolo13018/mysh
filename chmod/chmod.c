#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

struct option longopts [] = {
    {"help", no_argument, 0, 'h'},
    {"verbose", no_argument, 0, 'v'},
    {"changes", no_argument, 0, 'c'},
    {0,0,0,0}
};

int main (int argc, char *argv[]) {

    int h = 0;
    int v = 0;
    int c = 0;
    int i = 0;


    while ((i = getopt_long(argc, argv, "hvc", longopts, NULL)) != -1){

        switch (i){

            case 'h':
                h = 1;
                break;

            case 'v':
                v = 1;
                break;

            case 'c':
                c = 1;
                break;

            case '?':
            if (isprint (optopt))
              fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
              fprintf (stderr,"Unknown option character! `\\x%x'.\n", optopt);

                return 1;

            default:
                return 1;
        }
    }
    if (argc < 3){
      fprintf(stderr, "chmod error\n");
      exit(EXIT_FAILURE);
    }

    if (h == 1) {
      printf("usage: chmod[OPTION]... MODE[MODE]...file ...\n" \
              "  ----- Options -----\n" \
              "  -v\tWarns what will be made and when action is done.\n" \
              "  -c\tTells what has been made once the action is completed.\n");
    }

    char *permission = argv[optind];
    char *buf = argv[optind+1];
    int x;

    if (strlen(permission) != 4 | (permission[0] - '0') != 0 | (permission[1] - '0') > 7
        | (permission[2] - '0') > 7 | (permission[3]  - '0' )> 7) {
          printf("%c\n", permission[3]);
      printf("input error \n");
      exit(EXIT_FAILURE);
    }

    if(buf == NULL){
      printf("no path entered \n");
    }

    if (v == 1){
      printf("the file %s will be given a %s authorization \n", argv[3], argv[2]);
    }

    x = strtol(permission, 0, 8);
    if(chmod (buf,x) < 0){
      fprintf(stderr, "chmod error\n");
      exit(EXIT_FAILURE);
    }

    if (v == 1){
      printf("operation completed \n");
    }

    if (c == 1){
      printf("the file %s has been given a %s authorization \n", argv[3], argv[2]);
    }
    return EXIT_SUCCESS;
}
