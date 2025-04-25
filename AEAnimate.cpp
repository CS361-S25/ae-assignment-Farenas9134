#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"
#include "Grass.h"
#include "Deer.h"

emp::web::Document doc{"target"};

// Create random generator and world
emp::Random random_gen_2(5);
OrgWorld world{random_gen_2};

class AEAnimator : public emp::web::Animate {

    // arena width and height
    const int num_h_boxes = 20;
    const int num_w_boxes = 20;
    const double RECT_SIDE = 20;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::web::Canvas canvas{width, height, "canvas"};

    public:

    AEAnimator() {
        // shove canvas into the div
        // along with a control button
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        AddOrgs();
        
        world.Resize(num_w_boxes, num_h_boxes);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

        DrawSquares();

    }

    void DoFrame() override {
        canvas.Clear();
        world.Update();
        DrawSquares();
    }

    void DrawSquares() {
        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++){
            for (int y = 0; y < num_h_boxes; y++) {
                if (world.IsOccupied(org_num)) {
                    // Why are all my organisms just generic if one is a grass type and prints grass above?
                    std::string species = world[org_num].SpeciesName();
                    if (species == "Grass"){
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "black");
                    }
                    else{
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "purple", "black");
                    }
                } else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                }
                org_num++;
            }
        }
    }

    void AddOrgs() {
        Deer* deer_org = new Deer(&random_gen_2);
        Deer* deer_org2 = new Deer(&random_gen_2);
        Deer* deer_org3 = new Deer(&random_gen_2);
        Grass* grass_org = new Grass(&random_gen_2);
        Grass* grass_org2 = new Grass(&random_gen_2);
        
        world.AddOrgAt(deer_org, 0);
        world.AddOrgAt(deer_org2, 20);
        world.AddOrgAt(deer_org3, 80);
        world.AddOrgAt(grass_org, 50);
        world.AddOrgAt(grass_org2, 70);
    }

};



AEAnimator animator;

int main() {
    animator.Step();
}