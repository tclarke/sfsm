# sfsm
A C++ finite state machine that's mostly static via templates.

Requires at least c++17. Known to compile on g++ 10 and g++ 11.

## Usage
This is a header-only library and is fairly easy to use. Note that large state machines might take a long time to compile and the efficiency gains of template metaprogramming fall away.

See _demo.cpp_ for an example usage.
