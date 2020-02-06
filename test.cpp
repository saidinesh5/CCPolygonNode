#include <iostream>
#include <cassert>

#include "triangulate.h"

using namespace Triangulator;

int main(void) {

    // The original test case
    std::vector<Point> points {Point{0.00,6.00}, Point{0.00,0.00}, Point{3.00,0.00},
                               Point{4.00,1.00}, Point{6.00,1.00}, Point{8.00,0.00},
                               Point{12.00,0.00}, Point{13.00,2.00}, Point{8.00,2.00},
                               Point{8.00,4.00}, Point{11.00,4.00}, Point{11.00,6.00},
                               Point{6.00,6.00}, Point{4.00,3.00}, Point{2.00,6.00} };


    // A set of points with repeated vertices
    std::vector<Point> points1 {Point{39.950984,-75.186933},
                                Point{39.961154,-75.167580},
                                Point{39.968572,-75.174212},
                                Point{39.975980,-75.181033},
                                Point{39.981865,-75.188906},
                                Point{39.981659,-75.195303},
                                Point{39.994636,-75.187468},
                                Point{40.009989,-75.190446},
                                Point{40.017658,-75.200065},
                                Point{40.024697,-75.209661},
                                Point{40.031531,-75.219625},
                                Point{40.036816,-75.228566},
                                Point{40.043875,-75.238231},
                                Point{40.049193,-75.245805},
                                Point{40.057558,-75.255352},
                                Point{40.065749,-75.263601},
                                Point{40.076237,-75.276513},
                                Point{40.079146,-75.293471},
                                Point{40.076560,-75.306846},
                                Point{40.073788,-75.325313},
                                Point{40.073788,-75.325313},
                                Point{40.056138,-75.320793},
                                Point{40.058909,-75.302325},
                                Point{40.061703,-75.287741},
                                Point{40.059221,-75.284130},
                                Point{40.054870,-75.282316},
                                Point{40.046577,-75.273962},
                                Point{40.037379,-75.263521},
                                Point{40.030696,-75.254219},
                                Point{40.023802,-75.244781},
                                Point{40.017350,-75.234072},
                                Point{40.011325,-75.225368},
                                Point{40.004675,-75.216317},
                                Point{39.997538,-75.207391},
                                Point{39.995075,-75.210939},
                                Point{39.990349,-75.215857},
                                Point{39.972870,-75.209232},
                                Point{39.963504,-75.197938},
                                Point{39.958402,-75.193568},
                                Point{39.950984,-75.186933}};

    // Just a square
    std::vector<Point> points2 { Point{0,0}, Point{1,0}, Point{1,1}, Point{0,1} };
    // A square with 3 horizontal collinear points
    std::vector<Point> points3 { Point{0,0}, Point{0.5, 0}, Point{1,0}, Point{1,1}, Point{0,1} };
    // A square with 3 vertical collinear points
    std::vector<Point> points4 { Point{0,0}, Point{1,0}, Point{1, 0.5}, Point{1,1}, Point{0,1} };

    assert(triangulate(points).size() > 0);
    assert(triangulate(points1).size() > 0);
    assert(triangulate(points2).size() > 0);
    assert(triangulate(points3).size() > 0);
    assert(triangulate(points4).size() > 0);

    const std::vector<Point>& current_points = points4;
    auto result = triangulate(current_points);

    for (size_t i =0; i < result.size()/3; i ++) {
        const auto &p1 = current_points[result[i*3]];
        const auto &p2 = current_points[result[i*3 + 1]];
        const auto &p3 = current_points[result[i*3 + 2]];
        std::cout << "Triangle " << i << " => ("
                  << p1.X << ", " << p1.Y << ") ("
                  << p2.X << ", " << p2.Y << ") ("
                  << p3.X << ", " << p3.Y << ")\n";
    }

    return 0;
}
