#include <raylib.h>
#include <vector>
#include <string>
#include <fstream>



int main () {
        InitWindow(800, 600, "FarmaCraft");
        SetTargetFPS(144);

        InitAudioDevice();

        Music music = LoadMusicStream("includes/aud/King Has Returned.mp3");
        PlayMusicStream(music);

        Vector2 mousePoint = { 0.0f, 0.0f };
        int apples = 0;
        int bananas = 0;
        int oranges = 0;
        int clicks = 0;

        bool banana_upgrade = false;
        bool orange_upgrade = false;
      
        Rectangle btn_to_win = { GetScreenWidth() / 2 - MeasureText("1000 apples", 20) / 2, 130, 100, 100 };
        Rectangle btn_banana_upgrade = { 50, 130, 120, 80};
        Rectangle btn_orange_upgrade = { 50, 200, 120, 80};
        
        enum gamestate {
                GAME_STATE_MENU,
                GAME_STATE_CREDIT,
                GAME_STATE_STATS,
                GAME_STATE_SHOP,
                GAME_STATE_GAME,
                GAME_STATE_WIN
        };

        std::vector<std::string> developers = {
                "MaruDE",
                "Mati FL Studio"
        };

        std::vector<std::string> testers = {
                "Kaffe",
                "Avmia",
                "Adanoo",
                "Malutki"
        };

        std::vector<std::string> music_dev = {
                "Mati FL Studio"
        };

        

        gamestate gameState = GAME_STATE_MENU;

        while (!WindowShouldClose()) {
                UpdateMusicStream(music);
                mousePoint = GetMousePosition();
                
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                        apples++;
                        clicks++;
                }
                if (banana_upgrade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || banana_upgrade && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                        bananas++;
                        clicks++;
                }
                if (orange_upgrade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || orange_upgrade && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                        oranges++;
                        clicks++;
                }
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, btn_banana_upgrade) && !banana_upgrade && apples >= 250) {
                        banana_upgrade = true;
                        apples -= 250;
                }
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, btn_orange_upgrade) && !orange_upgrade && bananas >= 400) {
                        orange_upgrade = true;
                        bananas -= 400;
                }
                switch (gameState) {
                        case GAME_STATE_MENU:
                                ClearBackground(RAYWHITE);
                                BeginDrawing();
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("FarmaCraft", GetScreenWidth() / 2 - MeasureText("FarmaCraft", 20) / 2, 280, 20, BLACK);
                                DrawText("Nacisnij Enter aby zaczac", GetScreenWidth() / 2 - MeasureText("Nacisnij Enter aby zaczac", 20) / 2, 310, 20, BLACK);
                                DrawText("Nacisnij F2 aby zobaczyc tworcow", GetScreenWidth() / 2 - MeasureText("Nacisnij F2 aby zobaczyc tworcow", 20) / 2, 340, 20, BLACK);
                                EndDrawing();
                                if (IsKeyPressed(KEY_ENTER)) {
                                        gameState = GAME_STATE_GAME;
                                }
                                if (IsKeyPressed(KEY_F2)) {
                                        gameState = GAME_STATE_CREDIT;
                                }
                                break;
                        case GAME_STATE_CREDIT:
                                ClearBackground(RAYWHITE);
                                BeginDrawing();
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("Tworcy: ", 10, 40, 20, BLACK);
                                for (int i = 0; i < developers.size(); i++) {
                                        DrawText(developers[i].c_str(), 10, 70 + i * 30, 20, BLACK);
                                }
                                DrawText("Testerowie: ", 300, 40, 20, BLACK);
                                for (int i = 0; i < testers.size(); i++) {
                                        DrawText(testers[i].c_str(), 300, 70 + i * 30, 20, BLACK);
                                }
                                DrawText("Muzyka: ", 550, 40, 20, BLACK);
                                for (int i = 0; i < music_dev.size(); i++) {
                                        DrawText(music_dev[i].c_str(), 550, 70 + i * 30, 20, BLACK);
                                }
                                DrawText("Nacisnij Enter aby wrocic do menu", 10, 340, 20, BLACK);
                                EndDrawing();
                                if (IsKeyPressed(KEY_ENTER)) {
                                        gameState = GAME_STATE_MENU;
                                }
                                break;
                        case GAME_STATE_GAME:
                                ClearBackground(RAYWHITE);
                                BeginDrawing();
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText(TextFormat("Apples: %d", apples), 10, 40, 20, BLACK);
                                if (!banana_upgrade && !orange_upgrade) {
                                        DrawText("Nacisnij B aby wejsc do sklepu", 10, 70, 20, BLACK);
                                        DrawText("Nacisnij S aby zobaczyc statystyki", 10, 100, 20, BLACK);
                                }
                                if (banana_upgrade && !orange_upgrade) { 
                                        DrawText(TextFormat("Bananas: %d", bananas), 10, 70, 20, BLACK);
                                        DrawText("Nacisnij B aby wejsc do sklepu", 10, 100, 20, BLACK);
                                        DrawText("Nacisnij S aby zobaczyc statystyki", 10, 130, 20, BLACK);
                                }
                                if (banana_upgrade && orange_upgrade) {
                                        DrawText(TextFormat("Bananas: %d", bananas), 10, 70, 20, BLACK);
                                        DrawText(TextFormat("Oranges: %d", oranges), 10, 100, 20, BLACK);
                                        DrawText("Nacisnij B aby wejsc do sklepu", 10, 130, 20, BLACK);
                                        DrawText("Nacisnij S aby zobaczyc statystyki", 10, 160, 20, BLACK);
                                }
                                
                                EndDrawing();
                                if (IsKeyPressed(KEY_B)) {
                                        gameState = GAME_STATE_SHOP;
                                }
                                if (IsKeyPressed(KEY_S)) {
                                        gameState = GAME_STATE_STATS;
                                }
                                
                                break;
                        case GAME_STATE_SHOP:
                                ClearBackground(RAYWHITE);
                                BeginDrawing();
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText(TextFormat("Apples: %d", apples), 10, 40, 20, BLACK);
                                if (banana_upgrade) {
                                        DrawText(TextFormat("Bananas: %d", bananas), 10, 70, 20, BLACK);
                                }
                                if (orange_upgrade) {
                                        DrawText(TextFormat("Oranges: %d", oranges), 10, 100, 20, BLACK);
                                }
                                DrawText("Sklep", GetScreenWidth() / 2 - MeasureText("Sklep", 20) / 2, 100, 20, BLACK);
                                if (!banana_upgrade) {
                                        DrawRectangleRec(btn_banana_upgrade, YELLOW);
                                        DrawText("250 apples to open banana tree", 50, 140, 20, BLACK);
                                }
                                if (!orange_upgrade) {
                                        DrawRectangleRec(btn_orange_upgrade, ORANGE);
                                        DrawText("400 bananas to open orange tree", 50, 170, 20, BLACK);
                                }
                                DrawRectangleRec(btn_to_win, RED);
                                DrawText("1000 apples, 1000 bananas, 1000 oranges aby wygrac", GetScreenWidth() / 2 - MeasureText("1000 apples, 1000 bananas, 1000 oranges aby wygrac", 20) / 2, 240, 20, BLACK);
                                DrawText("Nacisnij B aby wrocic do gry", GetScreenWidth() / 2 - MeasureText("Nacisnij B aby wrocic do gry", 20) / 2, 310, 20, BLACK);
                                EndDrawing();
                                if (IsKeyPressed(KEY_B)) {
                                        gameState = GAME_STATE_GAME;
                                }
                                if (CheckCollisionPointRec(mousePoint, btn_to_win)) {
                                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && apples >= 1000 && bananas >= 1000 && oranges >= 1000) {
                                                apples -= 1000;
                                                gameState = GAME_STATE_WIN;
                                        }
                                }
                                break;
                        case GAME_STATE_STATS:
                                ClearBackground(RAYWHITE);
                                BeginDrawing();
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("Statystyki", GetScreenWidth() / 2 - MeasureText("Statystyki", 20) / 2, 280, 20, BLACK);
                                DrawText("Nacisnij S aby wrocic do gry", GetScreenWidth() / 2 - MeasureText("Nacisnij S aby wrocic do gry", 20) / 2, 310, 20, BLACK);
                                DrawText(TextFormat("Apples: %d", apples), 10, 40, 20, BLACK);
                                DrawText(TextFormat("Clicks: %d", clicks), 10, 70, 20, BLACK);
                                EndDrawing();
                                if (IsKeyPressed(KEY_S)) {
                                        gameState = GAME_STATE_GAME;
                                }
                                break;
                        case GAME_STATE_WIN:
                                ClearBackground(GREEN);
                                BeginDrawing();
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("Wygrales!", GetScreenWidth() / 2 - MeasureText("Wygrales!", 20) / 2, 280, 20, BLACK);
                                DrawText("Nacisnij Enter aby wrocic do menu", GetScreenWidth() / 2 - MeasureText("Nacisnij Enter aby wrocic do menu", 20) / 2, 310, 20, BLACK);
                                EndDrawing();
                                if (IsKeyPressed(KEY_ENTER)) {
                                        gameState = GAME_STATE_MENU;
                                }
                                break;
                }
        }
        
        std::fstream save_file("saves/save.json");
        save_file << "{\"apples\": " << apples << ",\n";
        save_file << "\"clicks\": " << clicks << "}";
        save_file.close();
        UnloadMusicStream(music);
        CloseAudioDevice();
        CloseWindow();
        return 0;
}
