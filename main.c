#include <raylib.h>
#include <stdio.h>

typedef unsigned int uint;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    uint radius;
} circle_t;

// TODO: make these not global, create a game object that gets passed to functions
float dt; // delta time
const int screenWidth = 800;
const int screenHeight = 450;
const float gravity = 9.8f;

void render_circles(int count, circle_t circles[count]) {
    for (int i = 0; i < count; i++) {
        DrawCircleV(circles[i].position, circles[i].radius, YELLOW);
    }
}

void update_circles(int count, circle_t* circles) {
    for (int i = 0; i < count; i++) {
        circles[i].position.y += circles[i].velocity.y*gravity*dt;
        circles[i].position.x += circles[i].velocity.x*dt;
        if ((circles[i].position.y + circles[i].radius) > screenHeight) {
            circles[i].position.y = screenHeight - circles[i].radius;
            circles[i].velocity.y *= -1;
        } else if (circles[i].position.y < circles[i].radius){
            circles[i].position.y = circles[i].radius; 
            circles[i].velocity.y *= -1;
        }
        if ((circles[i].position.x + circles[i].radius) > screenWidth) {
            circles[i].position.x = screenWidth - circles[i].radius;
            circles[i].velocity.x *= -1;
        } else if (circles[i].position.x < circles[i].radius) {
            circles[i].position.x = circles[i].radius;
            circles[i].velocity.x *= -1;
        }
    }
}

int main(void) {
    const int num_circles = 2;

    // int pos_x = 400;
    // int pos_y = 70;

    circle_t c1 = (circle_t){ .position = (Vector2){.x = 200, .y = 50}, .velocity = (Vector2){ .x = 20.0f, .y = -20.0f }, .radius = 10};
    circle_t c2 = (circle_t){ .position = (Vector2){.x = 300, .y = 30}, .velocity = (Vector2){ .x = 20.0f, .y = 20.0f }, .radius = 10};

    circle_t circles[num_circles] = {c1, c2};

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    // if this is set, the delta time is always 0 for some reason
    // SetTargetFPS(60);

    while (!WindowShouldClose()) {
        dt = GetFrameTime();
        update_circles(num_circles, circles);

        // render
        BeginDrawing();
            ClearBackground(BLACK);

            // DrawCircle(pos_x, pos_y, 10, YELLOW);
            render_circles(num_circles, circles);

            // debug stuff
            DrawText("U R A CUTIE", 50, 50, 10, YELLOW);
            DrawText(TextFormat("FPS: %i", GetFPS()), 5, 5, 10, GREEN);
            DrawText(TextFormat("Frame time: %f", dt), 5, 15, 10, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
