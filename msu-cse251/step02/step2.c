#include <stdio.h>
#include <math.h>

int main()
{
    double radius = 7.88;
    double height = 12.231;
    double volume, diameter, hypot; //volume体积 diameter直径 hypot平方根

    int wins = 11, losses = 2, games;

    double near = 10;
    double far = 22.5;

    double bottomVolume = 1700;
    double cupVolume = 350;
    int numCups;

    // 这个圆柱体的半径是：xx，高是xx
    // The cylinder has a radius of 7.880000 and a height of 12.231000
    printf("The cylinder has a radius of %f and a height of %f\n", radius, height);

    // %5.2f 表示总显示宽度是5，小数位占2     %8.1f表示总宽度是8，其中小数位占1位
    // The cylinder has a radius of  7.88 and a height of     12.2
    printf("The cylinder has a radius of %5.2f and a height of %8.1f\n", radius, height);

    printf("MSU had an %d-%d season in 2010!\n", wins, losses);

    // 圆柱的体积 = 底面积*高 = PI * R^2 * H
    volume = M_PI * radius * radius * height;

    games = wins + losses;

    hypot = sqrt(near * near + far * far);

    numCups = (int)bottomVolume / cupVolume;
    printf("Number of cups: %d\n", numCups);

    return 0;
}
