#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

enum gamestate {
        GAME_STATE_MENU,
        GAME_STATE_CREDIT,
        GAME_STATE_STATS,
        GAME_STATE_SHOP,
        GAME_STATE_GAME,
        GAME_STATE_GAME_LVL2,
        GAME_STATE_WIN
};

struct gamecontext {
        gamestate gameState = GAME_STATE_MENU;
        gamestate previousState = GAME_STATE_MENU;

        bool sfx_muted = false;
        float volume = 0.5f;
        float sfx_volume = 1.0f;

        Rectangle btn_sfx = { 115, 10, 20, 20 };

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
                "Kozlowska",
                "Ukrop",
                "Maslowww"
        };

        std::vector<std::string> music_dev = {
                "Mati FL Studio"
        };
};

struct farmer {
        int upgrade = 0;
        float farmerTimer = 0.0f;
};

struct cps {
        float cpsTimer = 0.0f;
        int clicksThisSecond = 0;
        float currentCPS = 0.0f;
};

struct gameAssets {
        // MUSIC
        Music music;
        Sound click;
        Sound buy_sound;
        // SFX
        Texture2D sfx_button;
        Texture2D sfx_button_muted;
        // 1LVL
        Texture2D appleTree;
        Texture2D bananaTree;
        Texture2D orangeTree;
        Texture2D win;
        Texture2D banana_upgrade_texture;
        Texture2D orange_upgrade_texture;
        // 2LVL
        Texture2D rock;
        Texture2D coal_mine;
        Texture2D iron_mine;
        Texture2D coal_upgrade_texture;
        Texture2D iron_upgrade_texture;
        // farmer
        Texture2D farmer_upgrade_texture;
        // power upgrade
        Texture2D power_upgrade_texture;
};

struct shopUI {
        Rectangle btn_to_win = { (float)GetScreenWidth() / 2 - 90, 120, 180, 100 };
        Rectangle btn_banana_upgrade = { 100, 425, 190, 80 };
        Rectangle btn_orange_upgrade = { 520, 425, 190, 80 };

        Rectangle btn_to_win_rock = { (float)GetScreenWidth() / 2 - 90, 120, 180, 100 };
        Rectangle btn_coal_upgrade = { 100, 425, 190, 80 };
        Rectangle btn_iron_upgrade = { 520, 425, 190, 80 };

        Rectangle btn_farmer_upgrade = { (float)GetScreenWidth() / 2 - 90, 425, 180, 100 };
        Rectangle btn_power_upgrade = { (float)GetScreenWidth() / 2 - 90, 425, 180, 100 };
};

struct shopItem {
        int price;
        int price_supporting;
        int price_supporting_another;
        enum type {
                ITEM_BANANA,
                ITEM_ORANGE,
                ITEM_COAL,
                ITEM_IRON, 
                ITEM_WIN_TREE,
                ITEM_WIN_ROCK,
                ITEM_FARMER,
                ITEM_POWER_UPGRADE
        };
        type type;
        bool upgradeStatus;
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

        int farmer_upgrade = 0;
        int power_upgrade = 0;

        int click_power = 1;

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
                save_file << farmer_upgrade << std::endl;
                save_file << power_upgrade << std::endl;
                save_file << click_power << std::endl;
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
                open_file >> data.farmer_upgrade;
                open_file >> data.power_upgrade;
                open_file >> data.click_power;
                open_file.close();
        } else {
                std::cout << "Nie znaleziono pliku save. Wartosci ustawiane na 0." << std::endl;
        }
        return data;
}

