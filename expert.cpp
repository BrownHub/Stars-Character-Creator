/*
 * CSCI 261 B
 *
 * Kendall Brown
 *
 * Source file for "expert" class
 */

#include "expert.h"

expert::expert() {
    save physicalEffect, mentalEffect, evasion, tech, luck;

    className = "Expert";
    primaryAttributes.push_back("Intelligence");
    primaryAttributes.push_back("Charisma");
    attackBonus = 0;

    physicalEffect.saveName="Physical Effect";
    physicalEffect.saveScore = 16;
    saves.push_back(physicalEffect);
    mentalEffect.saveName = "Mental Effect";
    mentalEffect.saveScore = 15;
    saves.push_back(mentalEffect);
    evasion.saveName = "Evasion";
    evasion.saveScore = 12;
    saves.push_back(evasion);
    tech.saveName = "Tech";
    tech.saveScore = 11;
    saves.push_back(tech);
    luck.saveName = "Luck";
    luck.saveScore = 14;
    saves.push_back(luck);

    skill combatProjectile;
    combatProjectile.skillName = "Combat(Projectile)";
    combatProjectile.skillScore = 0;
    skill cultureWorld;
    cultureWorld.skillName = "Culture(World)";
    cultureWorld.skillScore = 0;
    skill navigation;
    navigation.skillName = "Navigation";
    navigation.skillScore = 0;
    skill persuade;
    persuade.skillName = "Persuade";
    persuade.skillScore = 0;
    skill stealth;
    stealth.skillName = "Stealth";
    stealth.skillScore = 0;
    skill survival;
    survival.skillName = "Survival";
    survival.skillScore = 0;
    skill tactics;
    tactics.skillName = "Tactics";
    tactics.skillScore = 0;
    skill vehicleAny;
    vehicleAny.skillName = "Vehicle(Land)";
    vehicleAny.skillScore = 0;
    skill business;
    business.skillName = "Business";
    business.skillScore = 0;
    skill combatPrimitive;
    combatPrimitive.skillName = "Combat(Primitive)";
    combatPrimitive.skillScore = 0;
    skill cultureCriminal;
    cultureCriminal.skillName = "Culture(Criminal)";
    cultureCriminal.skillScore = 0;
    skill gambling;
    gambling.skillName = "Gambling";
    gambling.skillScore = 0;
    skill perception;
    perception.skillName = "Perception";
    perception.skillScore = 0;
    skill security;
    security.skillName = "Security";
    security.skillScore = 0;
    skill combatGunnery;
    combatGunnery.skillName = "Combat(Gunnery)";
    combatGunnery.skillScore = 0;
    skill cultureSpacer;
    cultureSpacer.skillName = "Culture(Spacer)";
    cultureSpacer.skillScore = 0;
    skill exosuit;
    exosuit.skillName = "Exosuit";
    exosuit.skillScore = 0;
    skill techAstronautics;
    techAstronautics.skillName = "Tech(Astronautics)";
    techAstronautics.skillScore = 0;
    skill techPostech;
    techPostech.skillName = "Tech(Postech)";
    techPostech.skillScore = 0;
    skill vehicleSpace;
    vehicleSpace.skillName = "Vehicle(Space)";
    vehicleSpace.skillScore = 0;
    skill computer;
    computer.skillName = "Computer";
    computer.skillScore = 0;
    skill combatUnarmed;
    combatUnarmed.skillName = "Combat(Unarmed)";
    combatUnarmed.skillScore = 0;


    vector<skill> bountyHunterSkills;
    bountyHunterSkills.push_back(combatProjectile);
    bountyHunterSkills.push_back(cultureWorld);
    bountyHunterSkills.push_back(navigation);
    bountyHunterSkills.push_back(persuade);
    bountyHunterSkills.push_back(stealth);
    bountyHunterSkills.push_back(survival);
    bountyHunterSkills.push_back(tactics);
    bountyHunterSkills.push_back(vehicleAny);

    package bountyHunter;
    bountyHunter.packageName = "Bounty Hunter";
    bountyHunter.packageSkills = bountyHunterSkills;

    vector<skill> criminalSkills;
    criminalSkills.push_back(business);
    criminalSkills.push_back(combatPrimitive);
    criminalSkills.push_back(cultureCriminal);
    criminalSkills.push_back(gambling);
    criminalSkills.push_back(perception);
    criminalSkills.push_back(persuade);
    criminalSkills.push_back(security);
    criminalSkills.push_back(stealth);

    package criminal;
    criminal.packageName = "Criminal";
    criminal.packageSkills = criminalSkills;

    vector<skill> pilotSkills;
    pilotSkills.push_back(combatGunnery);
    pilotSkills.push_back(cultureSpacer);
    pilotSkills.push_back(exosuit);
    pilotSkills.push_back(navigation);
    pilotSkills.push_back(techAstronautics);
    pilotSkills.push_back(techPostech);
    pilotSkills.push_back(vehicleAny);
    pilotSkills.push_back(vehicleSpace);

    package pilot;
    pilot.packageName = "Pilot";
    pilot.packageSkills = pilotSkills;

    trainingPackages.push_back(bountyHunter);
    trainingPackages.push_back(criminal);
    trainingPackages.push_back(pilot);

    vector<skill> conArtistSkills;
    conArtistSkills.push_back(cultureCriminal);
    conArtistSkills.push_back(cultureWorld);
    conArtistSkills.push_back(persuade);
    conArtistSkills.push_back(stealth);

    package conArtist;
    conArtist.packageName = "Con Artist";
    conArtist.packageSkills = conArtistSkills;

    vector<skill> gunneryCrewSkills;
    gunneryCrewSkills.push_back(combatGunnery);
    gunneryCrewSkills.push_back(cultureSpacer);
    gunneryCrewSkills.push_back(computer);
    gunneryCrewSkills.push_back(tactics);

    package gunneryCrew;
    gunneryCrew.packageName = "Gunnery Crew";
    gunneryCrew.packageSkills = gunneryCrewSkills;

    vector<skill> soldierSkills;
    soldierSkills.push_back(combatProjectile);
    soldierSkills.push_back(combatUnarmed);
    soldierSkills.push_back(cultureWorld);
    soldierSkills.push_back(tactics);

    package soldier;
    soldier.packageName = "Soldier";
    soldier.packageSkills = soldierSkills;

    backgroundPackages.push_back(conArtist);
    backgroundPackages.push_back(gunneryCrew);
    backgroundPackages.push_back(soldier);

}

vector<string> expert::GetPrimaryAttributes() {
    return primaryAttributes;
}

vector<expert::package> expert::GetBackgroundPackages() {
    return backgroundPackages;
}

vector<expert::package> expert::GetTrainingPackages() {
    return trainingPackages;
}

int expert::GetAttackBonus() {
    return attackBonus;
}

vector<expert::save> expert::GetSaves() {
    return saves;
}

int expert::GetHitDice() {
    return hitDice;
}