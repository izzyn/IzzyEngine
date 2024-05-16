#ifndef CWE_MATH_DEFINED
#define CWE_MATH_DEFINED
#include <math.h>

struct Vec3{
    float x;
    float y; 
    float z;
};

inline float dot(struct Vec3 v, struct Vec3 w){ return v.x*w.x+v.y*w.y+v.z*w.z;}
inline float magnitude(struct Vec3 v) {return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);}
inline struct Vec3 normal(struct Vec3 input, struct Vec3 v) {
    struct Vec3 normal;
    float mag = magnitude(v);
    normal.x = v.x/mag;
    normal.y = v.y/mag;
    normal.z = v.z/mag;
    return normal;

};
inline struct Vec3 scale(struct Vec3 v, float scalar){

    struct Vec3 out;
    out.x *= scalar;
    out.y *= scalar;
    out.z *= scalar;
    return out;
}
inline struct Vec3 add(struct Vec3 v, struct Vec3 w){
    struct Vec3 out;
    out.x = v.x+w.x;
    out.y = v.y+w.y;
    out.z = v.z+w.z;
    return out;
}
#endif
