/*
 * CSCI 261 B
 *
 * Kendall Brown
 *
 * Source file for "character" class
*/

#include <ctime>
#include <random>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;

#include "character.h"
#include "expert.h"


character::character() {
    attribute strength, intelligence, wisdom, dexterity, constitution, charisma;
    save physicalEffect, mentalEffect, evasion, tech, luck;
    skill starter;
    weapon charWeapon;
    armor charArmor;

    name = "No name";
    className = "Expert";
    level = 1;
    background = "none";
    training = "none";

    strength.attributeName = "Strength";
    attributes.push_back(strength);
    intelligence.attributeName = "Intelligence";
    attributes.push_back(intelligence);
    wisdom.attributeName = "Wisdom";
    attributes.push_back(wisdom);
    dexterity.attributeName = "Dexterity";
    attributes.push_back(dexterity);
    constitution.attributeName = "Constitution";
    attributes.push_back(constitution);
    charisma.attributeName = "Charisma";
    attributes.push_back(charisma);

    starter.skillName = "Starter";
    starter.skillScore = -1;
    skills.push_back(starter);


    physicalEffect.saveName = "Physical Effect";
    saves.push_back(physicalEffect);
    mentalEffect.saveName = "Mental Effect";
    saves.push_back(mentalEffect);
    evasion.saveName = "Evasion";
    saves.push_back(evasion);
    tech.saveName = "Tech";
    saves.push_back(tech);
    luck.saveName = "Luck";
    saves.push_back(luck);

    /* FIXME: Why do the numbers set in these structs return incorrectly?
    charWeapon.weaponName = "Semi-Automatic Pisol";
    charWeapon.weaponType = "Projectile";
    charWeapon.numDamageDice = 1;
    charWeapon.DamageDiceSize = 6;
    charWeapon.DamageModifier = 1;
    charWeapon.cost = 75;

    charArmor.armorName = "Woven Body Armor";
    charArmor.aC = 5;
    charArmor.cost = 400;
    */

    homeworld = "World";
    armorClass = 9;
}

void character::SetClass() {
    className = "Expert";
}

string character::GetClass() {
    return className;
}

void character::RollAttributes() {
    srand(time(0)); //Seed random values
    rand();

    for (int i = 0; i < attributes.size(); ++i) {
        int attributeScore = 0;
        for (int j = 0; j < 3; ++j) { //Attributes are determined by rolling 3 six-sided die
            attributeScore += ( (rand() % 6) + 1 );
        }
        attributes.at(i).score = attributeScore;
    }
    SetAttributeModifiers();
}

void character::SetAttributeModifiers() {
    for(int i = 0; i < attributes.size(); ++i) { //Ranges of corresponding modifiers
        if (attributes.at(i).score == 18) {
            attributes.at(i).modifier = 2;
        } else if (attributes.at(i).score > 13) {
            attributes.at(i).modifier = 1;
        } else if (attributes.at(i).score > 7) {
            attributes.at(i).modifier = 0;
        } else if (attributes.at(i).score > 3) {
            attributes.at(i).modifier = -1;
        } else {
            attributes.at(i).modifier = -2;
        }
    }
}

