#include "World.hpp"

#include <iostream>

struct Health {
    float hp;
};

struct Armor {
    int armor;
};

struct AttackDamage {
    int attackDmg;
    int armorPenetration;
};

struct MagicDamage {
    int magicDmg;
};

struct Healing {
    int healPoints;
};

struct Name {
    char* name;
};

struct GuildMember {}; // Tag component
struct Enemy {}; // Tag component

struct Test {};

int main() {
    secs::World ecs;

    auto knigth = ecs.spawn();
    ecs.addComponent(knigth, Name {"Nero"});
    ecs.addComponent(knigth, Health {100.0f});
    ecs.addComponent(knigth, Armor {150});
    ecs.addComponent(knigth, AttackDamage{50, 20});
    ecs.addComponent(knigth, GuildMember{});

    auto rogue = ecs.spawn();
    ecs.addComponent(rogue, Name {"Sitri"});
    ecs.addComponent(rogue, Health {60.0f});
    ecs.addComponent(rogue, Armor {30});
    ecs.addComponent(rogue, AttackDamage{100, 50});
    ecs.addComponent(rogue, GuildMember{});

    auto cleric = ecs.spawn();
    ecs.addComponent(cleric, Name {"Xoarsh"});
    ecs.addComponent(cleric, Health {75.0f});
    ecs.addComponent(cleric, Armor {100});
    ecs.addComponent(cleric, MagicDamage{30});
    ecs.addComponent(cleric, Healing{50});
    ecs.addComponent(cleric, GuildMember{});

    auto wizard = ecs.spawn();
    ecs.addComponent(wizard, Name {"Sorrow"});
    ecs.addComponent(wizard, Health {55.0f});
    ecs.addComponent(wizard, Armor {20});
    ecs.addComponent(wizard, MagicDamage{200});
    ecs.addComponent(wizard, GuildMember{});

    auto dragon = ecs.spawn();
    ecs.addComponent(dragon, Health {2000.0f});
    ecs.addComponent(dragon, Armor {400});
    ecs.addComponent(dragon, AttackDamage{50, 20});
    ecs.addComponent(dragon, Enemy{});

    bool dragonLives = true;
    bool guildLives = true;

    while(dragonLives && guildLives) {
        for (auto entity : ecs.getEntitiesWith<GuildMember, Health, Test>()) {
            Name* nameComponent = ecs.getComponent<Name>(entity);
            std::cout << nameComponent->name << " found!" << std::endl;
        }
        //dragonAttacks
        //guildLives = isGuildAlive
        //guildAttacks
        //dragonLives = isDragonAlive
        //guildHeals
        dragonLives = false;
    }
    //ecs.print(); // DEBUG purposes
    return 0;
}