bool processPurchase(PlayerData &data, Rectangle btn, shopItem &item, Vector2 mousePoint, gamecontext &context) {
        if (CheckCollisionPointRec(mousePoint, btn)) {
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                        switch (item.type) {
                                case shopItem::ITEM_BANANA:
                                        if (data.apples >= item.price) {
                                                data.banana_upgrade = true;
                                                data.apples -= item.price;
                                                return true;
                                        }
                                        break;
                                case shopItem::ITEM_ORANGE:
                                        if (data.bananas >= item.price) {
                                                data.orange_upgrade = true;
                                                data.bananas -= item.price;
                                                return true;
                                        }
                                        break;
                                case shopItem::ITEM_COAL:
                                        if (data.rocks >= item.price) {
                                                data.coal_upgrade = true;
                                                data.rocks -= item.price;
                                                return true;
                                        }
                                        break;
                                case shopItem::ITEM_IRON:
                                        if (data.coal >= item.price) {
                                                data.iron_upgrade = true;
                                                data.coal -= item.price;
                                                return true;
                                        }
                                        break;
                                case shopItem::ITEM_WIN_TREE:
                                        if (data.apples >= item.price && data.bananas >= item.price_supporting && data.oranges >= item.price_supporting_another) {
                                                data.tree_level_win = true;
                                                data.apples -= item.price;
                                                data.bananas -= item.price_supporting;
                                                data.oranges -= item.price_supporting_another;
                                                context.gameState = GAME_STATE_WIN;
                                                return true;
                                        }
                                        break;
                                case shopItem::ITEM_WIN_ROCK:
                                        if (data.rocks >= item.price && data.coal >= item.price_supporting && data.iron >= item.price_supporting_another) {
                                                data.rocks_level_win = true;
                                                data.rocks -= item.price;
                                                data.coal -= item.price_supporting;
                                                data.iron -= item.price_supporting_another;
                                                context.gameState = GAME_STATE_WIN;
                                                return true;
                                        }
                                        break;
                                case shopItem::ITEM_FARMER:
                                        if (data.apples >= item.price) {
                                                data.farmer_upgrade++;
                                                data.apples -= item.price;
                                                return true;
                                        }
                                        break;
                                case shopItem::ITEM_POWER_UPGRADE:
                                        if (data.coal >= item.price) {
                                                data.click_power += 2;
                                                data.power_upgrade++;
                                                data.coal -= item.price;
                                                return true;
                                        }
                                        break;
                        }
                }
        }
        return false;
}

void updateShop (PlayerData &data, gamecontext &context, const shopUI &shop_ui, Vector2 mousePoint, farmer &farmer, gameAssets &assets) {
        shopItem item;
        item.type = shopItem::ITEM_BANANA;
        item.price = 250;
        item.price_supporting = 0;
        item.price_supporting_another = 0;
       if (!data.banana_upgrade && processPurchase(data, shop_ui.btn_banana_upgrade, item, mousePoint, context)) {
        PlaySound(assets.buy_sound);
       }
       item.type = shopItem::ITEM_ORANGE;
       item.price = 400;
       item.price_supporting = 0;
       if (!data.orange_upgrade && processPurchase(data, shop_ui.btn_orange_upgrade, item, mousePoint, context)) {
        PlaySound(assets.buy_sound);
       }
       item.type = shopItem::ITEM_COAL;
       item.price = 2000;
       item.price_supporting = 0;
       if (!data.coal_upgrade && processPurchase(data, shop_ui.btn_coal_upgrade, item, mousePoint, context)) {
        PlaySound(assets.buy_sound);
       }
       item.type = shopItem::ITEM_IRON;
       item.price = 6000;
       item.price_supporting = 0;
       if (!data.iron_upgrade && processPurchase(data, shop_ui.btn_iron_upgrade, item, mousePoint, context)) {
                PlaySound(assets.buy_sound);
       }
       item.type = shopItem::ITEM_WIN_TREE;
       item.price = 1000;
       item.price_supporting = 1000;
       item.price_supporting_another = 1000;
       if (!data.tree_level_win && processPurchase(data, shop_ui.btn_to_win, item, mousePoint, context)) {
                PlaySound(assets.buy_sound);
       }
       item.type = shopItem::ITEM_WIN_ROCK;
       item.price = 15000;
       item.price_supporting = 12000;
       item.price_supporting_another = 10000;
       if (!data.rocks_level_win && processPurchase(data, shop_ui.btn_to_win_rock, item, mousePoint, context)) {
                PlaySound(assets.buy_sound);
       }
       item.type = shopItem::ITEM_FARMER;
       item.price = 100 * (data.farmer_upgrade + 1);
       item.price_supporting = 0;
       item.price_supporting_another = 0;
       if (processPurchase(data, shop_ui.btn_farmer_upgrade, item, mousePoint, context)) {
                farmer.upgrade = data.farmer_upgrade;
                PlaySound(assets.buy_sound);
       }
       item.type = shopItem::ITEM_POWER_UPGRADE;
       item.price = 500 * (data.power_upgrade + 1);;
       item.price_supporting = 0;
       item.price_supporting_another = 0;
       if (processPurchase(data, shop_ui.btn_power_upgrade, item, mousePoint, context)) {
                PlaySound(assets.buy_sound);
       }
}