void character::AdjustAttributes() {
    bool adjustable = false; //Whether adjusting is possible
    char userChoiceYN = 'N'; //Whether user wishes to adjust

    cout << endl << "Your base attributes are:" << endl; //Show user their attributes
    DisplayAttributes();
    cout << endl;

    for (int i = 0; i < GetAttributes().size(); ++i) { //Determing whether adjusting is possible
        if (GetAttributes().at(i).modifier > 0 ) {
            for (int j = 0; j < GetAttributes().size(); ++j) {
                if (GetAttributes().at(j).modifier < 0) {
                    adjustable = true;
                }
            }
            break;
        }
    }

    if ( !adjustable ) { //If adjusting is not possible, the rest of the function does not run
        cout << "You may not adjust any of your attributes" << endl;
    } else { //If adjusting is possible, the rest of the program only runs if user wishes for it to

        cout << "You may reduce any attribute that is greater than 13 to increase an attribute that is lower than 8."
             << endl;
        cout << "Would you like to adjust any of your attributes? (Y/N)" << endl << "-- ";

        cin >> userChoiceYN;
        userChoiceYN = CheckYN(userChoiceYN);

    }

    while (toupper(userChoiceYN) == 'Y') { //If user wishes to adjust
        int choiceNumber = 1; //Designated number of each possible choice to adjust
        int userChoiceAttribute = 0; //User's choice of attribute to adjust
        int userChoiceTracking = 0; //Allows program to select user's choice to adjust
        string userChoiceAttributeName;

        cout << "Which attribute would you like to remove a point from?" << endl << endl;
        for (int i = 0; i < GetAttributes().size(); ++i) { //Displays possible choices to decrement
            if (GetAttributes().at(i).modifier > 0) {
                cout << choiceNumber << ". " << GetAttributes().at(i).attributeName << endl;
                choiceNumber += 1;
            }
        }
        cout << endl << "-- ";
        cin >> userChoiceAttribute;

        while (userChoiceAttribute < 1 || userChoiceAttribute > choiceNumber) { //Checks that user input is acceptable
            cout << "To choose, please enter a number from 1 to " << choiceNumber << endl;
            cout << "-- ";
            cin >> userChoiceAttribute;
        }

        for (int i = 0; i < GetAttributes().size(); ++i) { //Adjusts by user's choice
            if (GetAttributes().at(i).modifier > 0) {
                userChoiceTracking += 1;
                if (userChoiceTracking == userChoiceAttribute) {
                    SetAttribute(GetAttributes().at(i).attributeName, GetAttributes().at(i).score - 1);
                    //FIXME: Only necessary if allowing the player to change their mind
                    userChoiceAttributeName = GetAttributes().at(i).attributeName;
                }
            }
        }

        //Resets values
        choiceNumber = 1;
        userChoiceAttribute = 0;
        userChoiceTracking = 0;

        cout << endl << "Which attribute would you like to add a point to?" << endl << endl;
        for (int i = 0; i < GetAttributes().size(); ++i) { //Displays possible choices to increment
            if (GetAttributes().at(i).modifier < 0) {
                cout << choiceNumber << ". " << GetAttributes().at(i).attributeName << endl;
                choiceNumber += 1;
            }
        }
        cout << endl << "-- ";
        cin >> userChoiceAttribute;

        while (userChoiceAttribute < 1 || userChoiceAttribute > choiceNumber) { //Checks that user's input is acceptable
            cout << "To choose, please enter a number from 1 to " << choiceNumber << endl;
            cout << "-- ";
            cin >> userChoiceAttribute;
        }

        for (int i = 0; i < GetAttributes().size(); ++i) { //Adjusts by user's choice
            if (GetAttributes().at(i).modifier < 0) {
                userChoiceTracking += 1;
                if (userChoiceTracking == userChoiceAttribute) {
                    SetAttribute(GetAttributes().at(i).attributeName, GetAttributes().at(i).score + 1);
                }
            }
        }

        cout << endl;
        DisplayAttributes(); //Displays the new attributes
        cout << endl;

        adjustable = false; //Checks if further adjustments are possible
        for (int i = 0; i < GetAttributes().size(); ++i) {
            if (GetAttributes().at(i).modifier > 0 ) {
                for (int j = 0; j < GetAttributes().size(); ++j) {
                    if (GetAttributes().at(j).modifier < 0) {
                        adjustable = true;
                    }
                }
                break;
            }
        }

        if (adjustable) { //Only continues if user still wishes to and more adjustments can be made
            cout << "Would you like to adjust another attribute? (Y/N)" << endl;
            cout << "-- ";
            cin >> userChoiceYN;
            userChoiceYN = CheckYN(userChoiceYN);

        } else { //does not continue if no more adjustments can be made
            userChoiceYN = 'N';
            cout << "No further adjustments can be made" << endl;
        }
    }
}

