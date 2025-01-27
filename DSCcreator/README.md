
# DSCcreator

A C data structure generator that creates optimized implementations of common data structures.

## Features

- Generate thread-safe and non-thread-safe implementations
- Support for multiple data structures:
- Linked List
- Stack
- Queue
- Binary Search Tree
- AVL Tree
- Red-Black Tree
- Hash Table
- Heap
- Graph
- Trie- Comprehensive test suite
- Performance benchmarking
- Documentation generation

## Requirements

- CMake 3.10 or higher
- C11 compliant compiler
- Python 3.6+ (for documentation generation)
- pthread support (for thread-safe implementations)

## Building
bash
mkdir build
cd build
cmake ..
make


## Testing

Run all tests:

bash
python3 scripts/test_all.py


Or run individual test components:

bash
cd build
ctest

## Usage

Generate a data structure:

bash
./dsc create list mylist --thread-safe

List available templates:

bash
./dsc list


Get information about a specific type:

bash
./dsc info hashtable


# Documentation

Generate documentation:

bash
python3 scripts/generate_docs.py


Documentation will be available in the `docs` directory.

## Examples

See the `examples` directory for usage examples:
- Basic data structure usage
- Thread-safe implementations
- Performance benchmarks

## License

MIT License


