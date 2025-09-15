#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief 根据命令行参数n生成x和y数据，并写入文件。
 * @param argc 命令行参数的数量。
 * @param argv 命令行参数的字符串数组。
 * @return 0 表示成功，1 表示失败。
 */
int main(int argc, char *argv[]) {
    // 检查命令行参数的数量。程序需要一个整数n作为参数。
    if (argc != 2) {
        fprintf(stderr, "用法: %s <正整数 n>\n", argv[0]);
        // 如果出错，返回失败状态。
        return EXIT_FAILURE;
    }

    // 将命令行参数字符串转换为整数。
    int n = atoi(argv[1]);
    
    // 检查n是否为正整数，且大于1。
    if (n <= 1) {
        fprintf(stderr, "错误: n 必须是大于1的正整数。\n");
        return EXIT_FAILURE;
    }

    // 打开文件用于写入。
    FILE *f = fopen("data.txt", "w");
    if (!f) {
        perror("文件打开失败");
        return EXIT_FAILURE;
    }

    // 定义常量和变量。
    const double xmin = -6.0 * M_PI;
    const double xmax = +6.0 * M_PI;
    const double delta = (xmax - xmin) / (n - 1);

    // 循环n次，计算x和y的值，并写入文件。
    for (int j = 0; j < n; j++) {
        double x = xmin + j * delta;
        double y;
        
        // 使用一个小的容忍度来判断x是否接近0，以避免浮点数比较问题。
        if (fabs(x) < 1e-9) {
            y = 1.0;
        } else {
            y = sin(x) / x;
        }
        
        // 将x和y的值写入文件，用制表符分隔。
        fprintf(f, "%lf\t%lf\n", x, y);
    }

    // 关闭文件。
    fclose(f);
    
    printf("成功生成数据文件: data.txt\n");
    // 成功完成，返回成功状态。
    return EXIT_SUCCESS;
}
