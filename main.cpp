#include "World.hpp"

#include <iostream> // for std::cout
#include <cstdlib> // for rand

struct Health {
    float hp;
    float maxHealth;
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
struct Dragon {}; // Tag component
struct Alive {}; // Tag component

float calculateDmg(int rawDmg, int armorPen, int armor) {
    float armorToBeConsidered = armor - armorPen;
    if (armorToBeConsidered < 0) {
        armorToBeConsidered = 0;
    }
    float dmgReduction = rawDmg*(armorToBeConsidered/100);
    return ((float)rawDmg) - dmgReduction;
}

void dragonAttacks(secs::World ecs) {
    std::cout << "\nDragon's turn! (Press any button to continue)";
    std::cin.get();

    auto dragon = ecs.getEntitiesWith<Dragon>().at(0);
    AttackDamage* dragonAtkDmg = ecs.getComponent<AttackDamage>(dragon);

    auto guildMembers = ecs.getEntitiesWith<GuildMember, Alive>();
    int randomIdx = rand() % guildMembers.size();

    auto dragonVictim = guildMembers.at(randomIdx);
    Name* victimName = ecs.getComponent<Name>(dragonVictim);
    Armor* victimArmor = ecs.getComponent<Armor>(dragonVictim);
    Health* victimHealth = ecs.getComponent<Health>(dragonVictim);

    float damage = calculateDmg(
        dragonAtkDmg->attackDmg,
        dragonAtkDmg->armorPenetration,
        victimArmor->armor
    );

    std::cout << "Dragon attacks " << victimName->name << ", dealing " << damage << " points of damage!" << std::endl;

    victimHealth->hp -= damage;

    if (victimHealth->hp <= 0) {
        victimHealth->hp = 0;
        ecs.removeComponent<Alive>(dragonVictim);
        std::cout << victimName->name << " lost his consciousness!" << std::endl;
    } else {
        std::cout << victimName->name << " has " << victimHealth->hp << " HP!"<< std::endl;
    }
}

bool isGuildAlive(secs::World ecs) {
    auto guildMembers = ecs.getEntitiesWith<GuildMember>();

    for (auto guildMember : guildMembers) {
        Health* health = ecs.getComponent<Health>(guildMember);
        if (health->hp != 0) {
            return true;
        }
    }
    std::cout << "The guild lost the battle!" << std::endl;
    return false;
}

void guildAttacks(secs::World ecs) {
    auto dragon = ecs.getEntitiesWith<Dragon>().at(0);
    Armor* dragonArmor = ecs.getComponent<Armor>(dragon);
    Health* dragonHealth = ecs.getComponent<Health>(dragon);

    auto guildMembers = ecs.getEntitiesWith<GuildMember, Alive>();

    for (auto guildMember : guildMembers) {
        Name* name = ecs.getComponent<Name>(guildMember);
        MagicDamage* magicDmg = ecs.getComponent<MagicDamage>(guildMember);
        if (magicDmg) {
            std::cout << name->name << " attacks the Dragon with a spell, dealing " << magicDmg->magicDmg << " points of damage!" << std::endl;
            dragonHealth->hp -= magicDmg->magicDmg;
            continue;
        }
        AttackDamage* atkDmg = ecs.getComponent<AttackDamage>(guildMember);
        float damage = calculateDmg(
            atkDmg->attackDmg,
            atkDmg->armorPenetration,
            dragonArmor->armor
        );
        std::cout << name->name << " attacks the Dragon, dealing " << damage << " points of damage!" << std::endl;
        dragonHealth->hp -= damage;
    }
}

void guildHeals(secs::World ecs) {
    auto xoarshQuery = ecs.getEntitiesWith<GuildMember, Healing, Alive>();
    if (xoarshQuery.size() == 0) {
        return;
    }
    auto xoarsh = xoarshQuery.at(0);
    Healing* healing = ecs.getComponent<Healing>(xoarsh);
    auto guildMembers = ecs.getEntitiesWith<GuildMember>();
    
    int healIndex = 0;
    float lowerHp = 300.0f;
    for (int i = 0; i < guildMembers.size(); i++) {
        Health *health = ecs.getComponent<Health>(guildMembers.at(i));
        if (health->hp < lowerHp) {
            lowerHp = health->hp;
            healIndex = i;
        }
    }

    Name *name = ecs.getComponent<Name>(guildMembers.at(healIndex));
    Health *health = ecs.getComponent<Health>(guildMembers.at(healIndex));
    std::cout << "Xoarsh heals " << name->name << " " << healing->healPoints << " HP!" << std::endl;
    if (health->hp == 0) {
        ecs.addComponent(guildMembers.at(healIndex), Alive{});
    }
    health->hp += healing->healPoints;
    if (health->hp > health->maxHealth) {
        health->hp = health->maxHealth;
    }
    std::cout << name->name << " has " << health->hp << " HP!" << std::endl;
}

bool isDragonAlive(secs::World ecs) {
    auto dragon = ecs.getEntitiesWith<Dragon>().at(0);
    Health* dragonHealth = ecs.getComponent<Health>(dragon);

    if (dragonHealth->hp <= 0) {
        std::cout << "\nDragon is dead!" << std::endl;
        return false;
    }
    std::cout << "\nDragon has " << dragonHealth->hp << " HP!" << std::endl;
    return true;
}


int main() {
    secs::World ecs;

    auto knigth = ecs.spawn();
    ecs.addComponent(knigth, Name {"Nero"});
    ecs.addComponent(knigth, Health {100.0f, 100.0f});
    ecs.addComponent(knigth, Armor {80});
    ecs.addComponent(knigth, AttackDamage{80, 20});
    ecs.addComponent(knigth, GuildMember{});
    ecs.addComponent(knigth, Alive {});

    auto rogue = ecs.spawn();
    ecs.addComponent(rogue, Name {"Sitri"});
    ecs.addComponent(rogue, Health {60.0f, 60.0f});
    ecs.addComponent(rogue, Armor {30});
    ecs.addComponent(rogue, AttackDamage{100, 50});
    ecs.addComponent(rogue, GuildMember{});
    ecs.addComponent(rogue, Alive {});

    auto cleric = ecs.spawn();
    ecs.addComponent(cleric, Name {"Xoarsh"});
    ecs.addComponent(cleric, Health {75.0f, 75.0f});
    ecs.addComponent(cleric, Armor {80});
    ecs.addComponent(cleric, MagicDamage{30});
    ecs.addComponent(cleric, Healing{50});
    ecs.addComponent(cleric, GuildMember{});
    ecs.addComponent(cleric, Alive {});

    auto wizard = ecs.spawn();
    ecs.addComponent(wizard, Name {"Sorrow"});
    ecs.addComponent(wizard, Health {60.0f, 60.0f});
    ecs.addComponent(wizard, Armor {20});
    ecs.addComponent(wizard, MagicDamage{100});
    ecs.addComponent(wizard, GuildMember{});
    ecs.addComponent(wizard, Alive {});

    auto dragon = ecs.spawn();
    ecs.addComponent(dragon, Health {2000.0f, 2000.0f});
    ecs.addComponent(dragon, Armor {90});
    ecs.addComponent(dragon, AttackDamage{55, 20});
    ecs.addComponent(dragon, Dragon{});

    bool dragonLives = true;
    bool guildLives = true;


    std::cout << "Start battle! (Press any button to continue)";
    std::cin.get();
    while(dragonLives && guildLives) {
        dragonAttacks(ecs);
        guildLives = isGuildAlive(ecs);

        std::cout << "\nGuild's turn! (Press any button to continue)";
        std::cin.get();
        guildAttacks(ecs);
        guildHeals(ecs);
        dragonLives = isDragonAlive(ecs);
    }
    //ecs.print(); // DEBUG purposes
    return 0;
}