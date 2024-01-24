Need [clang-uml](https://clang-uml.github.io/index.html)

```sh
clang-uml
clang-uml --add-compile-flag -I/usr/lib/clang/16/include    # might need additional flags, example for my machine
clang-uml --print-from -n load_map_example_sequence         # to get availabel commands for sequence diagram
```

then use plant uml to generate an actual `.svg` vector graphic
```sh
plantuml -tsvg *.puml
```