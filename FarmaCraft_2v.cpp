#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>



int main () {
        InitWindow(800, 600, "FarmaCraft");
        SetTargetFPS(144);

        InitAudioDevice();

        Music music = LoadMusicStream("includes/aud/King Has Returned.mp3");
        Sound click = LoadSound("includes/sf/click.mp3");
        PlayMusicStream(music);

        float volume = 0.5f;
        SetMusicVolume(music, volume);

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

        std::fstream open_file("saves/save.txt");
        if (open_file.is_open()) {
                open_file >> apples;
                open_file >> bananas;
                open_file >> oranges;
                open_file >> clicks;
                open_file >> banana_upgrade;
                open_file >> orange_upgrade;
                open_file >> tree_level_win;
                open_file >> rocks;
                open_file >> coal;
                open_file >> iron;
                open_file >> coal_upgrade;
                open_file >> iron_upgrade;
                open_file >> rocks_level_win;
                open_file.close();
        } else {
                std::cout << "Nie znaleziono pliku save. Wartosci ustawiane na 0." << std::endl;
        }
        
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

        

        gamestate gameState = GAME_STATE_MENU;

        std::cout << "#LoveAngelika" << std::endl;

        while (!WindowShouldClose()) {
                UpdateMusicStream(music);
                mousePoint = GetMousePosition();

                if (!tree_level_win) {
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                apples++;
                                clicks++;
                                PlaySound(click);
                        }
                        if (banana_upgrade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || banana_upgrade && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                bananas++;
                        }
                        if (orange_upgrade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || orange_upgrade && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                oranges++;
                        }
                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, btn_banana_upgrade) && !banana_upgrade && apples >= 250) {
                                banana_upgrade = true;
                                apples -= 250;
                        }
                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, btn_orange_upgrade) && !orange_upgrade && bananas >= 400) {
                                orange_upgrade = true;
                                bananas -= 400;
                        }
                } else {
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                rocks++;
                                clicks++;
                                PlaySound(click);
                        }
                        if (coal_upgrade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || coal_upgrade && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                coal++;
                        }
                        if (iron_upgrade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || iron_upgrade && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                iron++;
                        }
                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, btn_coal_upgrade) && !coal_upgrade && rocks >= 250) {
                                coal_upgrade = true;
                                rocks -= 2000;
                        }
                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, btn_iron_upgrade) && !iron_upgrade && coal >= 400) {
                                iron_upgrade = true;
                                coal -= 6000;
                        }
                }
                
                

                if (IsKeyDown(KEY_UP)) {
                        volume += 0.05f;
                        if (volume > 1.0f) volume = 1.0f; 
                        SetMusicVolume(music, volume);
                } else if (IsKeyDown(KEY_DOWN)) {
                        volume -= 0.05f;
                        if (volume < 0.0f) volume = 0.0f;
                        SetMusicVolume(music, volume);
                };

                BeginDrawing();

                DrawRectangle(140, 10, 100, 20, LIGHTGRAY);
                DrawRectangleLines(140, 10, 100, 20, BLACK);
                DrawRectangle((int)(140 + volume*100 - 5), 8, 10, 26, DARKGRAY);
                DrawText("UP/DOWN dla glosnosci", 140, 40, 8, BLACK);

                switch (gameState) {
                        case GAME_STATE_MENU:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("FarmaCraft", GetScreenWidth() / 2 - MeasureText("FarmaCraft", 20) / 2, 280, 20, BLACK);
                                DrawText("Nacisnij Enter aby zaczac", GetScreenWidth() / 2 - MeasureText("Nacisnij Enter aby zaczac", 20) / 2, 310, 20, BLACK);
                                DrawText("Nacisnij F2 aby zobaczyc tworcow", GetScreenWidth() / 2 - MeasureText("Nacisnij F2 aby zobaczyc tworcow", 20) / 2, 340, 20, BLACK);
                                if (IsKeyPressed(KEY_ENTER)) {
                                        gameState = GAME_STATE_GAME;
                                }
                                if (tree_level_win) {
                                        DrawText("Nacisnij F3 aby wejsc na nastepny poziom", GetScreenWidth() / 2 - MeasureText("Nacisnij F3 aby wejsc na nastepny poziom", 20) / 2, 370, 20, BLACK);
                                        if (IsKeyPressed(KEY_F3)) {
                                                gameState = GAME_STATE_GAME_LVL2;
                                        }
                                }
                                if (IsKeyPressed(KEY_F2)) {
                                        gameState = GAME_STATE_CREDIT;
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
                                if (IsKeyPressed(KEY_ENTER)) {
                                        gameState = GAME_STATE_MENU;
                                }
                                break;
                        case GAME_STATE_GAME:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText(TextFormat("Apples: %d", apples), 10, 40, 20, BLACK);
                                DrawText("Nacisnij B aby wejsc do sklepu", 420, 30, 20, BLACK);
                                DrawText("Nacisnij S aby zobaczyc statystyki", 420, 60, 20, BLACK);
                                DrawTexture(appleTree, 300, 135, WHITE);
                                if (banana_upgrade && !orange_upgrade) { 
                                        DrawText(TextFormat("Bananas: %d", bananas), 10, 70, 20, BLACK);
                                        DrawTexture(bananaTree, 10, 135, WHITE);
                                }
                                if (banana_upgrade && orange_upgrade) {
                                        DrawText(TextFormat("Bananas: %d", bananas), 10, 70, 20, BLACK);
                                        DrawText(TextFormat("Oranges: %d", oranges), 10, 100, 20, BLACK);
                                        DrawTexture(bananaTree, 10, 135, WHITE);
                                        DrawTexture(orangeTree, 580, 135, WHITE);
                                }
                                if (tree_level_win) {
                                        DrawText("Nacisnij SPACE aby wyjsc do menu", GetScreenWidth() / 2 - MeasureText("Nacisnij SPACE aby wyjsc do menu", 20) / 2, 370, 20, BLACK);
                                        if (IsKeyPressed(KEY_SPACE)) {
                                                gameState = GAME_STATE_MENU;
                                        }
                                }
                                
                                if (IsKeyPressed(KEY_B)) {
                                        gameState = GAME_STATE_SHOP;
                                }
                                if (IsKeyPressed(KEY_S)) {
                                        gameState = GAME_STATE_STATS;
                                }
                                
                                break;
                        case GAME_STATE_GAME_LVL2:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText(TextFormat("Rocks: %d", rocks), 10, 40, 20, BLACK);
                                DrawText("Nacisnij B aby wejsc do sklepu", 420, 30, 20, BLACK);
                                DrawText("Nacisnij S aby zobaczyc statystyki", 420, 60, 20, BLACK);
                                DrawTexture(rock, 270, 135, WHITE);
                                if (coal_upgrade && !iron_upgrade) { 
                                        DrawText(TextFormat("Coal: %d", coal), 10, 70, 20, BLACK);
                                        DrawTexture(coal_mine, 10, 135, WHITE);
                                }
                                if (coal_upgrade && iron_upgrade) {
                                        DrawText(TextFormat("Coal: %d", coal), 10, 70, 20, BLACK);
                                        DrawText(TextFormat("Iron: %d", iron), 10, 100, 20, BLACK);
                                        DrawTexture(coal_mine, 10, 215, WHITE);
                                        DrawTexture(iron_mine, 550, 215, WHITE);
                                }
                                if (IsKeyPressed(KEY_B)) {
                                        gameState = GAME_STATE_SHOP;
                                }
                                if (IsKeyPressed(KEY_S)) {
                                        gameState = GAME_STATE_STATS;
                                }
                                if (rocks_level_win) {
                                        DrawText("Nacisnij Space aby wrocic do menu", GetScreenWidth() / 2 - MeasureText("Nacisnij Space aby wrocic do menu", 20) / 2, 400, 20, BLACK);
                                        if (IsKeyPressed(KEY_SPACE)) {
                                                gameState = GAME_STATE_MENU;
                                        }
                                }
                                break;
                        case GAME_STATE_SHOP:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("Sklep", GetScreenWidth() / 2 - MeasureText("Sklep", 20) / 2, 100, 20, BLACK);
                                if (!tree_level_win) {
                                        DrawText(TextFormat("Apples: %d", apples), 10, 40, 20, BLACK);
                                        if (banana_upgrade) {
                                                DrawText(TextFormat("Bananas: %d", bananas), 10, 70, 20, BLACK);
                                        }
                                        if (orange_upgrade) {
                                                DrawText(TextFormat("Oranges: %d", oranges), 10, 100, 20, BLACK);
                                        }
                                        
                                        if (!banana_upgrade) {
                                                DrawRectangleRec(btn_banana_upgrade, RAYWHITE);
                                                DrawTexture(banana_upgrade_texture, 100, 425, WHITE);
                                                DrawText("250 apples to open banana tree", 20, 400, 20, BLACK);
                                        }
                                        if (!orange_upgrade) {
                                                DrawRectangleRec(btn_orange_upgrade, RAYWHITE);
                                                DrawTexture(orange_upgrade_texture, 520, 425, WHITE);
                                                DrawText("400 bananas to open orange tree", 430, 400, 20, BLACK);
                                        }
                                
                                
                                        DrawRectangleRec(btn_to_win, RAYWHITE);
                                        DrawTexture(win, GetScreenWidth() / 2 - 90, 120, WHITE);
                                        DrawText("1000 apples, 1000 bananas, 1000 oranges aby wygrac", GetScreenWidth() / 2 - MeasureText("1000 apples, 1000 bananas, 1000 oranges aby wygrac", 20) / 2, 240, 20, BLACK);
                                        if (IsKeyPressed(KEY_B)) {
                                        gameState = GAME_STATE_GAME;
                                        }
                                        if (CheckCollisionPointRec(mousePoint, btn_to_win)) {
                                                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && apples >= 1000 && bananas >= 1000 && oranges >= 1000) {
                                                        tree_level_win = true;
                                                        apples -= 1000;
                                                        bananas -= 1000;
                                                        oranges -= 1000;
                                                        gameState = GAME_STATE_WIN;
                                                }
                                        }
                                } else if (tree_level_win && !rocks_level_win) {
                                        DrawRectangleRec(btn_to_win_rock, RAYWHITE);
                                        DrawTexture(win, GetScreenWidth() / 2 - 90, 120, WHITE);
                                        DrawText("15000 rocks, 12000 coal, 10000 iron aby wygrac", GetScreenWidth() / 2 - MeasureText("1000 apples, 1000 bananas, 1000 oranges aby wygrac", 20) / 2, 240, 20, BLACK);
                                        if (IsKeyPressed(KEY_B)) {
                                        gameState = GAME_STATE_GAME_LVL2;
                                        }
                                        if (!coal_upgrade) {
                                                DrawRectangleRec(btn_coal_upgrade, RAYWHITE);
                                                DrawTexture(coal_upgrade_texture, 100, 425, WHITE);
                                                DrawText("2000 rocks to open coal mine", 20, 400, 20, BLACK);
                                        }
                                        if (!iron_upgrade) {
                                                DrawRectangleRec(btn_iron_upgrade, RAYWHITE);
                                                DrawTexture(iron_upgrade_texture, 520, 425, WHITE);
                                                DrawText("6000 coal to open iron mine", 430, 400, 20, BLACK);
                                        }
                                        if (CheckCollisionPointRec(mousePoint, btn_to_win_rock)) {
                                                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && rocks >= 15000 && coal >= 12000 && iron >= 10000) {
                                                        rocks_level_win = true;
                                                        rocks -= 15000;
                                                        coal -= 12000;
                                                        iron -= 10000;
                                                        gameState = GAME_STATE_WIN;
                                                }
                                        }
                                }
                                if (rocks_level_win) {
                                        if (IsKeyPressed(KEY_B)) {
                                                gameState = GAME_STATE_GAME_LVL2;
                                        }
                                        DrawText("Nacisnij B aby wrocic do gry", GetScreenWidth() / 2 - MeasureText("Nacisnij B aby wrocic do gry", 20) / 2, 310, 20, BLACK);
                                }
                                break;
                        case GAME_STATE_STATS:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("Statystyki", GetScreenWidth() / 2 - MeasureText("Statystyki", 20) / 2, 280, 20, BLACK);
                                DrawText("Nacisnij S aby wrocic do gry", GetScreenWidth() / 2 - MeasureText("Nacisnij S aby wrocic do gry", 20) / 2, 310, 20, BLACK);
                                DrawText(TextFormat("Apples: %d", apples), 10, 40, 20, BLACK);
                                DrawText(TextFormat("Clicks: %d", clicks), 10, 70, 20, BLACK);
                                DrawText(TextFormat("Bananas: %d", bananas), 300, 40, 20, BLACK);
                                DrawText(TextFormat("Oranges: %d", oranges), 600, 40, 20, BLACK);
                                DrawText(TextFormat("Rocks: %d", rocks), 10, 100, 20, BLACK);
                                DrawText(TextFormat("Coal: %d", coal), 10, 130, 20, BLACK);
                                DrawText(TextFormat("Iron: %d", iron), 10, 160, 20, BLACK);
                                if (!tree_level_win) {
                                        if (IsKeyPressed(KEY_S)) {
                                        gameState = GAME_STATE_GAME;
                                        }
                                } else {
                                        if (IsKeyPressed(KEY_S)) {
                                                gameState = GAME_STATE_GAME_LVL2;
                                        }
                                }
                                break;
                        case GAME_STATE_WIN:
                                ClearBackground(GREEN);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("Wygrales!", GetScreenWidth() / 2 - MeasureText("Wygrales!", 20) / 2, 280, 20, BLACK);
                                if (tree_level_win && !rocks_level_win) {
                                        DrawText("Teraz z menu mozesz wejsc na nastepny poziom!", GetScreenWidth() / 2 - MeasureText("Teraz z menu mozesz wejsc na nastepny poziom!", 20) / 2, 310, 20, BLACK);
                                } else
                                if (rocks_level_win) {
                                        DrawText("Narazie to tyle z gry, dziekuje za gre!", GetScreenWidth() / 2 - MeasureText("Narazie to tyle z gry, dziekuje za gre!", 20) / 2, 310, 20, BLACK);
                                }
                                DrawText("Nacisnij Enter aby wrocic do menu", GetScreenWidth() / 2 - MeasureText("Nacisnij Enter aby wrocic do menu", 20) / 2, 340, 20, BLACK);
                                if (IsKeyPressed(KEY_ENTER)) {
                                        gameState = GAME_STATE_MENU;
                                }
                                break;
                        default:
                                gameState = GAME_STATE_MENU;
                                break;
                }
                EndDrawing();
        }
        
        std::fstream save_file("saves/save.txt");
        save_file << apples << "\n";
        save_file << bananas << "\n";
        save_file << oranges << "\n";
        save_file << clicks << "\n";
        save_file << banana_upgrade << "\n";
        save_file << orange_upgrade << "\n";
        save_file << tree_level_win << "\n";
        save_file << rocks << "\n";
        save_file << coal << "\n";
        save_file << iron << "\n";
        save_file << coal_upgrade << "\n";
        save_file << iron_upgrade << "\n";
        save_file << rocks_level_win << "\n";   
        save_file.close();
        UnloadSound(click);
        UnloadMusicStream(music);
        CloseAudioDevice();
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
