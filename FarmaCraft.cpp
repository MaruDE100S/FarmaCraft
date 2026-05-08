#include "raylib.h"

int main() {
    InitWindow(800, 600, "FarmaCraft");
    SetTargetFPS(144);

    int clicks = 0;
    bool btnAction = false;
    gamestate gameState = GAME_STATE_MENU;
    bool winstate = false;

    Rectangle btn = { 350, 250, 100, 100 };

    Vector2 mousePoint = { 0.0f, 0.0f };

    InitAudioDevice();

    Music btnsound = LoadMusicStream("includes/sf/mockodmg1.mp3");
    Music music = LoadMusicStream("includes/aud/music.mp3");
    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        switch (gameState) {
            case GAME_STATE_MENU:
                
                
                break;
            case GAME_STATE_GAME:
                
                break;
            case GAME_STATE_WIN:
                
                break;
        }
        mousePoint = GetMousePosition();
        btnAction = false;

        UpdateMusicStream(music);

        if (CheckCollisionPointRec(mousePoint, btn)) {
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && clicks >= 100) {
                btnAction = true;
                winstate = true;
                clicks -= 100;
            }
        }

        

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            clicks++;
        }

        BeginDrawing();

        ClearBackground(GREEN);

        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, DARKGRAY);
        DrawText("Hello, World!", 10, 40, 20, WHITE);
        DrawText(TextFormat("Clicks: %d", clicks), 10, 70, 20, WHITE);
        DrawText("Naklikaj 100 razy aby wygrac!", 10, 100, 20, WHITE);

        DrawRectangleRec(btn, RED);

       if (winstate) {
                StopMusicStream(music);
                DrawText("You WIN", 10, 100, 20, RED);
                PlayMusicStream(btnsound);
                UpdateMusicStream(btnsound);
        }
        EndDrawing();
    }

    UnloadMusicStream(music);
    UnloadMusicStream(btnsound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
