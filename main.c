#include <raylib.h>
#include <stdio.h>

typedef unsigned int uint;

typedef struct {
    Vector2 cur_pos;
    Vector2 last_pos;
    Vector2 acceleration;
    uint radius;
} circle_t;

// TODO: make these not global, create a game object that gets passed to functions
float dt; // delta time
const int screenWidth = 800;
const int screenHeight = 450;
const Vector2 gravity = { 0.0f, 980.0f };

void render_circles(int count, circle_t circles[count]) {
    for (int i = 0; i < count; i++) {
        DrawCircleV(circles[i].position, circles[i].radius, YELLOW);
    }
}

void update() {
    apply_gravity();
}

void accelerate(circle_t circle, Vector2 acc) {
    Vector2Add(circle.acceleration, acc);
}

void apply_gravity(circle_t circle) {
    accelerate(circle, gravity); 
}

void update_circle(int count, circle_t circle, int ldt) {
    const Vector2 velocity = circle.cur_pos - circle.last_pos;
    // save the current position
    circle.last_pos = circle.cur_pos;
    // perform verlet integration
    circle.cur_pos = circle.cur_pos + velocity + circle.acceleration * ldt * ldt;
    circle.acceleration = {0};

    // for (int i = 0; i < count; i++) {
    //     circles[i].position.x += (circles[i].velocity.x*dt);
    //     circles[i].position.y += (circles[i].velocity.y*gravity*dt);
    //     if ((circles[i].position.y + circles[i].radius) > screenHeight) {
    //         circles[i].position.y = screenHeight - circles[i].radius;
    //         circles[i].velocity.y *= -1;
    //     } else if (circles[i].position.y < circles[i].radius){
    //         circles[i].position.y = circles[i].radius; 
    //         circles[i].velocity.y *= -1;
    //     }
    //     if ((circles[i].position.x + circles[i].radius) > screenWidth) {
    //         circles[i].position.x = screenWidth - circles[i].radius;
    //         circles[i].velocity.x *= -1;
    //     } else if (circles[i].position.x < circles[i].radius) {
    //         circles[i].position.x = circles[i].radius;
    //         circles[i].velocity.x *= -1;
    //     }
    // }
}

int main(void) {
    const int num_circles = 2;

    // int pos_x = 400;
    // int pos_y = 70;

    circle_t c1 = (circle_t){ .position = (Vector2){.x = 200, .y = 50}, .velocity = (Vector2){ .x = 30.0f, .y = -30.0f }, .radius = 20};
    circle_t c2 = (circle_t){ .position = (Vector2){.x = 300, .y = 30}, .velocity = (Vector2){ .x = 80.0f, .y = 30.0f }, .radius = 10};

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
