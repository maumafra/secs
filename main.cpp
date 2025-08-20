#include "World.cpp"

#include <iostream>

struct Pos {
    float x, y;
};

struct Velocity {
    int x;
};

int main() {
    World ecs;
    auto e = ecs.spawn();
    auto e2 = ecs.spawn();

    ecs.addComponent(e, Pos {1.0f, 2.0f});
    ecs.addComponent(e, Velocity {3});

    ecs.addComponent(e2, Velocity {5});
    ecs.addComponent(e2, Pos {-2.0f, -4.0f});

    auto e3 = ecs.spawn();
    ecs.addComponent(e3, Velocity {10});

    Velocity *vel = ecs.getComponent<Velocity>(e3);
    vel->x = 40;

    vel = ecs.getComponent<Velocity>(e);
    std::cout <<  "Entity " << e << " - Velocity: " << vel->x << std::endl; // Entity 0 - Velocity: 3

    vel = ecs.getComponent<Velocity>(e2);
    std::cout <<  "Entity " << e2 << " - Velocity: " << vel->x << std::endl; // Entity 1 - Velocity: 5

    vel = ecs.getComponent<Velocity>(e3);
    std::cout <<  "Entity " << e3 << " - Velocity: " << vel->x << std::endl; // Entity 4 - Velocity: 40

    //ecs.print(); DEBUG purposes
    return 0;
}