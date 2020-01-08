#ifndef structFilme_h
#define structFilme_h

#include "TelaMain.h"
#include "EntryCatalog.h"
#include "EntryRegister.h"
#include "EditEntry.h"
#include "ExcludeEntry.h"
#include <time.h>

#define NOME 200

struct Array {
    int count;
    int reserved;
    struct filme *p;
};

struct filme {
    int entryId;
    char nomeFilme[NOME]; // 200 bits
    time_t dataLancamento; // long 64 bits
    int duracaoFilme; // int 32
};

void AddFilme(struct filme f);
void DeleteFilme(struct Array *f ,int index);

struct Array *GetEntries(void);

#endif 
