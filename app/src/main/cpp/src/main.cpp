#include <SDL3/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>

extern "C" int SDL_main(int argc, char *argv[]) {
    SDL_Log("Starting SDL_main with argc=%d", argc);

    SDL_SetHint(SDL_HINT_ORIENTATIONS, "Portrait");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Log("SDL_Init succeeded");


    SDL_Window *window = SDL_CreateWindow("Eternal Clash", 800, 600, SDL_WINDOW_FULLSCREEN);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, SDL_SOFTWARE_RENDERER);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    bool running = true;
    SDL_FRect player = {540, 1200, 100, 100};
    bool isDragging = false;
    std::vector<SDL_FRect> enemies;
    std::vector<SDL_FRect> bullets;
    Uint32 lastSpawnTime = SDL_GetTicks();
    Uint32 lastAttackTime = SDL_GetTicks();

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;

                case SDL_EVENT_FINGER_DOWN: {
                    int touchX = static_cast<int>(event.tfinger.x * 1080);
                    int touchY = static_cast<int>(event.tfinger.y * 2400);
                    if (touchX >= player.x && touchX <= player.x + player.w &&
                        touchY >= player.y && touchY <= player.y + player.h) {
                        isDragging = true;
                    }
                    break;
                }

                case SDL_EVENT_FINGER_UP:
                    isDragging = false;
                    break;

                case SDL_EVENT_FINGER_MOTION: {
                    if (isDragging) {
                        int touchX = static_cast<int>(event.tfinger.x * 1080);
                        int touchY = static_cast<int>(event.tfinger.y * 2400);
                        player.x = touchX - player.w / 2;
                        player.y = touchY - player.h / 2;
                        if (player.x < 0) player.x = 0;
                        if (player.y < 0) player.y = 0;
                        if (player.x + player.w > 1080) player.x = 1080 - player.w;
                        if (player.y + player.h > 2400) player.y = 2400 - player.h;
                    }
                    break;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastSpawnTime >= 500) {
            SDL_FRect enemy = {static_cast<float>(rand() % 1080), static_cast<float>(rand() % 2400),
                               40, 40}; // Random position
            enemies.push_back(enemy);
            lastSpawnTime = currentTime;
        }

        if (currentTime - lastAttackTime >= 200 && !enemies.empty()) {
            float minDist = 1e9;
            for (auto &enemy: enemies) {
                float dx = enemy.x + enemy.w / 2 - (player.x + player.w / 2);
                float dy = enemy.y + enemy.h / 2 - (player.y + player.h / 2);
                float dist = dx * dx + dy * dy;
                if (dist < minDist) {
                    minDist = dist;
                }
            }

            SDL_FRect bullet = {player.x + player.w / 2 - 5, player.y + player.h / 2 - 5, 10, 10};
            bullets.push_back(bullet);
            lastAttackTime = currentTime;
        }

        for (auto &enemy: enemies) {
            int dx = player.x + player.w / 2 - (enemy.x + enemy.w / 2);
            int dy = player.y + player.h / 2 - (enemy.y + enemy.h / 2);
            enemy.x += (dx > 0 ? 2 : -2);
            enemy.y += (dy > 0 ? 2 : -2);
        }

        for (auto it = bullets.begin(); it != bullets.end();) {
            it->y -= 5;
            if (it->y < 0) {
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &player);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (const auto &enemy: enemies) {
            SDL_RenderFillRect(renderer, &enemy);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (const auto &bullet: bullets) {
            SDL_RenderFillRect(renderer, &bullet);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}