/**
* Author: Xuanyi Li
* Assignment: Simple 2D Scene
* Date due: 10/05/2026
*
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "raylib.h"
#include <cmath>

// Window
constexpr int SCREEN_WIDTH  = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int FPS = 60;

// Texture sizes on screen
constexpr float SUN_SIZE   = 120.0f;
constexpr float EARTH_SIZE = 75.0f;
constexpr float MOON_SIZE  = 42.0f;

// Orbit sizes
constexpr float EARTH_RADIUS_X = 220.0f;
constexpr float EARTH_RADIUS_Y = 130.0f;
constexpr float MOON_RADIUS_X  = 70.0f;
constexpr float MOON_RADIUS_Y  = 45.0f;

// Animation speeds
constexpr float SUN_MOVE_SPEED     = 0.45f;
constexpr float EARTH_ORBIT_SPEED  = 0.85f;
constexpr float MOON_ORBIT_SPEED   = 2.2f;
constexpr float EARTH_ROTATE_SPEED = 55.0f;
constexpr float SUN_PULSE_SPEED    = 2.0f;

Texture2D gSunTexture;
Texture2D gEarthTexture;
Texture2D gMoonTexture;

Vector2 gSunPosition   = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
Vector2 gEarthPosition = { 0.0f, 0.0f };
Vector2 gMoonPosition  = { 0.0f, 0.0f };

float gSunMoveTime    = 0.0f;
float gEarthOrbitTime = 0.0f;
float gMoonOrbitTime  = 0.0f;
float gEarthRotation  = 0.0f;
float gSunPulseTime   = 0.0f;
float gSunScale       = 1.0f;

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Project 1 - Simple 2D Scene");
    SetTargetFPS(FPS);

    gSunTexture   = LoadTexture("assets/sun.png");
    gEarthTexture = LoadTexture("assets/earth.png");
    gMoonTexture  = LoadTexture("assets/moon.png");
}

void processInput()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        CloseWindow();
    }
}

void update(float deltaTime)
{
    // All animation values use delta time.
    gSunMoveTime    += SUN_MOVE_SPEED * deltaTime;
    gEarthOrbitTime += EARTH_ORBIT_SPEED * deltaTime;
    gMoonOrbitTime  += MOON_ORBIT_SPEED * deltaTime;
    gSunPulseTime   += SUN_PULSE_SPEED * deltaTime;

    // Object 1: the sun moves in a small circular pattern.
    gSunPosition.x = SCREEN_WIDTH / 2.0f + cosf(gSunMoveTime) * 35.0f;
    gSunPosition.y = SCREEN_HEIGHT / 2.0f + sinf(gSunMoveTime) * 25.0f;

    // The sun also scales in and out.
    gSunScale = 1.0f + 0.12f * sinf(gSunPulseTime);

    // Object 2: Earth moves in an ellipse RELATIVE TO the sun.
    gEarthPosition.x = gSunPosition.x + cosf(gEarthOrbitTime) * EARTH_RADIUS_X;
    gEarthPosition.y = gSunPosition.y + sinf(gEarthOrbitTime) * EARTH_RADIUS_Y;

    // Earth also rotates.
    gEarthRotation += EARTH_ROTATE_SPEED * deltaTime;

    // Object 3: Moon moves in an ellipse RELATIVE TO Earth.
    gMoonPosition.x = gEarthPosition.x + cosf(gMoonOrbitTime) * MOON_RADIUS_X;
    gMoonPosition.y = gEarthPosition.y + sinf(gMoonOrbitTime) * MOON_RADIUS_Y;
}

void drawTextureCentered(Texture2D texture, Vector2 position,
                         float size, float rotation)
{
    Rectangle source = {
        0.0f,
        0.0f,
        static_cast<float>(texture.width),
        static_cast<float>(texture.height)
    };

    Rectangle destination = {
        position.x,
        position.y,
        size,
        size
    };

    Vector2 origin = {
        size / 2.0f,
        size / 2.0f
    };

    DrawTexturePro(texture, source, destination, origin, rotation, WHITE);
}

void render()
{
    // Extra credit: background changes gradually in a repeating pattern.
    unsigned char blue =
        static_cast<unsigned char>(35 + 20 * (sinf(gSunPulseTime * 0.35f) + 1.0f));

    Color background = { 8, 12, blue, 255 };

    BeginDrawing();
    ClearBackground(background);

    // Optional orbit guides make the relationships easy to see.
    DrawEllipseLines(
        static_cast<int>(gSunPosition.x),
        static_cast<int>(gSunPosition.y),
        EARTH_RADIUS_X,
        EARTH_RADIUS_Y,
        Color{70, 70, 95, 255}
    );

    DrawEllipseLines(
        static_cast<int>(gEarthPosition.x),
        static_cast<int>(gEarthPosition.y),
        MOON_RADIUS_X,
        MOON_RADIUS_Y,
        Color{70, 70, 95, 255}
    );

    drawTextureCentered(
        gSunTexture,
        gSunPosition,
        SUN_SIZE * gSunScale,
        0.0f
    );

    drawTextureCentered(
        gEarthTexture,
        gEarthPosition,
        EARTH_SIZE,
        gEarthRotation
    );

    drawTextureCentered(
        gMoonTexture,
        gMoonPosition,
        MOON_SIZE,
        -gEarthRotation * 0.5f
    );

    EndDrawing();
}

void shutdown()
{
    UnloadTexture(gSunTexture);
    UnloadTexture(gEarthTexture);
    UnloadTexture(gMoonTexture);
    CloseWindow();
}

int main()
{
    initialise();

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        processInput();
        update(deltaTime);
        render();
    }

    shutdown();
    return 0;
}
