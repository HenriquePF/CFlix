#ifndef structFilme_h
#define structFilme_h

#include "TelaMain.h"
#include "CatalogoLista.h"
#include "CadastroFilme.h"
#include "EditarFilme.h"
#include "ExcluirFilme.h"
#include <time.h>

#define NOME 200

struct Array {
    int count;
    int reserved;
    struct Array *next;
    struct filme *p;
};

struct filme {
    char nomeFilme[NOME];
    time_t dataLancamento;
    int duracaoFilme;
};

void AddFilme(struct filme f);
void DeleteFilme(struct Array *f ,int index);

struct Array *GetFilmes(void);

#endif 
