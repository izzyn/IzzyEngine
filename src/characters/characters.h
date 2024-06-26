#ifndef CHARACTERS_H_INCLUDED
#define CHARACTERS_H_INCLUDED
#include "../Collections/base_rendering.h"
#include "../Events/events.h"
#include "../CWE/vec.h"
#include "../Physics/physics.h"

typedef void (*evptr)(struct Character*, struct Context*);

struct Character{
    evptr update_ev;
    struct Mesh* mesh;
    struct Shader* shader;
    struct Texture* texture;
    float position[3];
    float rotation[3];
}; 

void render_character(struct Character* character);
struct Character* load_character(struct Mesh* mesh, struct Texture* texture, struct Shader* shader);
void remove_character(struct Character*);

#endif
