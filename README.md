# Test CPP roguelike project

This is a test project to learn how to make a roguelike game in C++.


## How to run


```bash
git clone https://github.com/tgiachi/hyperion-engine
git submodule update --init --recursive
cd hyperion-engine
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release && make -j4
./bin/hyperion-engine
