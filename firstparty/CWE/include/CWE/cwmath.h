#ifndef CWE_MATH_DEFINED
#define CWE_MATH_DEFINED
#include <math.h>
#include <stdio.h>

struct Vec3{
    float x;
    float y; 
    float z;
};

struct Mat3{
    struct Vec3 xh;
    struct Vec3 yh;
    struct Vec3 zh;
};

static inline float dot(struct Vec3 v, struct Vec3 w){ return v.x*w.x+v.y*w.y+v.z*w.z;};

static inline float magnitude(struct Vec3 v) {return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);};

static inline struct Vec3 normal(struct Vec3 input, struct Vec3 v) {
    struct Vec3 normal;
    float mag = magnitude(v);
    normal.x = v.x/mag;
    normal.y = v.y/mag;
    normal.z = v.z/mag;
    return normal;

};

static inline struct Vec3 scale(struct Vec3 v, float scalar){

    struct Vec3 out;
    out.x = v.x * scalar;
    out.y = v.y * scalar;
    out.z = v.z * scalar;
    return out;
};

static inline struct Vec3 add(struct Vec3 v, struct Vec3 w){
    struct Vec3 out;
    printf("Testingtesting\n");
    out.x = v.x+w.x;
    out.y = v.y+w.y;
    out.z = v.z+w.z;
    return out;
};

struct Mat3 MMult(struct Mat3 X, struct Mat3 Y);

struct Vec3 MVult(struct Mat3 X, struct Vec3 v); 

#endif
