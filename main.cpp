/*
 * CSCI 261 B
 *
 * Kendall Brown
 *
 * Program creates a character in the "Stars Without Number" Roleplaying Game and saves it
 */

#include <iostream>
#include <iomanip>
using namespace std;

#include "character.h"

int main() {
    character newCharacter; //Creates new character

    newCharacter.RollAttributes(); //Generates character's initial attributes

    newCharacter.AdjustAttributes(); //Allows player to adjust and set new values for attributes

    newCharacter.ChoosePrimaryAttributes(); //Allows player to choose the benefit of one of their primary attributes
    newCharacter.DisplayAttributes();

    newCharacter.ChooseBackground(); //Player chooses character background and changes are implemented
    newCharacter.DisplaySkills();

    newCharacter.ChooseTraining(); //Player chooses character training and changes are implemented
    newCharacter.DisplaySkills();

    newCharacter.SetClassStats(); //Rest of class stats are implemented
    newCharacter.DisplaySaves();

    newCharacter.RollInitialCredits(); //Starting money is generated

    newCharacter.SetName(); //User assigns character a name

    newCharacter.Save(); //Character file is created


    return 0;
}
