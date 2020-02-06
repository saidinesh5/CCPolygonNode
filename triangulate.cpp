/*
 *  triangulate.cpp
 
 PRKit:  Precognitive Research additions to Cocos2D.  http://cocos2d-iphone.org
 Contact us if you like it:  http://precognitiveresearch.com
 
 Created by Andy Sinesio on 6/25/10.
 Copyright 2011 Precognitive Research, LLC. All rights reserved.
 
 This class fills a polygon as described by an array of NSValue-encapsulated points with a texture.
 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

// COTD Entry submitted by John W. Ratcliff [jratcliff@verant.com]

// ** THIS IS A CODE SNIPPET WHICH WILL EFFICIEINTLY TRIANGULATE ANY
// ** POLYGON/CONTOUR (without holes) AS A STATIC CLASS.  THIS SNIPPET
// ** IS COMPRISED OF 3 FILES, TRIANGULATE.H, THE HEADER FILE FOR THE
// ** TRIANGULATE BASE CLASS, TRIANGULATE.CPP, THE IMPLEMENTATION OF
// ** THE TRIANGULATE BASE CLASS, AND TEST.CPP, A SMALL TEST PROGRAM
// ** DEMONSTRATING THE USAGE OF THE TRIANGULATOR.  THE TRIANGULATE
// ** BASE CLASS ALSO PROVIDES TWO USEFUL HELPER METHODS, ONE WHICH
// ** COMPUTES THE AREA OF A POLYGON, AND ANOTHER WHICH DOES AN EFFICENT
// ** POINT IN A TRIANGLE TEST.
// ** SUBMITTED BY JOHN W. RATCLIFF (jratcliff@verant.com) July 22, 2000

// Cleaned up the code to use modern C++ features and fixed a couple of bugs

#include <algorithm>
#include <limits>
#include <numeric>

#include "triangulate.h"

namespace Triangulator {

bool Point::operator==(const Point &b) const {
    return std::numeric_limits<real>::epsilon() > (X - b.X)*(X - b.X)
                                                + (Y - b.Y)*(Y - b.Y);
}

static real area(const std::vector<Point> &contour) {
    if (contour.size() <  3)
        return 0;

    int n = contour.size();
    real result = 0;

    for(int p=n-1,q=0; q < n; p=q++)
    {
        result += contour[p].X*contour[q].Y - contour[q].X*contour[p].Y;
    }

    return result*0.5;
}

static bool is_p_inside_triangle_abc(real Ax, real Ay, real Bx, real By, real Cx, real Cy, real Px, real Py) {
    real ax = Cx - Bx, ay = Cy - By;
    real bx = Ax - Cx, by = Ay - Cy;
    real cx = Bx - Ax, cy = By - Ay;
    real apx = Px - Ax, apy = Py - Ay;
    real bpx = Px - Bx, bpy = Py - By;
    real cpx = Px - Cx, cpy = Py - Cy;
    real aCROSSbp = ax*bpy - ay*bpx;
    real cCROSSap = cx*apy - cy*apx;
    real bCROSScp = bx*cpy -by*cpx;

    return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));
}

static bool snip(const std::vector<Point> &contour, size_t u, size_t v, size_t w, const std::vector<size_t>& indices) {
    float Ax = contour[indices[u]].X;
    float Ay = contour[indices[u]].Y;

    float Bx = contour[indices[v]].X;
    float By = contour[indices[v]].Y;

    float Cx = contour[indices[w]].X;
    float Cy = contour[indices[w]].Y;

    // If the points are collinear, meh
    if ( std::numeric_limits<real>::epsilon() > (((Bx-Ax)*(Cy-Ay)) - ((By-Ay)*(Cx-Ax))) )
        return false;

    for (size_t i = 0; i < indices.size(); i++) {
        if (i != u && i!= v && i != w){
            const auto& p = contour[indices[i]];
            if (is_p_inside_triangle_abc(Ax, Ay, Bx, By, Cx, Cy, p.X, p.Y))
                return false;
        }
    }

    return true;
}

std::vector<size_t> triangulate(const std::vector<Point>& contour) {
    if (contour.size() < 3)
        return {};

    std::vector<size_t> result;
    std::vector<size_t> indices(contour.size(), 0);

    std::iota(std::begin(indices), std::end(indices), 0);

    // Reverse the vertices so we have a counterclockwise polygon
    if (area(contour) < 0) {
        std::reverse(indices.begin(), indices.end());
    }

    // Delete consecutive duplicates. This seems to trip the algorithm
    auto last = std::unique(indices.begin(), indices.end(),
                            [&contour](const size_t a, const size_t b) {
                                return contour[a] == contour[b];
                            });
    indices.erase(last, indices.end());

    if (contour[0] == contour[contour.size() - 1]) {
        indices.pop_back();
    }

    // Remove n-2 Vertices, creating 1 triangle every time
    int n = indices.size();
    // This is for error detection, if the polygon we were provided was not a simple polygon
    int count = 2*n;

    for (int m=0,  v = n - 1; n > 2; ) {
        // Triangulation error, we have a bad polygon
        if (0 >= (count--)) {
            return {};
        }

        //3 consecutive vertices. cycle around if we reach the end of vertices
        int u = v; if (n <= u) u = 0;
        v = u + 1; if (n <= v) v = 0;
        int w = v + 1; if (n <= w) w = 0;

        if (snip(contour, u, v, w, indices))  {
            result.push_back(indices[u]);
            result.push_back(indices[v]);
            result.push_back(indices[w]);
            m++;

            indices.erase(indices.begin() + v);
            n--;
            count = 2*n;
        }
    }

    return result;
}

}
