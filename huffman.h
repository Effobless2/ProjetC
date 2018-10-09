#include <string.h>

#include "utils.h"
#include "liste_nd.h"

nd stringEncoding(char *);
char* recherchePrefixe(nd src, char val);
char* compression(nd src, char *str);
char* decompression(nd src, char *str);
nd compression_Fichier(char *);
char* searchPrefixe(nd src, char** prefixe);
char *decompression_Fichier(char *, nd);
char *HeaderRemoving(char *);