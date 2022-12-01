#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class point {
private:
    float x;
    float y;

public:
    float getX() {
        return x;
    }

    float getY() {
        return y;
    }
    point(float x1, float y1) {
        x = x1;
        y = y1;
    };

    point(const point &a_point) {
        x = a_point.x;
        y = a_point.y;
    }

    point &operator=(const point &kek) {
        x = kek.x;
        y = kek.y;
        return *this;
    }

};

class polyline {
private:
    vector<point> p_polyline;
public:
    explicit polyline(vector<point> &cline) {
        if (cline.size() < 3) {
            p_polyline = cline;
        } else {
            cout << "Не ломаная";
            p_polyline.clear();
            exit(0);
        }
    }

    ~polyline() {
        p_polyline.clear();
    }

    polyline(polyline &cline) {
        p_polyline = cline.p_polyline;
    }

    polyline &operator=(polyline const &cline) {
        p_polyline = cline.p_polyline;
        return *this;
    }

    float perimeter() {
        float per = 0, sum;
        for (int i = 0; i < p_polyline.size() - 1; i++) {
            sum = sqrt(pow((p_polyline[i].getX() - p_polyline[i - 1].getX()), 2) +
                       pow((p_polyline[i].getY() - p_polyline[i - 1].getY()), 2));
            per += sum;
        }
        return per;
    }
};

class Closed_polyline {
public:
    vector<point> c_line;
    explicit Closed_polyline(vector<point> &cline) {
        if ((cline[0].getX() == cline[cline.size() - 1].getX() && cline[0].getY() == cline[cline.size() - 1].getY()) && cline.size() > 3)  {
            c_line = cline;
        } else {
            cout << "Не замкнутая ломаная";
            c_line.clear();
            exit(0);
        }
    }

    ~Closed_polyline() {
        c_line.clear();
    }

    Closed_polyline(Closed_polyline &cline) {
        c_line = cline.c_line;
    }

    Closed_polyline &operator=(Closed_polyline const &cline) {
        c_line = cline.c_line;
        return *this;
    }


public:
    float perimeter() {
        float per = 0, sum;
        for (int i = 0; i < c_line.size() - 1; i++) {
            sum = sqrt(pow((c_line[i].getX() - c_line[i - 1].getX()), 2) +
                       pow((c_line[i].getY() - c_line[i - 1].getY()), 2));
            per += sum;
        }
        return per;
    }

    float area() {
        float are = 0;
        for (int i = 0; i < c_line.size(); i++) {
            are += sqrt(pow(abs(c_line[i].getX() - c_line[i - 1].getX()), 2.0) +
                        pow(abs(c_line[i].getY() - c_line[i - 1].getY()), 2.0)) *
                   abs(c_line[i].getY() - c_line[i - 1].getY()) / 2.0;
        }
        return are;
    }

};

class Polygon : public Closed_polyline {
private:
    vector<point> p_polygon;
public:
    static float check(point A, point B, point C) {
        if ((B.getX() - A.getX() * C.getY() - B.getY() - B.getY() - A.getY() * C.getX() - B.getX()) > 0) {
            return 1;
        } else {
            return -1;
        }
    }

    bool check_convex() {
        float check1 = check(p_polygon[0], p_polygon[1], p_polygon[2]);
        for (int i = 2; i < p_polygon.size(); i += 3) {
            if (check1 != check(p_polygon[i - 2], p_polygon[i - 1], p_polygon[i])) {
                cout << "Невыпуклый";
                p_polygon.clear();
                exit(0);
            }
        }
        return true;
    }

    explicit Polygon(vector<point> &cline) : Closed_polyline(cline) {
        if (!check_convex()) {
            p_polygon = cline;
        }
    }

    ~Polygon() {
        p_polygon.clear();
    }

    Polygon(Polygon &cline) : Closed_polyline(cline) {
        p_polygon = cline.p_polygon;
    }

    Polygon &operator=(Polygon const &cline) {
        p_polygon = cline.p_polygon;
        return *this;
    }
};

class Triangle : public Polygon {
private:
    vector<point> t_triangle;
public:
    explicit Triangle(vector<point> &cline) : Polygon(cline) {
        t_triangle = cline;
if (check_convex() && t_triangle.size() != 3) {
cout << "Это не треугольник";
t_triangle.clear();
exit(0);
}
}

~Triangle() {
    t_triangle.clear();
}

Triangle(Triangle &cline) : Polygon(cline) {
        t_triangle = cline.t_triangle;
}

Triangle &operator=(Triangle const &cline) {
    t_triangle = cline.t_triangle;
    return *this;
}
};

class Trapeze : public Polygon {
    vector<point> t_trapeze;
public:
    explicit Trapeze(vector<point> &cline) : Polygon(cline) {
        t_trapeze = cline;
        vector<pair<float, float>> lineVector;
        if (t_trapeze.size() == 4) {
            lineVector.emplace_back((t_trapeze[2].getX() - t_trapeze[1].getX()),
                                    (t_trapeze[2].getY() - t_trapeze[1].getY()));
            lineVector.emplace_back((t_trapeze[3].getX() - t_trapeze[0].getX()),
                                    (t_trapeze[3].getY() - t_trapeze[0].getY()));
            lineVector.emplace_back((t_trapeze[1].getX() - t_trapeze[0].getX()),
                                    (t_trapeze[1].getY() - t_trapeze[0].getY()));
            lineVector.emplace_back((t_trapeze[3].getX() - t_trapeze[2].getX()),
                                    (t_trapeze[3].getY() - t_trapeze[2].getY()));
        } else {
            t_trapeze.clear();
            exit(0);
        }

        if (!collinearVectors(lineVector[0], lineVector[1])) {
            if (!collinearVectors(lineVector[2], lineVector[3])) {
                t_trapeze.clear();
                exit(0);
            }
        } else {
            if (collinearVectors(lineVector[2], lineVector[3])) {
                t_trapeze.clear();
                exit(0);
            }
        }
    }

    ~Trapeze() {
        t_trapeze.clear();
    }

    Trapeze(Trapeze &cline) : Polygon(cline) {
        t_trapeze = cline.t_trapeze;
    }
    Trapeze &operator=(Trapeze const &cline) {
        t_trapeze = cline.t_trapeze;
        return *this;
    }

private:
    static bool collinearVectors(pair<float, float> vector1, pair<float, float> vector2) {
        if (vector1.first / vector2.first >= vector1.second / vector2.second - 0.0000001 &&
            vector1.first / vector2.first <= vector1.second / vector2.second + 0.0000001) {
            return true;
        }
        return false;
    }
};

class G_polygon : public Polygon {
private:
    vector<point> g_polygon;
public:
    explicit G_polygon(vector<point> &cline) : Polygon(cline) {
        g_polygon = cline;
        float len = sqrt(pow((g_polygon[1].getX() - g_polygon[0].getX()), 2) +
                         pow((g_polygon[1].getY() - g_polygon[0].getY()), 2));
        if (check_convex() && g_polygon.size() != 3) {
            if (perimeter() / g_polygon.size() == len) {
                cout << "Это не правильный многоугольник";
                g_polygon.clear();
                exit(0);
            }
        }
    }

    ~G_polygon() {
        g_polygon.clear();
    }

    G_polygon(G_polygon &cline) : Polygon(cline) {
        g_polygon = cline.g_polygon;
    }

    G_polygon &operator=(G_polygon const &cline) {
        g_polygon = cline.g_polygon;
        return *this;
    }
};

int main() {

    return 0;
}