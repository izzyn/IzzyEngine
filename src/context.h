#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include "Events/events.h"
#include "Characters/characters.h"
#include "Collections/libraries.h"

typedef struct Character* CHARACTER;

declVec(CHARACTER);

struct Context
{
    struct CHARACTER_vec* character_vector;

};

#endif
