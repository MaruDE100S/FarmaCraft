#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

struct cps {
        float cpsTimer = 0.0f;
        int clicksThisSecond = 0;
        float currentCPS = 0.0f;
};

struct PlayerData {
        int apples = 0;
        int bananas = 0;
        int oranges = 0;
        int clicks = 0;
        bool banana_upgrade = false;
        bool orange_upgrade = false;
        bool tree_level_win = false;
        int rocks = 0;
        int coal = 0;
        int iron = 0;
        bool coal_upgrade = false;
        bool iron_upgrade = false;
        bool rocks_level_win = false;
        void saveGame() {
                std::fstream save_file("saves/save.txt", std::ios::out);
                save_file << apples << std::endl;
                save_file << bananas << std::endl;
                save_file << oranges << std::endl;
                save_file << clicks << std::endl;
                save_file << banana_upgrade << std::endl;
                save_file << orange_upgrade << std::endl;
                save_file << tree_level_win << std::endl;
                save_file << rocks << std::endl;
                save_file << coal << std::endl;
                save_file << iron << std::endl;
                save_file << coal_upgrade << std::endl;
                save_file << iron_upgrade << std::endl;
                save_file << rocks_level_win << std::endl;
                save_file.close();
        }
};

PlayerData loadGame() {
        PlayerData data;
        std::fstream open_file("saves/save.txt");
        if (open_file.is_open()) {
                open_file >> data.apples;
                open_file >> data.bananas;
                open_file >> data.oranges;
                open_file >> data.clicks;
                open_file >> data.banana_upgrade;
                open_file >> data.orange_upgrade;
                open_file >> data.tree_level_win;
                open_file >> data.rocks;
                open_file >> data.coal;
                open_file >> data.iron;
                open_file >> data.coal_upgrade;
                open_file >> data.iron_upgrade;
                open_file >> data.rocks_level_win;
                open_file.close();
        } else {
                std::cout << "Nie znaleziono pliku save. Wartosci ustawiane na 0." << std::endl;
        }
        return data;
}

