# Triangulate


A little function to triangulate a simple polygon, given it's contour.


### Usage

```C++
#include <iostream>

#include "triangulate.h"

using namespace Triangulator;

int main(void) {

    std::vector<Point> points { Point{0,0}, Point{1,0}, Point{1,1}, Point{0,1} };
    auto result = triangulate(points);

    for (size_t i =0; i < result.size()/3; i ++) {
        const auto &p1 = points[result[i*3]];
        const auto &p2 = points[result[i*3 + 1]];
        const auto &p3 = points[result[i*3 + 2]];
        std::cout << "Triangle " << i << " => ("
                  << p1.X << ", " << p1.Y << ") ("
                  << p2.X << ", " << p2.Y << ") ("
                  << p3.X << ", " << p3.Y << ")\n";
    }

    return 0;
}
```

This will print:

```
Triangle 0 => (0, 1) (0, 0) (1, 0)
Triangle 1 => (1, 0) (1, 1) (0, 1)
```

### License

Created by Andy Sinesio on 6/25/10.
Edited by JOHN W. RATCLIFF (jratcliff@verant.com) July 22, 2000
Edited by 2014 Anton
Edited by Dinesh Manajipet February 7, 2020

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
