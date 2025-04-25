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
    for (int i :schedule1){
        if(IsOccupied(i)){
            pop[i]->Process(pointsPerUpdate);
            std::vector<size_t> neighbors = GetValidNeighborOrgIDs(i);
            bool AlreadyAte = false;
            for (int j:neighbors){
                if (pop[i]->SpeciesEat(pop[j]) && AlreadyAte == false){
                    DeleteOrganism(j);
                    std::cout << "ATE THAT" << std::endl;
                    AlreadyAte = true;
                    pop[i]->hasEaten = true;
                }
            }

            if (AlreadyAte == false){
                pop[i]->hasEaten = false;
            }
                // Never set hasEaten back to false. Need to do that when org doesn't eat

            if (pop[i]->CheckShouldOrgDie()) {
                std::cout << "Org died" << std::endl;
                DeleteOrganism(i);
            }
        }
    }

    // Checks conditions for reproduction and lets organisms move
    for (int i : schedule2){
        if(IsOccupied(i)){
            emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();

            // If offspring is made, place into non-empty box
            if (offspring){
                std::cout << "Reproduction!" << std::endl;

                emp::WorldPosition birth_pos = GetRandomNeighborPos(i);
                if (!IsOccupied(birth_pos)){
                    AddOrgAt(offspring, birth_pos.GetIndex());
                }
                else{delete offspring;}
            }

            // Move organisms to random neighboring position, if occupied stay put
            if (pop[i]->SpeciesName() != "Grass"){
            emp::WorldPosition newPosition = GetRandomNeighborPos(i);
            emp::Ptr<Organism> extracted_org = ExtractOrganism(i);
            if (!IsOccupied(newPosition)){
                AddOrgAt(extracted_org, newPosition);
            }
            else {AddOrgAt(extracted_org, i);}
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

};
#endif