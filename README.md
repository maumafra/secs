# Mau makes SECS (W.I.P.)
This is a Simple Entity Component System project written in C++. 👻

It is still in development. 😉

## ECS Knowledge
I'm new to ECS and C++, so I've been studying a lot.

My main references are [flecs](https://github.com/SanderMertens/flecs) and Sander Mertens' ECS articles (flecs creator).

The study materials that I use are listed below:

- https://github.com/SanderMertens/flecs
- https://ajmmertens.medium.com/
- https://github.com/zenialexandre/lotus
- https://github.com/bevyengine/bevy
- https://github.com/skypjack/entt

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