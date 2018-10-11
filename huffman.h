#include <string.h>

#include "utils.h"
#include "liste_nd.h"

nd stringEncoding(char *);
char* recherchePrefixe(nd, char);
char* compression(nd, char *);
char* decompression(nd, char *);
nd compression_Fichier(char *, char *);
char* searchPrefixe(nd, char**);
char *decompression_Fichier(char *, nd, char *);
char *HeaderRemoving(char *);