int main () {
        InitWindow(800, 600, "FarmaCraft");
        SetTargetFPS(144);

        InitAudioDevice();

        Music music = LoadMusicStream("includes/aud/King Has Returned.mp3");
        Sound click = LoadSound("includes/sf/click.mp3");
        PlayMusicStream(music);

        Texture2D sfx_button = LoadTexture("includes/sf/click_sound_remove.png");
        Texture2D sfx_button_muted = LoadTexture("includes/sf/click_sound_remove_muted.png");
        bool sfx_muted = false;

        float volume = 0.5f;
        SetMusicVolume(music, volume);

        float sfx_volume = 1.0f;
        SetSoundVolume(click, sfx_volume);

        // tree level
        Texture2D appleTree = LoadTexture("includes/tetures/appletree.png");
        Texture2D bananaTree = LoadTexture("includes/tetures/bananatree.png");
        Texture2D orangeTree = LoadTexture("includes/tetures/orangetree.png");

        Texture2D win = LoadTexture("includes/tetures/win_button.png");
        Texture2D banana_upgrade_texture = LoadTexture("includes/tetures/banana_button.png");
        Texture2D orange_upgrade_texture = LoadTexture("includes/tetures/orange_button.png");

        //rock level
        Texture2D rock = LoadTexture("includes/tetures/rock.png");
        Texture2D coal_mine = LoadTexture("includes/tetures/coal_mine.png");
        Texture2D iron_mine = LoadTexture("includes/tetures/iron_mine.png");

        Texture2D coal_upgrade_texture = LoadTexture("includes/tetures/coal_button.png");
        Texture2D iron_upgrade_texture = LoadTexture("includes/tetures/iron_button.png");

        Vector2 mousePoint = { 0.0f, 0.0f };

        PlayerData data;

        data = loadGame();

        cps cps;

        Rectangle btn_sfx = { 115, 10, 20, 20 };

        Rectangle btn_to_win = { GetScreenWidth() / 2 - 90, 120, 180, 100 };
        Rectangle btn_banana_upgrade = { 100, 425, 190, 80};
        Rectangle btn_orange_upgrade = { 520, 425, 190, 80};

        Rectangle btn_to_win_rock = { GetScreenWidth() / 2 - 90, 120, 180, 100};
        Rectangle btn_coal_upgrade = { 100, 425, 190, 80};
        Rectangle btn_iron_upgrade = { 520, 425, 190, 80};
        
        enum gamestate {
                GAME_STATE_MENU,
                GAME_STATE_CREDIT,
                GAME_STATE_STATS,
                GAME_STATE_SHOP,
                GAME_STATE_GAME,
                GAME_STATE_GAME_LVL2,
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
                "Malutki",
                "Mati FL Studio",
                "Gluilb",
                "666CENSORED999",
                "TouchPad",
                "Cygan",
                "Atomic",
                "Luca$$h",
                "Kozlowska"
        };

        std::vector<std::string> music_dev = {
                "Mati FL Studio"
        };

        std::cout << "#LoveAngelika" << std::endl;

        gamestate gameState = GAME_STATE_MENU;
        gamestate previousState = GAME_STATE_MENU;

        while (!WindowShouldClose()) {
                // LOGIC BLOCK
                UpdateMusicStream(music);
                mousePoint = GetMousePosition();
                cps.cpsTimer += GetFrameTime();
                if (cps.cpsTimer >= 1.0f) {
                        cps.currentCPS = (float)cps.clicksThisSecond / cps.cpsTimer;
                        cps.clicksThisSecond = 0;
                        cps.cpsTimer = 0.0f;
                }
                
                switch (gameState) {
                        case GAME_STATE_MENU:
                                if (IsKeyPressed(KEY_ENTER)) {
                                        gameState = GAME_STATE_GAME;
                                }
                                if (data.tree_level_win) {
                                        if (IsKeyPressed(KEY_F3)) {
                                                gameState = GAME_STATE_GAME_LVL2;
                                        }
                                }
                                if (IsKeyPressed(KEY_F2)) {
                                        gameState = GAME_STATE_CREDIT;
                                }
                                break;
                        case GAME_STATE_GAME:
                                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                        data.apples++;
                                        data.clicks++;
                                        cps.clicksThisSecond++;
                                        PlaySound(click);
                                }
                        if (data.banana_upgrade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || data.banana_upgrade && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                data.bananas++;
                        }
                        if (data.orange_upgrade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || data.orange_upgrade && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                data.oranges++;
                        }
                        if (IsKeyPressed(KEY_SPACE)) {
                                gameState = GAME_STATE_MENU;
                        }
                        if (IsKeyPressed(KEY_B)) {
                                previousState = GAME_STATE_GAME;
                                gameState = GAME_STATE_SHOP;
                        }
                        if (IsKeyPressed(KEY_S)) {
                                previousState = GAME_STATE_GAME;
                                gameState = GAME_STATE_STATS;
                        }
                        break;
                        case GAME_STATE_CREDIT:
                                if (IsKeyPressed(KEY_ENTER)) {
                                        gameState = GAME_STATE_MENU;
                                }
                                break;
                        case GAME_STATE_GAME_LVL2:
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                data.rocks++;
                                data.clicks++;
                                cps.clicksThisSecond++;
                                PlaySound(click);
                        }
                        if (data.coal_upgrade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || data.coal_upgrade && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                data.coal++;
                        }
                        if (data.iron_upgrade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || data.iron_upgrade && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                data.iron++;
                        }
                        if (IsKeyPressed(KEY_B)) {
                                previousState = GAME_STATE_GAME_LVL2;
                                gameState = GAME_STATE_SHOP;
                        }
                        if (IsKeyPressed(KEY_S)) {
                                previousState = GAME_STATE_GAME_LVL2;
                                gameState = GAME_STATE_STATS;
                        }
                        if (IsKeyPressed(KEY_SPACE)) {
                                gameState = GAME_STATE_MENU;
                        }
                        break;
                        case GAME_STATE_SHOP:
                                if (previousState == GAME_STATE_GAME) {
                                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, btn_banana_upgrade) && !data.banana_upgrade && data.apples >= 250) {
                                                data.banana_upgrade = true;
                                                data.apples -= 250;
                                        }
                                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, btn_orange_upgrade) && !data.orange_upgrade && data.bananas >= 400) {
                                                data.orange_upgrade = true;
                                                data.bananas -= 400;
                                        }
                                        if (CheckCollisionPointRec(mousePoint, btn_to_win)) {
                                                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && data.apples >= 1000 && data.bananas >= 1000 && data.oranges >= 1000) {
                                                        data.tree_level_win = true;
                                                        data.apples -= 1000;
                                                        data.bananas -= 1000;
                                                        data.oranges -= 1000;
                                                        gameState = GAME_STATE_WIN;
                                                }
                                        }
                                } else if (previousState == GAME_STATE_GAME_LVL2) {
                                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, btn_coal_upgrade) && !data.coal_upgrade && data.rocks >= 250) {
                                        data.coal_upgrade = true;
                                        data.rocks -= 2000;
                                        }
                                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, btn_iron_upgrade) && !data.iron_upgrade && data.coal >= 400) {
                                                data.iron_upgrade = true;
                                                data.coal -= 6000;
                                        }
                                        if (CheckCollisionPointRec(mousePoint, btn_to_win_rock)) {
                                                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && data.rocks >= 15000 && data.coal >= 12000 && data.iron >= 10000) {
                                                        data.rocks_level_win = true;
                                                        data.rocks -= 15000;
                                                        data.coal -= 12000;
                                                        data.iron -= 10000;
                                                        gameState = GAME_STATE_WIN;
                                                }
                                        }         
                                }
                                if (IsKeyPressed(KEY_B)) {
                                        gameState = previousState;
                                } 
                                break;
                        case GAME_STATE_STATS:
                                if (IsKeyPressed(KEY_S)) {
                                        gameState = previousState;
                                }
                                break;
                        case GAME_STATE_WIN:
                                if (IsKeyPressed(KEY_ENTER)) {
                                        gameState = GAME_STATE_MENU;
                                }
                                break;
                        default: 
                                gameState = GAME_STATE_GAME;
                                break;
                }
                
                if (CheckCollisionPointRec(mousePoint, btn_sfx)) {
                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                                sfx_muted = !sfx_muted;
                                if (sfx_muted) {
                                        sfx_volume = 0.0f;
                                } else {
                                        sfx_volume = 1.0f;
                                }
                                SetSoundVolume(click, sfx_volume);
                        }
                }

                if (IsKeyDown(KEY_UP)) {
                        volume += 0.01f;
                        if (volume > 1.0f) volume = 1.0f; 
                        SetMusicVolume(music, volume);
                } else if (IsKeyDown(KEY_DOWN)) {
                        volume -= 0.01f;
                        if (volume < 0.0f) volume = 0.0f;
                        SetMusicVolume(music, volume);
                };
                // -----------------------------------------------------------
                // DRAWING BLOCK
                BeginDrawing();

                DrawRectangle(140, 10, 100, 20, LIGHTGRAY);
                DrawRectangleLines(140, 10, 100, 20, BLACK);
                DrawRectangle((int)(140 + volume*100 - 5), 8, 10, 26, DARKGRAY);
                DrawText("UP/DOWN dla glosnosci", 140, 40, 8, BLACK);
                DrawRectangleRec(btn_sfx, RAYWHITE);
                if (sfx_muted) {
                        DrawTexture(sfx_button_muted, 115, 10, WHITE);
                } else {
                        DrawTexture(sfx_button, 115, 10, WHITE);
                }

                switch (gameState) {
                        case GAME_STATE_MENU:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("FarmaCraft", GetScreenWidth() / 2 - MeasureText("FarmaCraft", 20) / 2, 280, 20, BLACK);
                                DrawText("Nacisnij Enter aby zaczac", GetScreenWidth() / 2 - MeasureText("Nacisnij Enter aby zaczac", 20) / 2, 310, 20, BLACK);
                                DrawText("Nacisnij F2 aby zobaczyc tworcow", GetScreenWidth() / 2 - MeasureText("Nacisnij F2 aby zobaczyc tworcow", 20) / 2, 340, 20, BLACK);
                                if (data.tree_level_win) {
                                        DrawText("Nacisnij F3 aby wejsc na nastepny poziom", GetScreenWidth() / 2 - MeasureText("Nacisnij F3 aby wejsc na nastepny poziom", 20) / 2, 370, 20, BLACK);
                                }
                                break;
                        case GAME_STATE_CREDIT:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("Tworcy: ", 10, 40, 20, BLACK);
                                for (int i = 0; i < developers.size(); i++) {
                                        DrawText(developers[i].c_str(), 10, 70 + i * 30, 20, BLACK);
                                }
                                DrawText("Testerowie: ", 300, 40, 20, BLACK);
                                for (int i = 0; i < testers.size(); i++) {
                                        if (testers[i] == "Mati FL Studio") {
                                                DrawText(testers[i].c_str(), 300, 70 + i * 30, 20, YELLOW);
                                        } else {
                                                DrawText(testers[i].c_str(), 300, 70 + i * 30, 20, BLACK);
                                        }
                                }
                                DrawText("Muzyka: ", 550, 40, 20, BLACK);
                                for (int i = 0; i < music_dev.size(); i++) {
                                        DrawText(music_dev[i].c_str(), 550, 70 + i * 30, 20, BLACK);
                                }
                                DrawText("Nacisnij Enter aby wrocic do menu", 10, 400, 20, BLACK);
                                break;
                        case GAME_STATE_GAME:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText(TextFormat("CPS: %.1f", cps.currentCPS), GetScreenWidth() / 2 - MeasureText(TextFormat("CPS: %.1f", cps.currentCPS), 20) / 2 - 60, 40, 20, BLACK);     
                                DrawText(TextFormat("Apples: %d", data.apples), 10, 40, 20, BLACK);
                                DrawText("Nacisnij B aby wejsc do sklepu", 420, 30, 20, BLACK);
                                DrawText("Nacisnij S aby zobaczyc statystyki", 420, 60, 20, BLACK);
                                DrawTexture(appleTree, 300, 135, WHITE);
                                if (data.banana_upgrade && !data.orange_upgrade) { 
                                        DrawText(TextFormat("Bananas: %d", data.bananas), 10, 70, 20, BLACK);
                                        DrawTexture(bananaTree, 10, 135, WHITE);
                                }
                                if (data.banana_upgrade && data.orange_upgrade) {
                                        DrawText(TextFormat("Bananas: %d", data.bananas), 10, 70, 20, BLACK);
                                        DrawText(TextFormat("Oranges: %d", data.oranges), 10, 100, 20, BLACK);
                                        DrawTexture(bananaTree, 10, 135, WHITE);
                                        DrawTexture(orangeTree, 580, 135, WHITE);
                                }
                                DrawText("Nacisnij Space aby wrocic do menu", 420, 10, 10, BLACK);     
                                break;
                        case GAME_STATE_GAME_LVL2:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText(TextFormat("CPS: %.1f", cps.currentCPS), GetScreenWidth() / 2 - MeasureText(TextFormat("CPS: %.1f", cps.currentCPS), 20) / 2 - 60, 40, 20, BLACK);     
                                DrawText(TextFormat("Rocks: %d", data.rocks), 10, 40, 20, BLACK);
                                DrawText("Nacisnij B aby wejsc do sklepu", 420, 30, 20, BLACK);
                                DrawText("Nacisnij S aby zobaczyc statystyki", 420, 60, 20, BLACK);
                                DrawTexture(rock, 270, 135, WHITE);
                                if (data.coal_upgrade && !data.iron_upgrade) { 
                                        DrawText(TextFormat("Coal: %d", data.coal), 10, 70, 20, BLACK);
                                        DrawTexture(coal_mine, 10, 135, WHITE);
                                }
                                if (data.coal_upgrade && data.iron_upgrade) {
                                        DrawText(TextFormat("Coal: %d", data.coal), 10, 70, 20, BLACK);
                                        DrawText(TextFormat("Iron: %d", data.iron), 10, 100, 20, BLACK);
                                        DrawTexture(coal_mine, 10, 215, WHITE);
                                        DrawTexture(iron_mine, 550, 215, WHITE);
                                }
                                DrawText("Nacisnij Space aby wrocic do menu", 420, 10, 10, BLACK);       
                                break;
                        case GAME_STATE_SHOP:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);   
                                DrawText("Sklep", GetScreenWidth() / 2 - MeasureText("Sklep", 20) / 2, 100, 20, BLACK);
                                if (previousState == GAME_STATE_GAME) {
                                        DrawText(TextFormat("Apples: %d", data.apples), 10, 40, 20, BLACK);
                                        if (data.banana_upgrade) {
                                                DrawText(TextFormat("Bananas: %d", data.bananas), 10, 70, 20, BLACK);
                                        }
                                        if (data.orange_upgrade) {
                                                DrawText(TextFormat("Oranges: %d", data.oranges), 10, 100, 20, BLACK);
                                        }
                                        
                                        if (!data.banana_upgrade) {
                                                DrawRectangleRec(btn_banana_upgrade, RAYWHITE);
                                                DrawTexture(banana_upgrade_texture, 100, 425, WHITE);
                                                DrawText("250 apples to open banana tree", 20, 400, 20, BLACK);
                                        }
                                        if (!data.orange_upgrade) {
                                                DrawRectangleRec(btn_orange_upgrade, RAYWHITE);
                                                DrawTexture(orange_upgrade_texture, 520, 425, WHITE);
                                                DrawText("400 bananas to open orange tree", 430, 400, 20, BLACK);
                                        }
                                        if (!data.tree_level_win) {
                                                DrawRectangleRec(btn_to_win, RAYWHITE);
                                                DrawTexture(win, GetScreenWidth() / 2 - 90, 120, WHITE);
                                                DrawText("1000 apples, 1000 bananas, 1000 oranges aby wygrac", GetScreenWidth() / 2 - MeasureText("1000 apples, 1000 bananas, 1000 oranges aby wygrac", 20) / 2, 240, 20, BLACK);
                                        }
                                        
                                } 
                                if (previousState == GAME_STATE_GAME_LVL2) {
                                        DrawRectangleRec(btn_to_win_rock, RAYWHITE);
                                        DrawTexture(win, GetScreenWidth() / 2 - 90, 120, WHITE);
                                        DrawText("15000 rocks, 12000 coal, 10000 iron aby wygrac", GetScreenWidth() / 2 - MeasureText("1000 apples, 1000 bananas, 1000 oranges aby wygrac", 20) / 2, 240, 20, BLACK);
                                        if (!data.coal_upgrade) {
                                                DrawRectangleRec(btn_coal_upgrade, RAYWHITE);
                                                DrawTexture(coal_upgrade_texture, 100, 425, WHITE);
                                                DrawText("2000 rocks to open coal mine", 20, 400, 20, BLACK);
                                        }
                                        if (!data.iron_upgrade) {
                                                DrawRectangleRec(btn_iron_upgrade, RAYWHITE);
                                                DrawTexture(iron_upgrade_texture, 520, 425, WHITE);
                                                DrawText("6000 coal to open iron mine", 430, 400, 20, BLACK);
                                        }
                                }
                                DrawText("Nacisnij B aby wrocic do gry", GetScreenWidth() / 2 - MeasureText("Nacisnij B aby wrocic do gry", 20) / 2, 310, 20, BLACK);
                                break;
                        case GAME_STATE_STATS:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("Statystyki", GetScreenWidth() / 2 - MeasureText("Statystyki", 20) / 2, 280, 20, BLACK);
                                DrawText("Nacisnij S aby wrocic do gry", GetScreenWidth() / 2 - MeasureText("Nacisnij S aby wrocic do gry", 20) / 2 - 60, 310, 20, BLACK);
                                DrawText(TextFormat("Apples: %d", data.apples), 10, 40, 20, BLACK);
                                DrawText(TextFormat("Clicks: %d", data.clicks), 10, 70, 20, BLACK);
                                DrawText(TextFormat("Bananas: %d", data.bananas), 300, 40, 20, BLACK);
                                DrawText(TextFormat("Oranges: %d", data.oranges), 600, 40, 20, BLACK);
                                DrawText(TextFormat("Rocks: %d", data.rocks), 10, 100, 20, BLACK);
                                DrawText(TextFormat("Coal: %d", data.coal), 10, 130, 20, BLACK);
                                DrawText(TextFormat("Iron: %d", data.iron), 10, 160, 20, BLACK);
                                break;
                        case GAME_STATE_WIN:
                                ClearBackground(GREEN);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("Wygrales!", GetScreenWidth() / 2 - MeasureText("Wygrales!", 20) / 2, 280, 20, BLACK);
                                if (data.tree_level_win && !data.rocks_level_win) {
                                        DrawText("Teraz z menu mozesz wejsc na nastepny poziom!", GetScreenWidth() / 2 - MeasureText("Teraz z menu mozesz wejsc na nastepny poziom!", 20) / 2, 310, 20, BLACK);
                                } else
                                if (data.rocks_level_win) {
                                        DrawText("Narazie to tyle z gry, dziekuje za gre!", GetScreenWidth() / 2 - MeasureText("Narazie to tyle z gry, dziekuje za gre!", 20) / 2, 310, 20, BLACK);
                                }
                                DrawText("Nacisnij Enter aby wrocic do menu", GetScreenWidth() / 2 - MeasureText("Nacisnij Enter aby wrocic do menu", 20) / 2, 340, 20, BLACK);
                                break;
                        default:
                                gameState = GAME_STATE_MENU;
                                break;
                }
                EndDrawing();
                // --------------------------------------------------------------------------
        }

        // CLEAR BLOCK
        
        data.saveGame();
      
        UnloadSound(click);
        UnloadMusicStream(music);
        CloseAudioDevice();

        UnloadTexture(sfx_button);
        UnloadTexture(sfx_button_muted);
        // trees
        UnloadTexture(appleTree);
        UnloadTexture(bananaTree);
        UnloadTexture(orangeTree);
        // buttons
        UnloadTexture(win);
        UnloadTexture(banana_upgrade_texture);
        UnloadTexture(orange_upgrade_texture);
        // rocks
        UnloadTexture(rock);
        UnloadTexture(coal_mine);
        UnloadTexture(iron_mine);
        // rock_but
        UnloadTexture(coal_upgrade_texture);
        UnloadTexture(iron_upgrade_texture);
        CloseWindow();
        return 0;
}