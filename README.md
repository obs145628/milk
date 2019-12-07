# Milk

Toy language to learn more about compilers design.
Project just gettint started, far from being usable.

What is done:
- Reference and grammar for Milk V0 (a really basic version with very limited features)
- cgen: intermediate representation, can be compiled to C. Most features are there. Enough to be usable

What must be done to have a working V0 compiler:
- Implement lexer, parser and AST for V0
- Implement semantic analysis for V0
- Implement conversion from Milk AST to cgen Ast
- Implement C runtime and standard library code

## Building

Tested with clang++ 10

```shell
git submodule update --init --recursive
mkdir _build
cd _build
cmake ..
make 
```

## Testing

python3 required for testing

```shell
make check
```

## Documentation

doxygen and dot required

```shell
make doc
```