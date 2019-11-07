#include "EditMovie.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "Filme.h"
#include "TrimFunc.h"
#include "ReadMovie.h"
#include "ClearScreen.h"
#include "ReadMovie.h"

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RESET       "\033[0m"              /* RESET */

void EditMovie(int index) {
    
    /* Variables */
    struct Array *filmeEdit = GetFilmes();
    
    struct filme *f = {0};
    
    /* Usar f */
    f = &(filmeEdit->p[index]);
    
    ReadMovieName(f->nomeFilme, f);
    ReadMovieDate(&f->dataLancamento, f);
    ReadMovieDuration(&f->duracaoFilme, f);
}
