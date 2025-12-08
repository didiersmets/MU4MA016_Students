// question 2 Reading, writing (and visualizing) a mesh 读取写入和可视化网格 (3)
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


int mesh2D_to_gnuplot(Mesh2D* m, const char* filename) {
    FILE* fp;
    
    // 打开输出文件
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("错误: 无法创建文件 %s\n", filename);
        return -1;
    }
    
    printf("正在生成gnuplot文件: %s\n", filename);
    
    // 写入注释说明
    fprintf(fp, "# Gnuplot数据文件\n");
    fprintf(fp, "# 使用方法: gnuplot> plot '%s' with lines\n", filename);
    fprintf(fp, "# 网格信息: %d 个顶点, %d 个三角形\n", 
            m->nVertices, m->nTriangles);
    fprintf(fp, "#\n");
    
    // 对每个三角形，输出其三个顶点的坐标
    for (int i = 0; i < m->nTriangles; i++) {
        // 获取三角形的三个顶点索引
        // 注意: .mesh文件中索引从1开始，所以要减1
        int v1 = m->triangles[3*i] - 1;      // 第1个顶点
        int v2 = m->triangles[3*i+1] - 1;    // 第2个顶点
        int v3 = m->triangles[3*i+2] - 1;    // 第3个顶点
        
        // 检查索引是否有效
        if (v1 < 0 || v1 >= m->nVertices ||
            v2 < 0 || v2 >= m->nVertices ||
            v3 < 0 || v3 >= m->nVertices) {
            printf("警告: 三角形 %d 的顶点索引无效\n", i+1);
            continue;
        }
        
        // 输出第1个顶点的坐标
        fprintf(fp, "%lf %lf\n", 
                m->vertices[2*v1],      // x坐标
                m->vertices[2*v1+1]);   // y坐标
        
        // 输出第2个顶点的坐标
        fprintf(fp, "%lf %lf\n", 
                m->vertices[2*v2], 
                m->vertices[2*v2+1]);
        
        // 输出第3个顶点的坐标
        fprintf(fp, "%lf %lf\n", 
                m->vertices[2*v3], 
                m->vertices[2*v3+1]);
        
        // 再次输出第1个顶点，形成闭合的三角形
        fprintf(fp, "%lf %lf\n", 
                m->vertices[2*v1], 
                m->vertices[2*v1+1]);
        
        // 空行分隔不同的三角形
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    printf("Gnuplot文件生成完成!\n");
    printf("  可以使用以下命令可视化:\n");
    printf("  gnuplot> plot '%s' with lines\n", filename);
    
    return 0;
}