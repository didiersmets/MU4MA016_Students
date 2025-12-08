// indexed triangular meshes 索引化三角形 (5)
//用三角形的顶点坐标求面积，用叉积公式：顶点坐标为 (x1,y1), (x2,y2), (x3,y3)，则面积为0.5 * ((b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y))

double area_mesh2D(Mesh2D* m) {
    double total_area = 0.0;
    for (int i = 0; i < m->nt; i++) {
        Triangle t = m->tri[i];
        Vertex a = m->vert[t.v[0]];
        Vertex b = m->vert[t.v[1]];
        Vertex c = m->vert[t.v[2]];
        double area = 0.5 * ((b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y));
        total_area += area;
    }
    return total_area;
}
