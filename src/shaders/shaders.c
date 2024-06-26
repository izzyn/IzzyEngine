#include "../Collections/libraries.h"
#include "shaders.h"

int shaderStatus(unsigned int shader)
{
    int success = 0;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        int maxLength = 0;
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* errorLog = malloc(maxLength);
        glGetProgramInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        cwlog("Shader loader",LOGGER_ERROR, "%s", errorLog);
        glDeleteProgram(shader);
        free(errorLog);
        return -1;
    }
    return 0;
}
struct Shader* loadshader(const char* name){

    struct Shader* shader = malloc(sizeof(struct Shader));

    shader->ID = glCreateProgram();
    unsigned shaderIDs[3];
    int shader_count = 0;

    printf("\n--- LOADING IN SHADER %s ---\n", name);
    FILE *fptr = fopen(name, "r");
    fseek(fptr, 0L, SEEK_END);
    int size = ftell(fptr);
    rewind(fptr);
    char* file = malloc(sizeof(char) * size);
    fread(file, 1, size, fptr);
    cwlog(name, LOGGER_INFO, "Last char: %d", file[size-1]);
    int begin = 0;
    int shader_type=0;
    int new_shader_type=0;
    int load = false;
    int reading = false;
    cwlog(name, LOGGER_INFO, "Parsing shader file");
    for(int i = 0; i < size; i++){
        if(file[i] == '\n' && size - i > 8){
            char str[9];
            memcpy(str, file+i+1, 8);
            str[8] = '\0';
            if(!strcmp("--VERT--", str)){
                new_shader_type = GL_VERTEX_SHADER;
                cwlog(name, LOGGER_INFO, "Compiling vertex shader");
                load = true;
            }
            else if(!strcmp("--FRAG--", str)){
                new_shader_type = GL_FRAGMENT_SHADER;
                cwlog(name, LOGGER_INFO, "Compiling fragment shader");

                load = true;
            }
            else if(!strcmp("--GMTR--", str)){
                new_shader_type = GL_GEOMETRY_SHADER;
                cwlog(name, LOGGER_INFO, "Compiling geometry shader");

                load = true;
            }
        }
        if((load || i == size-1)){
            if(reading){
                cwlog(name, LOGGER_INFO, "Shader type: %x", shader_type);
                i+= i==size-1;
                cwlog(name, LOGGER_INFO, "Reading Subfile");
                char* subfile = malloc(i-begin+1);
                subfile[i-begin] = '\0';
                cwlog(name, LOGGER_INFO, "Copying into subfile");
                strncpy(subfile, file+begin,i-begin);
                cwlog(name, LOGGER_INFO, "Creating shader object");
                unsigned ID = glCreateShader(shader_type);

                cwlog(name, LOGGER_INFO, "Parsing shader source");
                glShaderSource(ID, 1, (const char**)&subfile, NULL);

                cwlog(name, LOGGER_INFO, "Compiling shader");
                glCompileShader(ID);

                cwlog(name, LOGGER_INFO, "Attatching shader");
                glAttachShader(shader->ID, ID);

                free(subfile);
                shaderIDs[shader_count] = ID;
                shader_count+=1;

            }
            shader_type = new_shader_type;
            i += 10;
            begin = i;
            reading = true;
            load = false;
            
        }
    }
    
    free((char*)file);

    glLinkProgram(shader->ID);
    cwlog(name, LOGGER_INFO, "Shader Status %d",shaderStatus(shader->ID));
    for(int i = 0; i < shader_count; i++){

        cwlog(name, LOGGER_SETUP, "Cleaning up shader compilation...");
        glDetachShader(shader->ID, shaderIDs[i]);
        glDeleteShader(shaderIDs[i]);
    }
    
    glGenVertexArrays(1, &shader->vao);
    glBindVertexArray(shader->vao);
    return shader;
}

void select_shader(struct Shader* shader){
    glUseProgram(shader->ID);
    glBindVertexArray(shader->vao);
}
