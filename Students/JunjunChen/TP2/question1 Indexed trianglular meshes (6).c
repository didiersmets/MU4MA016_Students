// indexed triangular meshes 索引化三角形 (6)

#include <math.h>

//vertex 3D
typedef struct { 
    double x, y, z; 
} Vertex3D;

typedef struct {
    int v[3]; 
} Triangle;  // 与 2D 相同：存索引

typedef struct {
    int nv;        // 顶点数
    Vertex3D* vert;
    int nt;        // 三角形数
    Triangle* tri;
} Mesh3D;


static inline Vertex3D v_add(Vertex3D a, Vertex3D b){
    return (Vertex3D){
        a.x+b.x, a.y+b.y, a.z+b.z
    };
}
static inline Vertex3D v_sub(Vertex3D a, Vertex3D b){
    return (Vertex3D){
        a.x-b.x, a.y-b.y, a.z-b.z
    };
}
static inline Vertex3D v_scale(Vertex3D a, double s){
    return (Vertex3D){
        s*a.x, s*a.y, s*a.z
    };
}
static inline Vertex3D v_cross(Vertex3D a, Vertex3D b){
    return (Vertex3D){ a.y*b.z - a.z*b.y,
                       a.z*b.x - a.x*b.z,
                       a.x*b.y - a.y*b.x };
}
static inline double v_dot(Vertex3D a, Vertex3D b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

//体积 = (1/6) * sum_T  c_T · ((b-a)×(c-a))
double volume_mesh3D(const Mesh3D* m)
{
    double acc = 0.0;
    for (int i = 0; i < m->nt; ++i) {
        Triangle T = m->tri[i];
        Vertex3D a = m->vert[T.v[0]];
        Vertex3D b = m->vert[T.v[1]];
        Vertex3D c = m->vert[T.v[2]];

        Vertex3D cT = v_scale(v_add(v_add(a,b), c), 1.0/3.0);     // 重心barycentre
        Vertex3D n2 = v_cross(v_sub(b,a), v_sub(c,a));             // 2*法向面积向量
        acc += v_dot(cT, n2);
    }
    return acc / 6.0;  // volume >=0
}

