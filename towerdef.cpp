#include<iostream>
using namespace std;

class Entity
{
    public:

    int id;

    virtual int getID() = 0;

    Entity()
    {
        id = 0;
    }
    
    void setID(int i)
    {
        id = i;
    }
};

class Equipment: public Entity
{
    public:

    float integrity;

    Equipment():Entity()
    {
        integrity = 100;
    }

    void getDull()
    {
        integrity -= 0.1;
    }

    void repair()
    {
        integrity = 100;
    }
};

class Weapon: public Equipment
{
    public:

    int power, range, accuracy;

    Weapon():Equipment()
    {
        power=0;
        range=0;
        accuracy=50;
    }

    int getID()
    {
        return id;
    }
};

class Tool: public Equipment
{
    public:

    int efficiency;
    Tool():Equipment()
    {
        efficiency=50;
    }

    int getID()
    {
        return id;
    }
};

class Character: public Entity
{
    public:

    int health;

    Character():Entity()
    {
        health = 100;
    }

    void takeDmg(int dmg)
    {
        health -= dmg;
    }
};

class Player: public Character
{
    public:

    int coins;

    Player():Character()
    {
        coins = 0;
    }

    void coinSpend(int cost)
    {
        coins -= cost;
    }

    void coinGet(int gold)
    {
        coins += gold;
    }

    int getID()
    {
        return id;
    }
};

class Worker: public Character
{
    public:

    int efficiency;
    Tool pickaxe;

    Worker():Character()
    {
        efficiency = 50;
    }

    int getID()
    {
        return id;
    }

    void getHeal(int heal)
    {
        health += heal;
    }
};

class Army: public Character
{
    public:

    int x, y, armor, dexterity, strength;
    Weapon weapon;

    Army():Character()
    {
        x=0;
        y=0;
        armor=1;
        dexterity=1;
        strength=1;
    }

    int hit()
    {
        return strength + weapon.power * weapon.integrity / 100;
    }
};

class Soldier: public Army
{
    public:

    Soldier():Army()
    {}

    void getHeal(int heal)
    {
        health += heal;
    }

    int getID()
    {
        return id;
    }
};

class Enemy: public Army
{
    public:

    int mvSpeed, goldValue, dmgValue;

    Enemy():Army()
    {
        mvSpeed=1;
        goldValue=10;
        dmgValue=1;
    }

    void moveUp()
    {
        x -= 1;
    }

    void moveDown()
    {
        x += 1;
    }

    void moveRight()
    {
        y += 1;
    }

    void moveLeft()
    {
        y -= 1;
    }

    int getID()
    {
        return id;
    }
};

class Environment: public Entity
{
    public:
    Environment():Entity()
    {}
};


class Map: public Environment
{
    public:

    int width, height, tile[50][50][5];

    Map():Environment()
    {
        width=50;
        height=50;
        for (int i=0;i<width;i++)
            for(int j=0;j<height;j++)
                for(int k=0;k<5;k++)
                    tile[i][j][k] = 0;
    }

    int getID()
    {
        return id;
    }
};

class MapComponent: public Environment
{
    public:

    int x, y, level, price;
    
    MapComponent():Environment()
    {
        x = 0;
        y = 0;
        level = 1;
        price = 0;
    }

    void levelUp()
    {
        level += 1;
    }
};

class Trap: public MapComponent
{
    public:

    int damage, AOE;

    Trap():MapComponent()
    {
        damage = 1;
        AOE = 0;
    }

    void placeTrap(int posx, int posy)
    {
        x = posx;
        y = posy;
    }

    int getID()
    {
        return id;
    }
};

class Tower: public MapComponent
{
    public:

    int range;
    Soldier ranger[3];

    Tower():MapComponent()
    {
        range = 5;
    }

    int getID()
    {
        return id;
    }

    int tRange(int i)
    {
        return range+ranger[i].weapon.range;
    }

};

class Barracks: public MapComponent
{
    public:

    int range;

    Barracks():MapComponent()
    {
        range = 5;
    }

    Soldier unit[3];

    void deployUnit(int i, int posx, int posy)
    {
        unit[i].x = posx;
        unit[i].y = posy;
    }

    int getID()
    {
        return id;
    }
};

class Quarry: public MapComponent
{
    public:

    int oreQuality;
    float accidentChance;

    Quarry():MapComponent()
    {
        oreQuality=1;
        accidentChance = 0.5;
    }

    Worker miner[3];

    int generateGold()
    {
        int sum;
        for(int i; i<3;i++)
        {
            sum += oreQuality + oreQuality*(miner[i].efficiency + miner[i].pickaxe.efficiency);
        }
        return sum;
    }

    int getID()
    {
        return id;
    }
};

int main()
{
    Soldier knight;

    cout << "Knight's health is: " << knight.health;

    Tower tower1;

    tower1.range = 10;

    cout << "\nTower range is: " << tower1.tRange(1);

    Quarry quarry1;

    cout << "\nQuarry generated " << quarry1.generateGold() << " gold";

    return 0;
}