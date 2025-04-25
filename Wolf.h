#ifndef WOLF_H
#define WOLF_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class Wolf : public Organism {
    private:
        int age;

    public:
        Wolf(emp::Ptr<emp::Random> _random, double _points = 0.0, int _age=0)
            : Organism(_random, _points), age(0) {}

        std::string SpeciesName() const override {
            return "Wolf";
        }

        virtual bool SpeciesEat(Organism* other) override {
            if (other->SpeciesName() == "Deer") {
                points += 200;
                std::cout << "Wolf ate!" << std::endl;
                return true;
            }
            else {
                return false;
            }
        }

        emp::Ptr<Organism> CheckReproduction() override {
            if (points >= 2000){
                emp::Ptr<Wolf> wolfOffSpring = new Wolf(random, 0.0);
                wolfOffSpring->SetPoints(0);
                return wolfOffSpring;
            }
            return nullptr;
        }

        bool CheckShouldOrgDie() override {
            if (points <= -4000){
                return true;
            }
            return false;
        }

        void Process(double given_points) override {
            points += given_points;
            if (hasEaten == false){
                points -= 100;
            }
        }
};

#endif