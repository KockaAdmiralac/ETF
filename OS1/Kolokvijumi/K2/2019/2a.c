#include <stdlib.h>

typedef struct {
    char* base; // Base address of the module
    size_t size; // Size of the module in sizeof(char)
    const char* name; // Name of the module's file
} ModDesc;

size_t mem_size = 100000;
int mem_extend(size_t);
int load(const char *, char *);

void load_module(ModDesc *mod) {
    if (mod->base != NULL) {
        return;
    }
    mem_extend(mod->size);
    char *new_base = NULL + mem_size;
    load(mod->name, new_base);
    mod->base = new_base;
    mem_size += mod->size;
}
