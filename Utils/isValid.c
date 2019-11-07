#include "isValid.h"
#include "telaMain.h"
#include "catalogoLista.h"
#include "cadastroFilme.h"
#include "editarFilme.h"
#include "excluirFilme.h"
#include <ctype.h>

int isValid(char option) {
    
    if(isdigit(option) == 0) {
        return 0;
    } else {
        return (int)option;
    }
}
