/*
 * CSCI 261 B
 *
 * Kendall Brown
 *
 * Header file for "character" class
 */

#ifndef FINALPROJECT_CHARACTER_H
#define FINALPROJECT_CHARACTER_H

#include <string>
#include <vector>
using namespace std;

#include "expert.h"

class character {
private:
    struct attribute { //Structure for attribute scores and modifiers
        string attributeName;
        int score;
        int modifier;
    };

    struct save {
        string saveName;
        int saveScore;
    };

    struct skill { //structure for skills and their level
        string skillName;
        int skillScore;
    };

    struct hp { //structure for max and current hit points
        int maxHP;
        int currentHP;
    };

    struct weapon { //structure for weapon stats
        string weaponName;
        string weaponType;
        int numDamageDice;
        int DamageDiceSize;
        int DamageModifier;
        int cost;
    };

    struct armor { //structure for armor stats
        string armorName;
        int aC;
        int cost;
    };

    string name; //Character's name
    expert characterClass;
    int level; //Character's level
    string className; //Character's class
    string background; //Character's background package
    string training; //Character's training package
    const int NUM_ATTRIBUTES = 6;
    vector<attribute> attributes; //Character's attributes
    int attackBonus; //Character's attack bonus
    const int NUM_SAVES = 5;
    vector<save> saves; //Character's saving scores
    vector<skill> skills; //Character's skill levels
    string homeworld; //Character's homeworld
    hp hitPoints; //Character's hit points
    int armorClass; //Character's armor class
    int credits; //Character's money
    weapon charWeapon; //Character's weapon
    armor charArmor; //Character's armor
    char CheckYN(char answer); //Checks that user inputs to Y/N questions are acceptable
    int CheckNumberRange(int answer, int lowValue, int highValue); //Checks that unser inputs to integer responses are within an acceptable range

public:
    character(); //Constructs necesary variables
    void SetName(); //Sets character's name
    string GetName(); //Returns character's name
    void SetClass(); //Sets character's class
    string GetClass(); //Returns character's class
    void RollAttributes(); //Rolls and sets character's initial attributes
    void SetAttributeModifiers(); //Sets modifier value for attributes
    void AdjustAttributes(); //Allows player to adjust their attributes within game rules
    void ChoosePrimaryAttributes(); //Allows player to choose which primary attribute to benefit from
    void DisplayAttributes(); //Shows attributes to user
    void SetAttribute(string attributeToSet, int scoreToSet); //Sets character's attribute
    vector<attribute> GetAttributes(); //Returns character's attributes
    void SetSkills(expert::package skillPackage);
    void DisplaySkills();
    void ChooseBackground(); //Sets character's background package
    string GetBackground(); //Returns character's background package
    void ChooseTraining(); //Sets character's training package
    string GetTraining(); //Returns character's background package
    void SetClassStats();
    void SetAttackBonus(); //Sets character's AB
    int GetAttackBonus(); //Returns character's AB
    void SetSaves(); //Sets character's saving scores
    void DisplaySaves(); //Returns character's saving scores
    skill GetSkills(); //Returns character skills
    void SetHomeworld(); //Sets character's place of origin
    string GetHomeworld(); //Returns character's place of origin
    void SetStartingHitPoints(); //Sets character's first hit points
    void SetHitPoints(); //Sets character's hit points based on stats
    hp GetHitPoints(); //Returns character's hit points
    void SetArmorClass(); //Sets character's AC based on stats
    int GetArmorClass(); //Returns character's AC
    void RollInitialCredits(); //Calculates character's starting money
    int GetCredits(); //Returns character's money
    weapon GetCharWeapon(); //Returns character's weapon
    armor GetCharArmor(); //Returns character's armor
    int GetLevel(); //returns character's level
    int Save(); //Outputs character info to a file
    void Load(); //Retrieves character info from a file
    void Display(); //Displays character's info


};


#endif //FINALPROJECT_CHARACTER_H
