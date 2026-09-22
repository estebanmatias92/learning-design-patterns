#include <cstddef>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Forward declarations (cyclic Visitor <-> Element dependency)
class Paragraph;
class Image;
class Table;

// 1. Visitor interface
// 2b. Second dispatch target (dynamic on Visitor,
//     static overload picked by caller)
class Visitor {
  public:
    virtual void visit(const Paragraph *p) = 0;
    virtual void visit(const Image *i) = 0;
    virtual void visit(const Table *t) = 0;
    virtual ~Visitor() = default;
};

// 2. Visitable / Element interface
class Node {
  public:
    virtual void accept(Visitor &v) = 0;
    virtual ~Node() = default;
};

// 3. ConcreteElements (stable types)
class Paragraph : public Node {
  public:
    std::string text;
    explicit Paragraph(std::string t) : text(std::move(t)) {}
    // STATIC: overload picked at compile-time (this is Paragraph*)
    // + DISPATCH 2 (dynamic): virtual picks concrete visitor at runtime
    void accept(Visitor &v) override { v.visit(this); }
};

class Image : public Node {
  public:
    std::string alt, src;
    Image(std::string a, std::string s) : alt(std::move(a)), src(std::move(s)) {}
    // STATIC: overload picked at compile-time (this is Image*)
    // + DISPATCH 2 (dynamic): virtual picks concrete visitor at runtime
    void accept(Visitor &v) override { v.visit(this); }
};

class Table : public Node {
  public:
    std::vector<std::string> cells;
    int cols;
    Table(std::vector<std::string> c, int n) : cells(std::move(c)), cols(n) {}
    // STATIC: overload picked at compile-time (this is Table*)
    // + DISPATCH 2 (dynamic): virtual picks concrete visitor at runtime
    void accept(Visitor &v) override { v.visit(this); }
};

// 4. ConcreteVisitors (both total: meaningful for every element)
class HtmlExporter : public Visitor {
  public:
    void visit(const Paragraph *p) override { std::printf("<p>%s</p>\n", p->text.c_str()); }
    void visit(const Image *i) override {
        std::printf("<img src=\"%s\" alt=\"%s\" />\n", i->src.c_str(), i->alt.c_str());
    }
    void visit(const Table *t) override {
        const auto cols = static_cast<std::size_t>(t->cols);
        std::printf("<table>\n");
        for (std::size_t k = 0; k < t->cells.size(); ++k) {
            if (k % cols == 0) {
                std::printf("  <tr>\n");
            }
            std::printf("    <td>%s</td>\n", t->cells[k].c_str());
            if (k % cols == cols - 1) {
                std::printf("  </tr>\n");
            }
        }
        std::printf("</table>\n");
    }
};

class PlainTextExporter : public Visitor {
  public:
    void visit(const Paragraph *p) override { std::printf("%s\n", p->text.c_str()); }
    void visit(const Image *i) override { std::printf("[image: %s]\n", i->alt.c_str()); }
    void visit(const Table *t) override {
        const auto cols = static_cast<std::size_t>(t->cols);
        for (std::size_t k = 0; k < t->cells.size(); ++k) {
            std::printf("%s", t->cells[k].c_str());
            std::printf(k % cols == cols - 1 ? "\n" : " | ");
        }
    }
};

// 5. ObjectStructure + 6. Client
class Document {
    std::vector<std::unique_ptr<Node>> blocks;

  public:
    void add(std::unique_ptr<Node> b) { blocks.push_back(std::move(b)); }
    void accept(Visitor &v) {
        // DISPATCH 1 (dynamic): virtual picks
        // Paragraph/Image/Table::accept at runtime
        for (auto &b : blocks) {
            b->accept(v);
        }
    }
};

int main() {
    Document doc;
    doc.add(std::make_unique<Paragraph>("Hello, visitor!"));
    doc.add(std::make_unique<Image>("sunset", "sunset.png"));
    doc.add(std::make_unique<Table>(std::vector<std::string>{"a1", "b1", "a2", "b2"}, 2));

    HtmlExporter html;
    // Client: same call, concrete visitor (HtmlExporter) at runtime
    doc.accept(html);

    std::cout << "\n---\n\n";

    PlainTextExporter plain;
    // Client: same call, concrete visitor (PlainTextExporter) at runtime
    doc.accept(plain);
}
