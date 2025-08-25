# Mau makes SECS (W.I.P.)
This is a Simple Entity Component System project written in C++. 👻

This should be enough for an ECS Application. But if somehow you find any bugs, feel free to open a Pull Request. 😉

## ECS Knowledge
I'm new to ECS and C++, so I've been studying a lot.

My main references are [flecs](https://github.com/SanderMertens/flecs) and Sander Mertens' ECS articles (flecs creator).

The study materials that I use are listed below:

- https://github.com/SanderMertens/flecs
- https://ajmmertens.medium.com/
- https://github.com/zenialexandre/lotus
- https://github.com/bevyengine/bevy
- https://github.com/skypjack/entt

## Example
There is a full application on main.cpp file, so feel free to check it out.

A simple example is shown below:
```c++
#include "World.hpp"

struct Pos {
    int x, y;
}

struct Vel {
    int x, y;
}

int main() {
    secs::World ecs;

    auto entity = ecs.spawn();
    ecs.addComponent(entity, Pos{0, 0});
    ecs.addComponent(entity, Vel{0, 1});

    auto entity2 = ecs.spawn();
    ecs.addComponent(entity2, Pos{0, 0});
    ecs.addComponent(entity2, Vel{1, 0});

    for (auto ent : ecs.getEntitiesWith<Pos, Vel>()) {
        Pos* pos = ecs.getComponent<Pos>(ent);
        Vel* vel = ecs.getComponent<Vel>(ent);
        pos->x += vel->x;
        pos->y += vel->y;
    }
    return 0;
}
```

## Build
This project uses CMake, so ideally you should have it installed.

In the project directory, run:
```
cmake . -B build
```
^This should create a build directory, with all the necessary build files for building the project.

Then, to actually build the code, run:
```
cmake --build build
```

And voilà, your executable is generated.

## Notes
I am using [wyhash](https://github.com/wangyi-fudan/wyhash) for hashing.