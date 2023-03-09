#include <iostream>
#include <cmath>
class MathMixin {
public:
    const double pi() const {
        return std::acos(-1);
    }

    double approximate_ellipse_perimetr(double a, double b) const {
        return pi() * std::sqrt(2 * (a * a + b * b));
    }

    double square_by_Geron(double a, double b, double c) const {
        auto p = (a + b + c) / 2;
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }

    //return angle between b and c (radians)
    double theCosineTheoremAngle(double a, double b, double c) const {
        return std::acos((b * b + c * c - a * a) / (2 * b * c));
    }

    //return third side of triangle
    double theCosineTheoremSide(double b, double c, double angelbc) const {
        return std::sqrt(b * b + c * c - (2 * b * c * std::cos(angelbc)));
    }
};
class Figure {
public:
    virtual double perimetr() const = 0;
    virtual double square() const = 0;
};

class Ellipse : public Figure, private MathMixin {
public:
    Ellipse(double a, double b) : a(a), b(b) {}

    double perimetr() const override {
        return approximate_ellipse_perimetr(a, b);
    }

    double square() const override {
        return pi() * a * b;
    }
private:
    double a, b;
};

class Circle : public Ellipse {
public:
    Circle(double r) : Ellipse(r, r) {}
};

//triangle may be initialize by three sides (by default) or two sides with angle between them (in radians)
class Triangle : public Figure, private MathMixin{
public:
    Triangle(double a, double b, double c, bool cIsAngle = false) {
        if (!cIsAngle) {
            this->a = a;
            this->b = b;
            this->c = c;
            angleab = 0;
        }
        else {
            this->a = a;
            this->b = b;
            angleab = c;
            this->c = 0;
        }
    }

    double perimetr() const override {
        if (c) { return a + b + c; }
        else { return a + b + theCosineTheoremSide(a, b, angleab);}
    }

    double square() const override {
        if (c) { return square_by_Geron(a, b, c); }
        else { return 0.5 * a * b * std::sin(angleab); }
    }

    void AllsidesAndAngles() const{
        if (c) {
            std::cout << "A, B, and C sides are " << a << " " << b << " " << c << std::endl;
            std::cout << "Angels (in radians) between AB, BC and AC are " << theCosineTheoremAngle(c, a, b) <<
                " " << theCosineTheoremAngle(a, b, c) << " " << theCosineTheoremAngle(b, a, c) << std::endl;
        }
        else {
            double tempC = theCosineTheoremSide(a, b, angleab);
            std::cout << "A, B, and C sides are " << a << " " << b << " "
                << tempC << std::endl;
            std::cout << "Angels (in radians) between AB, BC and AC are " << angleab <<
                " " << theCosineTheoremAngle(a, b, tempC) << " " << theCosineTheoremAngle(b, a, tempC) << std::endl;
        }       
    }
private:
    double a, b, c, angleab;
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(double edge, double base) : Triangle(edge, edge, base) {}
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
    EquilateralTriangle(double a) : IsoscelesTriangle(a, a) {}
};

class Rectangle : public Figure {
public:
    Rectangle(double a, double b) : a(a), b(b) {}
    double perimetr() const override {
        return 2 * (a + b);
    }
    double square() const override {
        return a * b;
    }
private:
    double a, b;
};

class Square : public Rectangle {
public:
    Square(double a) : Rectangle(a, a) {}
};

int main() {
    Ellipse ell(4, 5);
    std::cout << "Ellipse perimetr is " << ell.perimetr() << std::endl;
    std::cout << "Ellipse square is " << ell.square() << std::endl;

    Circle circle(3);
    std::cout << "Circle perimetr is " << circle.perimetr() << std::endl;
    std::cout << "Circle square is " << circle.square() << std::endl;

    Triangle triangleThreeSides(3, 4, 5);
    std::cout << "Triangle 1 perimetr is " << triangleThreeSides.perimetr() << std::endl;
    std::cout << "Triangle 1 square is " << triangleThreeSides.square() << std::endl;
    triangleThreeSides.AllsidesAndAngles();

    Triangle triangleTwoSides(3, 4, 1.57079633, true);
    std::cout << "Triangle 2 perimetr is " << triangleTwoSides.perimetr() << std::endl;
    std::cout << "Triangle 2 square is " << triangleTwoSides.square() << std::endl;
    triangleTwoSides.AllsidesAndAngles();

    IsoscelesTriangle iso(10, 15);
    std::cout << "Isosceles Triangle perimetr is " << iso.perimetr() << std::endl;
    std::cout << "Isosceles Triangle square is " << iso.square() << std::endl;
    iso.AllsidesAndAngles();

    EquilateralTriangle eq(10);
    std::cout << "Equilateral Triangle perimetr is " << eq.perimetr() << std::endl;
    std::cout << "Equilateral Triangle square is " << eq.square() << std::endl;
    eq.AllsidesAndAngles();

    Rectangle rec(4, 5);
    std::cout << "Rectangle perimetr is " << rec.perimetr() << std::endl;
    std::cout << "Rectangle square is " << rec.square() << std::endl;

    Square sq(87);
    std::cout << "Square perimetr is " << sq.perimetr() << std::endl;
    std::cout << "Square square is " << sq.square() << std::endl;
}