void loadAssets (gameAssets &assets) {
        assets.music = LoadMusicStream("includes/aud/King Has Returned.mp3");
        assets.click = LoadSound("includes/sf/click.mp3");
        assets.buy_sound = LoadSound("includes/sf/BuySound.mp3");
        assets.sfx_button = LoadTexture("includes/sf/click_sound_remove.png");
        assets.sfx_button_muted = LoadTexture("includes/sf/click_sound_remove_muted.png");
        assets.appleTree = LoadTexture("includes/tetures/appletree.png");
        assets.bananaTree = LoadTexture("includes/tetures/bananatree.png");
        assets.orangeTree = LoadTexture("includes/tetures/orangetree.png");
        assets.win = LoadTexture("includes/tetures/win_button.png");
        assets.banana_upgrade_texture = LoadTexture("includes/tetures/banana_button.png");
        assets.orange_upgrade_texture = LoadTexture("includes/tetures/orange_button.png");
        assets.rock = LoadTexture("includes/tetures/rock.png");
        assets.coal_mine = LoadTexture("includes/tetures/coal_mine.png");
        assets.iron_mine = LoadTexture("includes/tetures/iron_mine.png");
        assets.coal_upgrade_texture = LoadTexture("includes/tetures/coal_button.png");
        assets.iron_upgrade_texture = LoadTexture("includes/tetures/iron_button.png");
        assets.farmer_upgrade_texture = LoadTexture("includes/tetures/farmer-upgrade.png");
        assets.power_upgrade_texture = LoadTexture("includes/tetures/power-upgrade.png");
}

void unloadAssets (gameAssets &assets) {
        UnloadSound(assets.click);
        UnloadSound(assets.buy_sound);
        UnloadMusicStream(assets.music);
        CloseAudioDevice();

        UnloadTexture(assets.sfx_button);
        UnloadTexture(assets.sfx_button_muted);
        // trees
        UnloadTexture(assets.appleTree);
        UnloadTexture(assets.bananaTree);
        UnloadTexture(assets.orangeTree);
        // buttons
        UnloadTexture(assets.win);
        UnloadTexture(assets.banana_upgrade_texture);
        UnloadTexture(assets.orange_upgrade_texture);
        // rocks
        UnloadTexture(assets.rock);
        UnloadTexture(assets.coal_mine);
        UnloadTexture(assets.iron_mine);
        // rock_but
        UnloadTexture(assets.coal_upgrade_texture);
        UnloadTexture(assets.iron_upgrade_texture);
        // farmer
        UnloadTexture(assets.farmer_upgrade_texture);
        // power
        UnloadTexture(assets.power_upgrade_texture);
}

