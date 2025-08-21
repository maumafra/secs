#include "World.cpp"

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

struct GuildMember {}; // Tag component
struct Enemy {}; // Tag component

int main() {
    secs::World ecs;

    auto knigth = ecs.spawn();
    ecs.addComponent(knigth, Health {100.0f});
    ecs.addComponent(knigth, Armor {150});
    ecs.addComponent(knigth, AttackDamage{50, 20});
    ecs.addComponent(knigth, GuildMember{});

    
    auto rogue = ecs.spawn();
    ecs.addComponent(rogue, Health {60.0f});
    ecs.addComponent(rogue, Armor {30});
    ecs.addComponent(rogue, AttackDamage{100, 50});
    ecs.addComponent(rogue, GuildMember{});

    auto cleric = ecs.spawn();
    ecs.addComponent(cleric, Health {75.0f});
    ecs.addComponent(cleric, Armor {100});
    ecs.addComponent(cleric, MagicDamage{30});
    ecs.addComponent(cleric, Healing{50});
    ecs.addComponent(cleric, GuildMember{});

    auto wizard = ecs.spawn();
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
        //dragonAttacks
        //guildLives = isGuildAlive
        //guildAttacks
        //dragonLives = isDragonAlive
        //guildHeals
        dragonLives = false;
    }
    ecs.print(); // DEBUG purposes
    return 0;
}