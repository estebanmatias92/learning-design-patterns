#include <cstdio>
#include <memory>
#include <vector>

// Forward declarations (cyclic Visitor <-> Element dependency)
class Dot;
class Circle;
class Rectangle;

// 1. Visitor interface
// 2b. Second dispatch target (dynamic on Visitor,
//     static overload picked by caller)
class Visitor {
  public:
    virtual void visit(const Dot *d) = 0;
    virtual void visit(const Circle *c) = 0;
    virtual void visit(const Rectangle *r) = 0;
    virtual ~Visitor() = default;
};

// 2. Visitable / Element interface
class Shape {
  public:
    virtual void accept(Visitor &v) = 0;
    virtual ~Shape() = default;
};

// 3. ConcreteElements
class Dot : public Shape {
  public:
    double x, y;
    Dot(double x, double y) : x(x), y(y) {}
    // STATIC: overload picked at compile-time (this is Dot*)
    // + DISPATCH 2 (dynamic): virtual picks concrete visitor at runtime
    void accept(Visitor &v) override { v.visit(this); }
};

class Circle : public Shape {
  public:
    double x, y, radius;
    Circle(double x, double y, double r) : x(x), y(y), radius(r) {}
    // STATIC: overload picked at compile-time (this is Circle*)
    // + DISPATCH 2 (dynamic): virtual picks concrete visitor at runtime
    void accept(Visitor &v) override { v.visit(this); }
};

class Rectangle : public Shape {
  public:
    double x, y, width, height;
    Rectangle(double x, double y, double w, double h) : x(x), y(y), width(w), height(h) {}
    // STATIC: overload picked at compile-time (this is Rectangle*)
    // + DISPATCH 2 (dynamic): virtual picks AreaCalculator vs XmlExporter at runtime
    void accept(Visitor &v) override { v.visit(this); }
};

// 4. ConcreteVisitors
class AreaCalculator : public Visitor {
  public:
    double total_area = 0.0;
    void visit(const Dot *) override {}
    void visit(const Circle *c) override {
        total_area += 3.141592653589793 * c->radius * c->radius;
    }
    void visit(const Rectangle *r) override { total_area += r->width * r->height; }
};

class XmlExporter : public Visitor {
  public:
    void visit(const Dot *d) override { std::printf("<dot x=\"%g\" y=\"%g\" />\n", d->x, d->y); }
    void visit(const Circle *c) override {
        std::printf("<circle x=\"%g\" y=\"%g\" r=\"%g\" />\n", c->x, c->y, c->radius);
    }
    void visit(const Rectangle *r) override {
        std::printf("<rect x=\"%g\" y=\"%g\" w=\"%g\" h=\"%g\" />\n", r->x, r->y, r->width,
                    r->height);
    }
};

// 5. ObjectStructure + 6. Client
class Drawing {
    std::vector<std::unique_ptr<Shape>> shapes;

  public:
    void add(std::unique_ptr<Shape> s) { shapes.push_back(std::move(s)); }
    void accept(Visitor &v) {
        // DISPATCH 1 (dynamic): virtual picks Dot/Circle/Rectangle::accept at runtime
        for (auto &s : shapes)
            s->accept(v);
    }
};

int main() {
    Drawing drawing;
    drawing.add(std::make_unique<Dot>(1.0, 2.0));
    drawing.add(std::make_unique<Circle>(0.0, 0.0, 5.0));
    drawing.add(std::make_unique<Rectangle>(0.0, 0.0, 4.0, 6.0));

    AreaCalculator area;
    // Client: same call, concrete visitor (AreaCalculator) picked at runtime
    drawing.accept(area);
    std::printf("Total area: %.2f\n", area.total_area);

    XmlExporter xml;
    // Client: same call, concrete visitor (XmlExporter) picked at runtime
    drawing.accept(xml);
}