void character::ChoosePrimaryAttributes() {
    char userChoiceYN;
    int userChoicePrimaryAttribute;

    cout << endl << "As an expert, you may choose to make either " << characterClass.GetPrimaryAttributes().at(0) << " or "
         << characterClass.GetPrimaryAttributes().at(1) << " your primary attribute which makes it an automatic 14" << endl;
    cout << "Would you like to do so? (Y/N)" << endl;
    cout << "-- ";
    cin >> userChoiceYN;

    userChoiceYN = CheckYN(userChoiceYN);

    if (userChoiceYN == 'Y') {
        cout << "Which attribute would you like make your primary?" << endl;
        for (int i = 0; i < characterClass.GetPrimaryAttributes().size(); ++i) {
            cout << i + 1 << ". " << characterClass.GetPrimaryAttributes().at(i) << endl;
        }
        cout << endl << "-- ";
        cin >> userChoicePrimaryAttribute;

        userChoicePrimaryAttribute = CheckNumberRange(userChoicePrimaryAttribute, 1, characterClass.GetPrimaryAttributes().size());

        SetAttribute(characterClass.GetPrimaryAttributes().at(userChoicePrimaryAttribute - 1), 14);
    }




}

void character::DisplayAttributes() {
    for (int i = 0; i < GetAttributes().size(); ++i) {
        cout << left << GetAttributes().at(i).attributeName << ":"
             << setw(14 - GetAttributes().at(i).attributeName.size()) << ""<< setw(2) << right
             << GetAttributes().at(i).score << " | " << GetAttributes().at(i).modifier << endl;
    }
}

vector<character::attribute> character::GetAttributes() {
    return attributes;
}

void character::SetAttribute(string attributeToSet, int scoreToSet) {
    for (int i = 0; i < attributes.size(); ++i) {
        if (attributes.at(i).attributeName == attributeToSet) {
            attributes.at(i).score = scoreToSet;
        }
    }

    SetAttributeModifiers();
}

void character::ChooseBackground() {
    int userChoiceBackPackage;
    cout << endl << "You may now choose your character's background package" << endl;
    cout << endl << "You may select from: " << endl;
    for (int i = 0; i < characterClass.GetBackgroundPackages().size(); ++i) {
        cout << i + 1 << ". " << characterClass.GetBackgroundPackages().at(i).packageName << endl;
    }
    cout << "-- ";

    cin >> userChoiceBackPackage;

    userChoiceBackPackage = CheckNumberRange(userChoiceBackPackage, 1, characterClass.GetBackgroundPackages().size());

    background = characterClass.GetBackgroundPackages().at(userChoiceBackPackage - 1).packageName;
    SetSkills(characterClass.GetBackgroundPackages().at(userChoiceBackPackage - 1));
}

void character::ChooseTraining() {
    int userChoiceTrainPackage;
    cout << endl << "You may now choose your character's trainging package" << endl;
    cout << endl << "You may select from: " << endl;
    for (int i = 0; i < characterClass.GetTrainingPackages().size(); ++i) {
        cout << i + 1 << ". " << characterClass.GetTrainingPackages().at(i).packageName << endl;
    }
    cout << "-- ";

    cin >> userChoiceTrainPackage;

    userChoiceTrainPackage = CheckNumberRange(userChoiceTrainPackage, 1, characterClass.GetTrainingPackages().size());

    training = characterClass.GetTrainingPackages().at(userChoiceTrainPackage - 1).packageName;
    SetSkills(characterClass.GetTrainingPackages().at(userChoiceTrainPackage - 1));
}


void character::SetSkills(expert::package skillPackage) {
    bool hasSkill = false;
    for (int i = 0; i < skillPackage.packageSkills.size(); ++i) {
        for (int j = 0; j < skills.size(); ++j) {
            if ( skillPackage.packageSkills.at(i).skillName == skills.at(j).skillName ) {
                skills.at(j).skillScore += 1;
                hasSkill = true;
            }
        }
        if (!hasSkill) {
            skill skillToSet;
            skillToSet.skillName = skillPackage.packageSkills.at(i).skillName;
            skillToSet.skillScore = skillPackage.packageSkills.at(i).skillScore;

            skills.push_back( skillToSet );
        }
        hasSkill = false;
    }
}


void character::DisplaySkills() {
    cout << endl;
    for (int i = 0; i < skills.size(); ++i) {
        if (skills.at(i).skillName != "Starter") {
            cout << left << setw(18) << skills.at(i).skillName << right << "| " <<
                 skills.at(i).skillScore << endl;
        }
    }
}


void character::SetClassStats() {
    SetAttackBonus();
    SetSaves();
    SetStartingHitPoints();
}


void character::SetAttackBonus() {
    attackBonus = characterClass.GetAttackBonus();
}

int character::GetAttackBonus() {
    return attackBonus;
}


