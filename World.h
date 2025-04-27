#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class OrgWorld : public emp::World<Organism> {

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;

    public:

    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {
    }

  void Update() {
    double pointsPerUpdate = 0;

    emp::World<Organism>::Update();

    emp::vector<size_t> schedule1 = emp::GetPermutation(random, GetSize());
    emp::vector<size_t> schedule2 = emp::GetPermutation(random, GetSize());

    // Calls the process function for each organism
    CallProcesses(schedule1, pointsPerUpdate);

    // Checks conditions for reproduction and lets organisms move
    for (int i : schedule2){
        if(IsOccupied(i)){
            emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();

            // If offspring is made, place into non-empty box
            if (offspring){
                PlaceOffspring(offspring, i);
            }

            // Move non-grass organisms to random neighboring position, if occupied check if can be eaten
            if (pop[i]->SpeciesName() != "Grass"){
                MoveOrg(i);
            }
        }
    }
}

    // Removes organism from initial position and returns a pointer to the org
    emp::Ptr<Organism> ExtractOrganism(int orgPos){
        emp::Ptr<Organism> extracted_org = pop[orgPos];
        pop[orgPos] = nullptr;
        return extracted_org;
    }

    // Removes organism from initial position and deletes it
    void DeleteOrganism(int orgPos){
        emp::Ptr<Organism> extracted_org = pop[orgPos];
        pop[orgPos] = nullptr;
        delete(extracted_org);
    }

    bool EatSpecies (emp::Ptr<Organism> given_org, int position){
        // Check if org can eat species at occupied area
        if(given_org->SpeciesEat(pop[position])){
            DeleteOrganism(pop[position]);
            given_org->hasEaten = true;
            AddOrgAt(given_org, position);
            return true;
        }
        return false;
    }

    void CallProcesses (emp::vector<size_t> schedule, int points) {
        for (int i :schedule){
            if(IsOccupied(i)){
                pop[i]->Process(points);
    
                if (pop[i]->CheckShouldOrgDie()) {
                    DeleteOrganism(i);
                }
            }
        }
    }

    void PlaceOffspring(emp::Ptr<Organism> offspring, int parent_pos){
        emp::WorldPosition birth_pos = GetRandomNeighborPos(parent_pos);
        if (!IsOccupied(birth_pos)){
            AddOrgAt(offspring, birth_pos.GetIndex());
            }
        else{delete offspring;}
    }

    void MoveOrg(int pos) {
        emp::WorldPosition newPosition = GetRandomNeighborPos(pos);
        emp::Ptr<Organism> extracted_org = ExtractOrganism(pos);

        if (!IsOccupied(newPosition)){
            AddOrgAt(extracted_org, newPosition);
        }

        else {
            bool wasEaten = EatSpecies(extracted_org, newPosition.GetIndex());
            
            if (!wasEaten){
                AddOrgAt(extracted_org, pos);
            }
        }
    }

};
#endif