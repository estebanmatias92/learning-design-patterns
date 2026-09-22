# Mission: Visitor Pattern

## Why
Add new operations to a stable class hierarchy without editing existing classes — stop scattering `instanceof` / `dynamic_cast` chains across the codebase.

## Success looks like
- Trace `element.accept(visitor)` → `visitor.visitX(this)` and name both dispatches
- Explain why `visitor.visit(element)` alone fails in C++/Java/C# (static overload binding)
- Implement a new Visitor (e.g. `XmlExporter`) without touching element classes
- State the rule-of-thumb: stable types + growing operations = Visitor; volatile types = avoid it

## Constraints
- Language: C++17 canonical (`visitor/code/` compiles with GCC/Clang/MSVC). Java/C# snippets in lessons are transfer illustrations only.
- Background: solid OOP + polymorphism assumed
- Lessons: short, single-win, interactive

## Out of scope
- `std::variant` / `std::visit`, acyclic visitor, general multi-dispatch
- Compiler/AST tooling specifics (revisit if mission shifts)