void character::SetSaves() {
    for (int i = 0; i < characterClass.GetSaves().size(); ++i) {
        for (int j = 0; j < saves.size(); ++j) {
            if ( characterClass.GetSaves().at(i).saveName == saves.at(j).saveName )
                saves.at(j).saveScore = characterClass.GetSaves().at(i).saveScore;
        }
    }
}


void character::DisplaySaves() {
    cout << endl;
    for (int i = 0; i < saves.size(); ++i) {
        cout << saves.at(i).saveName << ": " << saves.at(i).saveScore << endl;
    }
}

void character::SetStartingHitPoints() {
    int conModifier;

    for (int i = 0; i < attributes.size(); ++i) {
        if (attributes.at(i).attributeName == "Constitution") {
            conModifier = attributes.at(i).modifier;
            break;
        }
    }

    hitPoints.maxHP = characterClass.GetHitDice() + conModifier;
    hitPoints.currentHP = hitPoints.maxHP;
}

character::hp character::GetHitPoints() {
    return hitPoints;
}

void character::RollInitialCredits() {
    credits = 100 * (rand() % 6 + 1) + 400;
}

int character::GetCredits() {
    return credits;
}

/*
void character::SetArmorClass() {
    int dexMod;
    for (int i = 0; i < attributes.size(); ++i) {
        if (attributes.at(i).attributeName == "Dexterity") {
            dexMod = attributes.at(i).modifier;
        }
    }
    armorClass = charArmor.aC + dexMod;
}

character::armor character::GetCharArmor() {
    return charArmor;
}
*/

int character::GetArmorClass() {
    return armorClass;
}

void character::SetName() {
    string nameToSet;
    cout << endl << "Enter your character's name:" << endl;
    cout << "-- ";
    cin >> nameToSet;

    name = nameToSet;
}

string character::GetName() {
    return name;
}

int character::GetLevel() {
    return level;
}

string character::GetHomeworld() {
    return homeworld;
}

string character::GetBackground() {
    return background;
}

string character::GetTraining() {
    return training;
}

int character::Save() {
    ofstream saveFile;
    saveFile.open(GetName());

    if (saveFile.fail()) {
        cout << "Could not save character";
        return -1;
    }

    saveFile << GetName() << endl;
    saveFile << "Level: " << GetLevel() << endl;
    saveFile << "Homeworld: " << GetHomeworld() << endl;
    saveFile << "Background: " << GetBackground() << endl;
    saveFile << "Training: " << GetTraining() << endl;
    saveFile << "Attributes:" << endl;
    for (int i = 0; i < GetAttributes().size(); ++i) {
        saveFile << left << GetAttributes().at(i).attributeName << ":"
             << setw(14 - GetAttributes().at(i).attributeName.size()) << ""<< setw(2) << right
             << GetAttributes().at(i).score << " | " << GetAttributes().at(i).modifier << endl;
    }
    saveFile << "Max HP: " << GetHitPoints().maxHP << " | " << "Current HP: " << GetHitPoints().currentHP << endl;
    saveFile << "Attack Bonus: " << GetAttackBonus() << endl;
    saveFile << "Saves:" << endl;
    for (int i = 0; i < saves.size(); ++i) {
        saveFile << saves.at(i).saveName << ": " << saves.at(i).saveScore << endl;
    }
    saveFile << "Skills:" << endl;
    for (int i = 0; i < skills.size(); ++i) {
        if (skills.at(i).skillName != "Starter") {
            saveFile << left << setw(18) << skills.at(i).skillName << right << "| " <<
                 skills.at(i).skillScore << endl;
        }
    }
    saveFile << "AC: " << GetArmorClass() << endl;
    saveFile << "Credits: " << GetCredits();

    saveFile.close();

}

char character::CheckYN(char answer) {
    answer = toupper(answer);
    while (answer != 'Y' && answer != 'N') { //Checks to make sure user input is acceptable
        cout << "Please enter as either \"Y\" or \"N\"" << endl;
        cout << "-- ";

        cin >> answer;
        answer = toupper(answer);
        cout << endl;
    }
    return answer;
}

int character::CheckNumberRange(int answer, int lowValue, int highValue) {
    while (answer < lowValue || answer > highValue) {
        cout << "Please make a selection from " << lowValue << " through " << highValue << endl;
        cout << "-- ";
        cin >> answer;
    }
    return answer;
}