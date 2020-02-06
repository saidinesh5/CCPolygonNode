
/*
 * triangulate.h
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

/**********************************************************************/
/************ HEADER FILE FOR TRIANGULATE.H ***************************/
/**********************************************************************/


#pragma once

#include <vector>

namespace Triangulator {

typedef float real;

struct Point {
    bool operator==(const Point& other) const;

    real X;
    real Y;
};


/**
 * @brief triangulate a simple polygon into triangles
 * @param contour - the outline of the polygon
 * @return if triangulation is successful,
 *  return list of triangles like: [A0, A1, A2, B0, B1, B2, ...]
 *      Where A, B, C .... are various possible triangles
 *      0, 1, 2 are the vertices of the triangle
 *      where A0, A1, A2, B0, B1, B2 are all indices of points in the contour
 * else returns empty vector
 */
std::vector<size_t> triangulate(const std::vector<Point>& contour);

}
