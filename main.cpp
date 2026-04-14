#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

struct Body {
    int age = 0;
    float height=0;
    float weight = 0;
    
    char Hbuffer[16] = "";
    char Wbuffer[16] = "";
    
    int genderActive = 0; // 0 for Male, 1 for Female
    bool ageEdit = false;
    bool heightEdit = false;
    bool weightEdit = false;

    float GetBMR() const {
        if (age <= 0 || height <= 0 || weight <= 0) return 0.0f;
        if (genderActive == 0) 
            return (10.0f * weight) + (6.25f * height) - (5.0f * age) + 5.0f;
        return (10.0f * weight) + (6.25f * height) - (5.0f * age) - 161.0f;
    }

    float GetTDEE() const { return GetBMR() * 1.4f; }
    float GetSugarGrams() const { return (GetTDEE() * 0.05f) / 4.0f; }
    float GetSugarTSP() const { return GetSugarGrams() / 4.0f; }
};
__attribute__((force_align_arg_pointer))
int main() {
    Body amar;

    snprintf(amar.Hbuffer, sizeof(amar.Hbuffer), "%.2f", amar.height);
    snprintf(amar.Wbuffer, sizeof(amar.Wbuffer), "%.2f", amar.weight);

    InitWindow(1280, 720, "Sugar Limit Calculator");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Q)) break;

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Sugar Limit", 300, 100, 30, WHITE);

        if (GuiValueBox({100, 200, 100, 60}, "Age", &amar.age, 0, 120, amar.ageEdit)) amar.ageEdit = !amar.ageEdit;
        if (GuiValueBoxFloat({100, 300, 100, 60}, "Height (cm)", amar.Hbuffer, &amar.height, amar.heightEdit)) amar.heightEdit = !amar.heightEdit;
        if (GuiValueBoxFloat({100, 400, 100, 60}, "Weight (kg)", amar.Wbuffer, &amar.weight, amar.weightEdit)) amar.weightEdit = !amar.weightEdit;
        
        GuiToggleGroup({100, 500, 100, 60}, "MALE;FEMALE", &amar.genderActive);

        float tdee = amar.GetTDEE();
        DrawText(TextFormat("Daily Calorie: %.2f cal", tdee), 400, 350, 30, RED);
        DrawText(TextFormat("Sugar Limit: %.2f grams", amar.GetSugarGrams()), 400, 380, 30, YELLOW);
        DrawText(TextFormat("Sugar Limit: %.2f tsp", amar.GetSugarTSP()), 400, 420, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}