void updateGame (gamecontext &context, gameAssets &assets, PlayerData &data, cps &cps, shopUI &shop_ui, Vector2 mousePoint, farmer &farmer) {
         // LOGIC BLOCK
                UpdateMusicStream(assets.music);
                mousePoint = GetMousePosition();
                cps.cpsTimer += GetFrameTime();
                if (cps.cpsTimer >= 1.0f) {
                        cps.currentCPS = (float)cps.clicksThisSecond / cps.cpsTimer;
                        cps.clicksThisSecond = 0;
                        cps.cpsTimer = 0.0f;
                }

                if (farmer.upgrade > 0) {
                        farmer.farmerTimer += GetFrameTime();
                        if (farmer.farmerTimer >= 1.0f) {
                                data.apples += farmer.upgrade;
                                if (data.banana_upgrade) { data.bananas += farmer.upgrade; }
                                if (data.orange_upgrade) { data.oranges += farmer.upgrade; }
                                if (data.tree_level_win) { data.rocks += farmer.upgrade; }
                                if (data.coal_upgrade) { data.coal += farmer.upgrade; }
                                if (data.iron_upgrade) { data.iron += farmer.upgrade; }
                                farmer.farmerTimer = 0.0f;
                        }
                }
                
                switch (context.gameState) {
                        case GAME_STATE_MENU:
                                if (IsKeyPressed(KEY_ENTER)) {
                                        context.previousState = context.gameState;
                                        context.gameState = GAME_STATE_GAME;
                                }
                                if (data.tree_level_win) {
                                        if (IsKeyPressed(KEY_F3)) {
                                                context.previousState = context.gameState;
                                                context.gameState = GAME_STATE_GAME_LVL2;
                                        }
                                }
                                if (IsKeyPressed(KEY_F2)) {
                                        context.gameState = GAME_STATE_CREDIT;
                                }
                                break;
                        case GAME_STATE_GAME:
                                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                        data.apples+= data.click_power;
                                        data.clicks++;
                                        cps.clicksThisSecond++;
                                        PlaySound(assets.click);
                                }
                                if (data.banana_upgrade && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))) {
                                        data.bananas+= data.click_power;
                                }
                                if (data.orange_upgrade && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))) {
                                        data.oranges+= data.click_power;
                                }
                                if (IsKeyPressed(KEY_SPACE)) {
                                        context.gameState = GAME_STATE_MENU;
                                }
                                if (IsKeyPressed(KEY_B)) {
                                        context.previousState = context.gameState;
                                        context.gameState = GAME_STATE_SHOP;
                                }
                                if (IsKeyPressed(KEY_S)) {
                                        context.previousState = context.gameState;
                                        context.gameState = GAME_STATE_STATS;
                                }
                        break;
                        case GAME_STATE_CREDIT:
                                if (IsKeyPressed(KEY_ENTER)) {
                                        context.gameState = GAME_STATE_MENU;
                                }
                                break;
                        case GAME_STATE_GAME_LVL2:
                                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                                        data.rocks += data.click_power;
                                        data.clicks++;
                                        cps.clicksThisSecond++;
                                        PlaySound(assets.click);
                                }
                                if (data.coal_upgrade && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))) {
                                        data.coal += data.click_power;
                                }
                                if (data.iron_upgrade && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))) {
                                        data.iron+= data.click_power;
                                }
                                if (IsKeyPressed(KEY_B)) {
                                        context.previousState = GAME_STATE_GAME_LVL2;
                                        context.gameState = GAME_STATE_SHOP;
                                }
                                if (IsKeyPressed(KEY_S)) {
                                        context.previousState = GAME_STATE_GAME_LVL2;
                                        context.gameState = GAME_STATE_STATS;
                                }
                                if (IsKeyPressed(KEY_SPACE)) {
                                        context.gameState = GAME_STATE_MENU;
                                }
                        break;
                        case GAME_STATE_SHOP:
                                if (context.previousState == GAME_STATE_GAME) {
                                        updateShop(data, context, shop_ui, mousePoint, farmer, assets);
                                } else if (context.previousState == GAME_STATE_GAME_LVL2) {
                                        updateShop(data, context, shop_ui, mousePoint, farmer, assets);     
                                }
                                if (IsKeyPressed(KEY_B)) {
                                        context.gameState = context.previousState;
                                } 
                                break;
                        case GAME_STATE_STATS:
                                if (IsKeyPressed(KEY_S)) {
                                        context.gameState = context.previousState;
                                }
                                break;
                        case GAME_STATE_WIN:
                                if (IsKeyPressed(KEY_ENTER)) {
                                        context.gameState = GAME_STATE_MENU;
                                }
                                break;
                        default: 
                                context.gameState = GAME_STATE_GAME;
                                break;
                }
                
                if (CheckCollisionPointRec(mousePoint, context.btn_sfx)) {
                        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                                context.sfx_muted = !context.sfx_muted;
                                if (context.sfx_muted) {
                                        context.sfx_volume = 0.0f;
                                } else {
                                        context.sfx_volume = 1.0f;
                                }
                                SetSoundVolume(assets.click, context.sfx_volume);
                                SetSoundVolume(assets.buy_sound, context.sfx_volume);
                        }
                }

                if (IsKeyDown(KEY_UP)) {
                        context.volume += 0.01f;
                        if (context.volume > 1.0f) context.volume = 1.0f; 
                        SetMusicVolume(assets.music, context.volume);
                } else if (IsKeyDown(KEY_DOWN)) {
                        context.volume -= 0.01f;
                        if (context.volume < 0.0f) context.volume = 0.0f;
                        SetMusicVolume(assets.music, context.volume);
                };
}

