// question 2 Reading, writing (and visualizing) a mesh 读取写入和可视化网格 (1-2)
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

int read_mesh2D(Mesh2D* m, const char* filename) {
    FILE* fp;
    char line[256];
    char keyword[64];
    int dimension;
    int ref;  // 用于读取参考标记但不存储
    
    initMesh2D(m);
    
    // 打开文件
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("错误: 无法打开文件 %s\n", filename);
        return -1;
    }
    
    printf("正在读取文件: %s\n", filename);
    
    // 读取文件内容
    while (fgets(line, sizeof(line), fp)) {
        // 跳过空行和注释行
        if (line[0] == '\n' || line[0] == '#') {
            continue;
        }
        
        // 读取关键字
        sscanf(line, "%s", keyword);
        
        // 检查文件格式版本
        if (strcmp(keyword, "MeshVersionFormatted") == 0) {
            int version;
            sscanf(line, "%*s %d", &version);
            printf("  网格格式版本: %d\n", version);
            continue;
        }
        
        // 检查维度
        if (strcmp(keyword, "Dimension") == 0) {
            sscanf(line, "%*s %d", &dimension);
            printf("  维度: %d\n", dimension);
            if (dimension != 2) {
                printf("错误: 这不是2D网格 (维度=%d)\n", dimension);
                fclose(fp);
                return -1;
            }
            continue;
        }
        
        // 读取顶点
        if (strcmp(keyword, "Vertices") == 0) {
            // 读取顶点数量
            fscanf(fp, "%d", &m->nVertices);
            printf("  读取 %d 个顶点...\n", m->nVertices);
            
            // 分配内存：每个顶点有2个坐标(x, y)
            m->vertices = (double*)malloc(2 * m->nVertices * sizeof(double));
            
            if (m->vertices == NULL) {
                printf("错误: 内存分配失败\n");
                fclose(fp);
                freeMesh2D(m);
                return -1;
            }
            
            // 读取每个顶点的坐标
            for (int i = 0; i < m->nVertices; i++) {
                // 读取 x坐标 y坐标，忽略参考标记
                fscanf(fp, "%lf %lf %d", 
                       &m->vertices[2*i],      // x坐标
                       &m->vertices[2*i+1],    // y坐标
                       &ref);                  // 参考标记(读取但不保存)
            }
            continue;
        }
        
        // 读取三角形
        if (strcmp(keyword, "Triangles") == 0) {
            // 读取三角形数量
            fscanf(fp, "%d", &m->nTriangles);
            printf("  读取 %d 个三角形...\n", m->nTriangles);
            
            // 分配内存：每个三角形有3个顶点索引
            m->triangles = (int*)malloc(3 * m->nTriangles * sizeof(int));
            
            if (m->triangles == NULL) {
                printf("错误: 内存分配失败\n");
                fclose(fp);
                freeMesh2D(m);
                return -1;
            }
            
            // 读取每个三角形的顶点索引
            for (int i = 0; i < m->nTriangles; i++) {
                // 读取三个顶点索引，忽略参考标记
                fscanf(fp, "%d %d %d %d", 
                       &m->triangles[3*i],      // 第1个顶点
                       &m->triangles[3*i+1],    // 第2个顶点
                       &m->triangles[3*i+2],    // 第3个顶点
                       &ref);                   // 参考标记(读取但不保存)
            }
            continue;
        }
        
        // 检测文件结束
        if (strcmp(keyword, "End") == 0) {
            break;
        }
        
        // 跳过其他不认识的关键字（如Edges等）
    }
    
    fclose(fp);
    printf("文件读取完成!\n");
    printf("  总计: %d 个顶点, %d 个三角形\n", m->nVertices, m->nTriangles);
    
    return 0;
}