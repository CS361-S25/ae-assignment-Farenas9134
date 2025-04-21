#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"
#include "Grass.h"

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

        Organism* new_org = new Organism(&random_gen_2);
        Grass* grass_org = new Grass(&random_gen_2);
        std::cout << "Organism grass_org is "<< grass_org->SpeciesName() << std::endl;
        world.Inject(*grass_org);
        std::cout << "Organism grass_org is "<< grass_org->SpeciesName() << std::endl;
        world.Inject(*new_org);
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
                    std::string species = world[org_num].SpeciesName();
                    std::cout << "Organism at position " << org_num << " is a " << species << std::endl;
                    if (species == "Grass"){
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "black");
                    }
                    else{
                        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                    }
                } else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                }
                org_num++;
            }
        }
    }

};

AEAnimator animator;

int main() {
    animator.Step();
}