void drawGame(gamecontext &context, gameAssets assets, PlayerData data, cps cps, shopUI &shop_ui) {
         // DRAWING BLOCK
                BeginDrawing();

                DrawRectangle(140, 10, 100, 20, LIGHTGRAY);
                DrawRectangleLines(140, 10, 100, 20, BLACK);
                DrawRectangle((int)(140 + context.volume * 100 - 5), 8, 10, 26, DARKGRAY);
                DrawText("UP/DOWN dla glosnosci", 140, 40, 8, BLACK);
                DrawRectangleRec(context.btn_sfx, RAYWHITE);
                if (context.sfx_muted) {
                        DrawTexture(assets.sfx_button_muted, 115, 10, WHITE);
                } else {
                        DrawTexture(assets.sfx_button, 115, 10, WHITE);
                }
                switch (context.gameState) {
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
                                for (size_t i = 0; i < context.developers.size(); i++) {
                                        DrawText(context.developers[i].c_str(), 10, (int)(70 + i * 30), 20, BLACK);
                                }
                                DrawText("Testerowie: ", 300, 40, 20, BLACK);
                                for (size_t i = 0; i < context.testers.size(); i++) {
                                        DrawText(context.testers[i].c_str(), 300, (int)(70 + i * 30), 20, BLACK);
                                }
                                DrawText("Muzyka: ", 550, 40, 20, BLACK);
                                for (size_t i = 0; i < context.music_dev.size(); i++) {
                                        DrawText(context.music_dev[i].c_str(), 550, (int)(70 + i * 30), 20, MAGENTA);
                                }
                                DrawText("Nacisnij Enter aby wrocic do menu", 10, 550, 20, BLACK);
                                break;
                        case GAME_STATE_GAME:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText(TextFormat("CPS: %.1f", cps.currentCPS), GetScreenWidth() / 2 - MeasureText(TextFormat("CPS: %.1f", cps.currentCPS), 20) / 2 - 60, 40, 20, BLACK);     
                                DrawText(TextFormat("Apples: %d", data.apples), 10, 40, 20, BLACK);
                                if (data.farmer_upgrade > 0) {
                                        DrawText(TextFormat("Farmers: %d (+%d/s)", data.farmer_upgrade, data.farmer_upgrade), 420, 90, 20, DARKGREEN);
                                }
                                if (data.power_upgrade > 0) {
                                        DrawText(TextFormat("Power: %d (+%d/click)", data.click_power, data.power_upgrade * 2), 420, 120, 20, DARKGREEN);
                                }
                                DrawText("Nacisnij B aby wejsc do sklepu", 420, 30, 20, BLACK);
                                DrawText("Nacisnij S aby zobaczyc statystyki", 420, 60, 20, BLACK);
                                DrawTexture(assets.appleTree, 300, 135, WHITE);
                                if (data.banana_upgrade && !data.orange_upgrade) { 
                                        DrawText(TextFormat("Bananas: %d", data.bananas), 10, 70, 20, BLACK);
                                        DrawTexture(assets.bananaTree, 10, 135, WHITE);
                                }
                                if (data.banana_upgrade && data.orange_upgrade) {
                                        DrawText(TextFormat("Bananas: %d", data.bananas), 10, 70, 20, BLACK);
                                        DrawText(TextFormat("Oranges: %d", data.oranges), 10, 100, 20, BLACK);
                                        DrawTexture(assets.bananaTree, 10, 135, WHITE);
                                        DrawTexture(assets.orangeTree, 580, 135, WHITE);
                                }
                                DrawText("Nacisnij Space aby wrocic do menu", 420, 10, 10, BLACK);     
                                break;
                        case GAME_STATE_GAME_LVL2:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText(TextFormat("CPS: %.1f", cps.currentCPS), GetScreenWidth() / 2 - MeasureText(TextFormat("CPS: %.1f", cps.currentCPS), 20) / 2 - 90, 40, 20, BLACK);     
                                DrawText(TextFormat("Rocks: %d", data.rocks), 10, 40, 20, BLACK);
                                if (data.farmer_upgrade > 0) {
                                        DrawText(TextFormat("Farmers: %d (+%d/s)", data.farmer_upgrade, data.farmer_upgrade), 420, 90, 20, DARKGREEN);
                                }
                                if (data.power_upgrade > 0) {
                                        DrawText(TextFormat("Power: %d (+%d/click)", data.click_power, data.power_upgrade * 2), 420, 120, 20, DARKGREEN);
                                }
                                DrawText("Nacisnij B aby wejsc do sklepu", 420, 30, 20, BLACK);
                                DrawText("Nacisnij S aby zobaczyc statystyki", 420, 60, 20, BLACK);
                                DrawTexture(assets.rock, 270, 135, WHITE);
                                if (data.coal_upgrade && !data.iron_upgrade) { 
                                        DrawText(TextFormat("Coal: %d", data.coal), 10, 70, 20, BLACK);
                                        DrawTexture(assets.coal_mine, 10, 135, WHITE);
                                }
                                if (data.coal_upgrade && data.iron_upgrade) {
                                        DrawText(TextFormat("Coal: %d", data.coal), 10, 70, 20, BLACK);
                                        DrawText(TextFormat("Iron: %d", data.iron), 10, 100, 20, BLACK);
                                        DrawTexture(assets.coal_mine, 10, 215, WHITE);
                                        DrawTexture(assets.iron_mine, 550, 215, WHITE);
                                }
                                DrawText("Nacisnij Space aby wrocic do menu", 420, 10, 10, BLACK);       
                                break;
                        case GAME_STATE_SHOP:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);   
                                DrawText("Sklep", GetScreenWidth() / 2 - MeasureText("Sklep", 20) / 2, 100, 20, BLACK);
                                
                                if (context.previousState == GAME_STATE_GAME) {
                                        int farmerPrice = 100 * (data.farmer_upgrade + 1);
                                        const char* farmerText = TextFormat("%d apples aby utworzyc farmera", farmerPrice);
                                        DrawText(farmerText, GetScreenWidth() / 2 - MeasureText(farmerText, 20) / 2, 530, 20, BLACK);
                                        DrawRectangleRec(shop_ui.btn_farmer_upgrade, RAYWHITE);
                                        DrawTexture(assets.farmer_upgrade_texture, GetScreenWidth() / 2 - assets.farmer_upgrade_texture.width / 2, 425, WHITE);
                                        DrawText(TextFormat("Posiadasz: %d", data.farmer_upgrade), GetScreenWidth() / 2 - MeasureText(TextFormat("Posiadasz: %d", data.farmer_upgrade), 20) / 2, 560, 20, DARKGREEN);
                                        DrawText(TextFormat("Apples: %d", data.apples), 10, 40, 20, BLACK);
                                        if (data.banana_upgrade) {
                                                DrawText(TextFormat("Bananas: %d", data.bananas), 10, 70, 20, BLACK);
                                        }
                                        if (data.orange_upgrade) {
                                                DrawText(TextFormat("Oranges: %d", data.oranges), 10, 100, 20, BLACK);
                                        }
                                        
                                        if (!data.banana_upgrade) {
                                                DrawRectangleRec(shop_ui.btn_banana_upgrade, RAYWHITE);
                                                DrawTexture(assets.banana_upgrade_texture, 100, 425, WHITE);
                                                DrawText("250 apples to open banana tree", 20, 400, 20, BLACK);
                                        }
                                        if (!data.orange_upgrade) {
                                                DrawRectangleRec(shop_ui.btn_orange_upgrade, RAYWHITE);
                                                DrawTexture(assets.orange_upgrade_texture, 520, 425, WHITE);
                                                DrawText("400 bananas to open orange tree", 430, 400, 20, BLACK);
                                        }
                                        if (!data.tree_level_win) {
                                                DrawRectangleRec(shop_ui.btn_to_win, RAYWHITE);
                                                DrawTexture(assets.win, GetScreenWidth() / 2 - 90, 120, WHITE);
                                                DrawText("1000 apples, 1000 bananas, 1000 oranges aby wygrac", GetScreenWidth() / 2 - MeasureText("1000 apples, 1000 bananas, 1000 oranges aby wygrac", 20) / 2, 240, 20, BLACK);
                                        }
                                        
                                        
                                        
                                } 
                                if (context.previousState == GAME_STATE_GAME_LVL2) {
                                        int powerPrice = 500 * (data.power_upgrade + 1);
                                        const char* powerPriceText = TextFormat("%d coal aby ulepszyc kopalnie", powerPrice);
                                        DrawText(powerPriceText, GetScreenWidth() / 2 - MeasureText(powerPriceText, 20) / 2, 530, 20, BLACK);
                                        DrawRectangleRec(shop_ui.btn_to_win_rock, RAYWHITE);
                                        DrawTexture(assets.win, GetScreenWidth() / 2 - 90, 120, WHITE);
                                        DrawRectangleRec(shop_ui.btn_power_upgrade, RAYWHITE);
                                        DrawTexture(assets.power_upgrade_texture, GetScreenWidth() / 2 - assets.power_upgrade_texture.width / 2, 425, WHITE);
                                        DrawText(TextFormat("Power upgrade: %d", data.power_upgrade), GetScreenWidth() / 2 - MeasureText(TextFormat("Power upgrade: %d", data.power_upgrade), 20) / 2, 560, 20, DARKGREEN);
                                        const char* winRockText = "15000 rocks, 12000 coal, 10000 iron aby wygrac";
                                        DrawText(winRockText, GetScreenWidth() / 2 - MeasureText(winRockText, 20) / 2, 240, 20, BLACK);
                                        if (!data.coal_upgrade) {
                                                DrawRectangleRec(shop_ui.btn_coal_upgrade, RAYWHITE);
                                                DrawTexture(assets.coal_upgrade_texture, 100, 425, WHITE);
                                                DrawText("2000 rocks to open coal mine", 20, 400, 20, BLACK);
                                        }
                                        if (!data.iron_upgrade) {
                                                DrawRectangleRec(shop_ui.btn_iron_upgrade, RAYWHITE);
                                                DrawTexture(assets.iron_upgrade_texture, 520, 425, WHITE);
                                                DrawText("6000 coal to open iron mine", 430, 400, 20, BLACK);
                                        }
                                }
                                DrawText("Nacisnij B aby wrocic do gry", GetScreenWidth() / 2 - MeasureText("Nacisnij B aby wrocic do gry", 20) / 2, 310, 20, BLACK);
                                break;
                        case GAME_STATE_STATS:
                                ClearBackground(RAYWHITE);
                                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 8, GREEN);
                                DrawText("Statystyki", GetScreenWidth() / 2 - MeasureText("Statystyki", 20) / 2, 280, 20, BLACK);
                                DrawText("Nacisnij S aby wrocic do gry", GetScreenWidth() / 2 - MeasureText("Nacisnij S aby wrocic do gry", 20) / 2, 310, 20, BLACK);
                                DrawText(TextFormat("Apples: %d", data.apples), 10, 40, 20, BLACK);
                                DrawText(TextFormat("Clicks: %d", data.clicks), 10, 70, 20, BLACK);
                                DrawText(TextFormat("Bananas: %d", data.bananas), 300, 40, 20, BLACK);
                                DrawText(TextFormat("Oranges: %d", data.oranges), 600, 40, 20, BLACK);
                                DrawText(TextFormat("Rocks: %d", data.rocks), 10, 100, 20, BLACK);
                                DrawText(TextFormat("Coal: %d", data.coal), 10, 130, 20, BLACK);
                                DrawText(TextFormat("Iron: %d", data.iron), 10, 160, 20, BLACK);
                                DrawText(TextFormat("Farmers: %d", data.farmer_upgrade), 10, 190, 20, BLACK);
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
                                context.gameState = GAME_STATE_MENU;
                                break;
                }
                EndDrawing();
}

// FarmaCraft 5.5v - The Last Update!
int main () {
        InitWindow(800, 600, "FarmaCraft");
        SetTargetFPS(144);

        InitAudioDevice();

        gameAssets assets;
        loadAssets(assets);
        shopUI shop_ui;
        gamecontext context;
        farmer farmer;

        PlayMusicStream(assets.music);

        SetMusicVolume(assets.music, context.volume);

        SetSoundVolume(assets.click, context.sfx_volume);
        SetSoundVolume(assets.buy_sound, context.sfx_volume);

        Vector2 mousePoint = { 0.0f, 0.0f };

        PlayerData data;

        data = loadGame();
        farmer.upgrade = data.farmer_upgrade;

        cps cps;

        std::cout << "#LoveAngelika" << std::endl;

        while (!WindowShouldClose()) {
                updateGame(context, assets, data, cps, shop_ui, mousePoint, farmer);

                drawGame(context, assets, data, cps, shop_ui);
        }

        data.saveGame();
      
        unloadAssets(assets);

        CloseWindow();
        return 0;
}