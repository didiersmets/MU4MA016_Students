// question 2 Reading, writing (and visualizing) a mesh 读取写入和可视化网格 (4)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int nVertices;
    int nTriangles;
    
    double *vertices;   // 顶点坐标数组 [x1,y1, x2,y2, ..., xn,yn]
    int *triangles;     // 三角形顶点索引数组 [v1,v2,v3, v1,v2,v3, ...]
} Mesh2D;

void initMesh2D(Mesh2D* m) {
    m->nVertices = 0;
    m->nTriangles = 0;
    m->vertices = NULL;
    m->triangles = NULL;
}

void freeMesh2D(Mesh2D* m) {
    if (m->vertices) {
        free(m->vertices);
    }
    if (m->triangles) {
        free(m->triangles);
    }
    initMesh2D(m);
}


int write_mesh2D(Mesh2D* m, const char* filename) {
    FILE* fp;
    
    // 打开输出文件
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("错误: 无法创建文件 %s\n", filename);
        return -1;
    }
    
    printf("正在写入文件: %s\n", filename);
    
    // 写入文件头
    fprintf(fp, "MeshVersionFormatted 1\n\n");
    fprintf(fp, "Dimension 2\n\n");
    
    // 写入顶点部分
    fprintf(fp, "Vertices\n");
    fprintf(fp, "%d\n", m->nVertices);
    
    for (int i = 0; i < m->nVertices; i++) {
        // 写入 x坐标 y坐标 参考标记(统一设为1)
        fprintf(fp, "%lf %lf 1\n", 
                m->vertices[2*i],      // x坐标
                m->vertices[2*i+1]);   // y坐标
    }
    fprintf(fp, "\n");
    
    // 写入三角形部分
    if (m->nTriangles > 0) {
        fprintf(fp, "Triangles\n");
        fprintf(fp, "%d\n", m->nTriangles);
        
        for (int i = 0; i < m->nTriangles; i++) {
            // 写入 顶点1 顶点2 顶点3 参考标记(统一设为1)
            fprintf(fp, "%d %d %d 1\n", 
                    m->triangles[3*i],      // 第1个顶点索引
                    m->triangles[3*i+1],    // 第2个顶点索引
                    m->triangles[3*i+2]);   // 第3个顶点索引
        }
        fprintf(fp, "\n");
    }
    
    // 写入文件尾
    fprintf(fp, "End\n");
    
    fclose(fp);
    printf("文件写入完成!\n");
    
    return 0;
}