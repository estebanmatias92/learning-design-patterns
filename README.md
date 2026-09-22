# learning-design-patterns

[![CI](https://github.com/estebanmatias92/learning-design-patterns/actions/workflows/ci.yml/badge.svg)](https://github.com/estebanmatias92/learning-design-patterns/actions/workflows/ci.yml)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![CMake](https://img.shields.io/badge/CMake-%3E%3D3.16-green)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow)

Aprender patrones de diseño con **lecciones cortas + código C++17 ejecutable**.
Cada patrón es un módulo autocontenido: teoría interactiva (HTML sin dependencias)
+ playground reproducible (CMake + Make).

> Idioma canónico: **C++17**. Los snippets Java/C# aparecen solo como transferencia
> (ver `visitor/MISSION.md`).

## Módulos

| Módulo | Estado | Lecciones | Código |
| ------ | ------ | --------- | ------ |
| `visitor/` | ✅ listo | 4 lecciones + cheatsheet + glosario | 3 ejemplos (`basic_shapes`, `banking`, `document`) |
| `strategy/` | 🔜 roadmap | — | — |
| `observer/` | 🔜 roadmap | — | — |

Ver índice del módulo actual: [`visitor/README.md`](visitor/README.md).

## Cómo leer las lecciones

Sin build, solo un navegador:

```sh
# opción 1: abrir el índice
xdg-open visitor/index.html
# opción 2: servir local (evita file:// quirks)
python3 -m http.server -d visitor 8000
# → http://localhost:8000/
```

O publicadas en GitHub Pages (tras activar, ver Fase F): `https://estebanmatias92.github.io/learning-design-patterns/`.

## Cómo compilar un módulo

```sh
cd visitor/code
make build
make run EXAMPLE=basic_shapes
make run EXAMPLE=banking
make run EXAMPLE=document
make clean
```

Puro CMake (sin Makefile):

```sh
cmake -S visitor/code -B /tmp/build -DCMAKE_BUILD_TYPE=Release
cmake --build /tmp/build
```

Requisitos: GCC ≥ 7 / Clang ≥ 5 / MSVC 2017+ (C++17), CMake ≥ 3.16, GNU Make ≥ 3.81.
Probado localmente con GCC 16 + CMake 4.4.

## Estructura (monorepo)

```
learning-design-patterns/
  README.md            # este archivo (visión monorepo)
  LICENSE              # MIT
  visitor/             # módulo 1: patrón Visitor
    README.md          # índice del módulo
    MISSION.md         # por qué / éxito / alcance
    lessons/           # 0001–0004 .html interactivos
    reference/         # cheatsheet + glosario
    assets/            # styles.css + quiz.js (sin deps)
    code/              # playground C++17 (Pitchfork)
    learning-records/  # ADRs de aprendizaje
    RESOURCES.md       # fuentes primarias
```

Convención para futuros módulos: clonar la estructura de `visitor/`
(`MISSION.md`, `lessons/`, `reference/`, `code/`, `learning-records/`).

## Roadmap

- [ ] Activar GitHub Pages para `visitor/`
- [ ] Cablear framework de tests (`tests/` hoy reservado, `VISITOR_BUILD_TESTS=OFF`)
- [ ] Añadir `strategy/` como segundo módulo
- [ ] `format-check` + `clang-tidy` en CI (hoy solo build)

## Licencia

MIT — ver [LICENSE](LICENSE).
