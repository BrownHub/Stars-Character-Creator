/*
 * CSCI 261 B
 *
 * Kendall Brown
 *
 * Header file for "expert" class
 */

#ifndef FINALPROJECT_EXPERT_H
#define FINALPROJECT_EXPERT_H

#include <string>
#include <vector>
using namespace std;

class expert {
public:
    struct save {
        string saveName;
        int saveScore;
    };

    struct skill { //structure for skills and their level
        string skillName;
        int skillScore;
    };

    struct package {
        string packageName;
        vector<skill> packageSkills;
    };

    expert(); //Constructs the expert character class
    int GetHitDice(); //Returns class hit Dice
    vector<string> GetPrimaryAttributes(); //Returns class primary attributes
    int GetAttackBonus(); //Returns class AB
    vector<save> GetSaves(); //Returns class saving scores
    vector<package> GetBackgroundPackages(); //Displays class background packages and returns the player's choice
    vector<package> GetTrainingPackages(); //Displays class training package and returns the player's choice

private:
    string className; //Name of character class
    const int hitDice = 6; //Character class hit dice for determining health
    vector<string> primaryAttributes; //Character class primary attributes
    int attackBonus; //Character class attack bonus
    vector<save> saves; //Character class saves
    vector<package> backgroundPackages; //Background packages for character to choose from
    vector<package> trainingPackages; //Training packages for character to choose from

};


#endif //FINALPROJECT_EXPERT_H
