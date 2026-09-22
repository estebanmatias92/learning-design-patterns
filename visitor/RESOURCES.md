# Visitor Resources

## Knowledge

- [Refactoring.Guru: Visitor](https://refactoring.guru/design-patterns/visitor)
  Canonical structure, `accept` wiring, pros/cons with Java examples. Use for: element/visitor skeleton, when-to-use, implementation steps.
- [Refactoring.Guru: Visitor and Double Dispatch](https://refactoring.guru/design-patterns/visitor-double-dispatch)
  Why overloaded `visit()` binds statically and why `accept()` fixes it. Use for: single vs double dispatch lesson.
- [MartinLwx: Understanding Visitor Pattern, the art of double dispatch](https://martinlwx.github.io/en/visitor-pattern-understanding-double-dispatch/)
  Two single dispatches compose into double dispatch; AST `accept`/`visit_*` walkthrough. Use for: handshake mental model.
- [SourceMaking: Visitor](https://sourcemaking.com/design_patterns/visitor)
  GoF intent, "recover lost type information", double-dispatch definition. Use for: expression-problem framing.
- [Design Patterns in Action: Visitor](https://designpatternsinaction.com/pattern/visitor)
  Typed `visitParagraph`/`visitHeading` example, double-dispatch handshake, `instanceof` pitfalls. Use for: quiz design, anti-patterns.

## Wisdom (Communities)

- [r/code_review](https://www.reddit.com/r/code_review/)
  Get feedback on your first Visitor implementation. Use for: checking `accept` wiring and visitor cohesion.
- [Stack Overflow: `design-patterns` + `visitor-pattern`](https://stackoverflow.com/questions/tagged/visitor-pattern)
  High-signal Q&A on dispatch edge cases. Use for: "why not just overload?" troubleshooting.

## Gaps

- No single-file Java runnable covering all four lessons found; lessons ship their own minimal `Dot/Circle` examples instead.
