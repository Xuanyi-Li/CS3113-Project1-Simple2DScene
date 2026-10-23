/**
 * Author: [Your name]
 * Assignment: Simple 2D Scene
 * Date due: 10/05/2026
 * [Complete the required integrity statement accurately before submission.]
 */
#include "raylib.h"
#include <math.h>

// Enums
enum AppStatus { TERMINATED, RUNNING };
enum Direction { LEFT, RIGHT };

// Global Constants
constexpr int SCREEN_WIDTH = 1200, SCREEN_HEIGHT = 675, FPS = 60;
constexpr float LIMIT_ANGLE = 20.0f;
constexpr float MAX_AMP = 10.0f;
constexpr Vector2 BASE_SIZE = { 170.0f, 170.0f };

// Image
constexpr char JIWOO_FP[] = "assets/game/jiwoo.png";
constexpr char CARMEN_FP[] = "assets/game/carmen.png";
constexpr char YUHA_FP[] = "assets/game/yuha.png";
constexpr char STELLA_FP[] = "assets/game/stella.png";
constexpr char JUUN_FP[] = "assets/game/juun.png";
constexpr char ANA_FP[] = "assets/game/ana.png";
constexpr char IAN_FP[] = "assets/game/ian.png";
constexpr char YEON_FP[] = "assets/game/yeon.png";

// Global Variables
AppStatus gAppStatus = RUNNING;
Direction gDirection = RIGHT;
float gAngle = 0.0f, gPulseTime = 0.0f, gPreviousTicks = 0.0f;
Vector2 gScale = BASE_SIZE;
Texture2D gBackgroundTexture;
Vector2 gJiwooPosition = { 130.0f, 270.0f };
Texture2D gJiwooTexture;
Vector2 gCarmenPosition = { 430.0f, 250.0f };
Texture2D gCarmenTexture;
Vector2 gYuhaPosition = { 730.0f, 290.0f };
Texture2D gYuhaTexture;
Vector2 gStellaPosition = { 1030.0f, 280.0f };
Texture2D gStellaTexture;
Vector2 gJuunPosition = { 130.0f, 480.0f };
Texture2D gJuunTexture;
Vector2 gAnaPosition = { 300.0f, 30.0f };
Texture2D gAnaTexture;
Vector2 gIanPosition = { 730.0f, 490.0f };
Texture2D gIanTexture;
Vector2 gYeonPosition = { 1030.0f, 520.0f };
Texture2D gYeonTexture;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hearts2Hearts - 8 Members");
    gBackgroundTexture = LoadTexture("assets/game/background.png");
    gJiwooTexture = LoadTexture(JIWOO_FP);
    gCarmenTexture = LoadTexture(CARMEN_FP);
    gYuhaTexture = LoadTexture(YUHA_FP);
    gStellaTexture = LoadTexture(STELLA_FP);
    gJuunTexture = LoadTexture(JUUN_FP);
    gAnaTexture = LoadTexture(ANA_FP);
    gIanTexture = LoadTexture(IAN_FP);
    gYeonTexture = LoadTexture(YEON_FP);
    SetTargetFPS(FPS);
    gPreviousTicks = static_cast<float>(GetTime());
}

void processInput()
{
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update()
{
    // Delta time
    float ticks = static_cast<float>(GetTime());
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    gPulseTime += 1.0f * deltaTime;

    // Jiwoo
    if (gJiwooPosition.x < 170.0f)
    {
        gJiwooPosition.x += 16.0f * deltaTime;
        gJiwooPosition.y += 8.0f * deltaTime;
    }
    else
    {
        gJiwooPosition = { 130.0f, 270.0f };
    }

    // Carmen
    if (gCarmenPosition.x > 390.0f)
    {
        gCarmenPosition.x += -12.0f * deltaTime;
        gCarmenPosition.y += 9.0f * deltaTime;
    }
    else
    {
        gCarmenPosition = { 430.0f, 250.0f };
    }

    // Yuha
    if (gYuhaPosition.x < 770.0f)
    {
        gYuhaPosition.x += 10.0f * deltaTime;
        gYuhaPosition.y += -6.0f * deltaTime;
    }
    else
    {
        gYuhaPosition = { 730.0f, 290.0f };
    }

    // Stella
    if (gStellaPosition.x > 990.0f)
    {
        gStellaPosition.x += -14.0f * deltaTime;
        gStellaPosition.y += -7.0f * deltaTime;
    }
    else
    {
        gStellaPosition = { 1030.0f, 280.0f };
    }

    // Juun
    if (gJuunPosition.x < 170.0f)
    {
        gJuunPosition.x += 20.0f * deltaTime;
        gJuunPosition.y += 10.0f * deltaTime;
    }
    else
    {
        gJuunPosition = { 130.0f, 480.0f };
    }

    // Ana
    if (gAnaPosition.x > 280.0f)
    {
        gAnaPosition.x += -10.0f * deltaTime;
        gAnaPosition.y += 5.0f * deltaTime;
    }
    else
    {
        gAnaPosition = { 300.0f, 30.0f };
    }

    // Ian
    if (gIanPosition.x < 770.0f)
    {
        gIanPosition.x += 8.0f * deltaTime;
        gIanPosition.y += 6.0f * deltaTime;
    }
    else
    {
        gIanPosition = { 730.0f, 490.0f };
    }

    // Yeon
    if (gYeonPosition.x > 990.0f)
    {
        gYeonPosition.x += -18.0f * deltaTime;
        gYeonPosition.y += -12.0f * deltaTime;
    }
    else
    {
        gYeonPosition = { 1030.0f, 520.0f };
    }

    gAngle += (gDirection == RIGHT) ? 20.0f * deltaTime : -20.0f * deltaTime;
    if      (gAngle >  LIMIT_ANGLE) gDirection = LEFT;
    else if (gAngle < -LIMIT_ANGLE) gDirection = RIGHT;

    gScale = {
        BASE_SIZE.x + MAX_AMP * cos(gPulseTime),
        BASE_SIZE.y + MAX_AMP * cos(gPulseTime)
    };
}

void render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // The title and member names are printed in a static background texture
    Rectangle backgroundTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gBackgroundTexture.width),
        static_cast<float>(gBackgroundTexture.height)
    };
    Rectangle backgroundDestinationArea = {
        0.0f, 0.0f,
        static_cast<float>(SCREEN_WIDTH),
        static_cast<float>(SCREEN_HEIGHT)
    };
    Vector2 backgroundOrigin = { 0.0f, 0.0f };
    DrawTexturePro(
        gBackgroundTexture, backgroundTextureArea, backgroundDestinationArea,
        backgroundOrigin, 0.0f, WHITE
    );

    // Jiwoo texture 
    Rectangle jiwooTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gJiwooTexture.width),
        static_cast<float>(gJiwooTexture.height)
    };
    Rectangle jiwooDestinationArea = {
        gJiwooPosition.x, gJiwooPosition.y,
        170.0f, 170.0f
    };
    Vector2 jiwooOrigin = { 85.0f, 85.0f };
    DrawTexturePro(
        gJiwooTexture, jiwooTextureArea, jiwooDestinationArea,
        jiwooOrigin, 0.0f, WHITE
    );

    // Carmen texture
    Rectangle carmenTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gCarmenTexture.width),
        static_cast<float>(gCarmenTexture.height)
    };
    Rectangle carmenDestinationArea = {
        gCarmenPosition.x, gCarmenPosition.y,
        170.0f, 170.0f
    };
    Vector2 carmenOrigin = { 85.0f, 85.0f };
    DrawTexturePro(
        gCarmenTexture, carmenTextureArea, carmenDestinationArea,
        carmenOrigin, 0.0f, WHITE
    );

    // Yuha texture 
    Rectangle yuhaTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gYuhaTexture.width),
        static_cast<float>(gYuhaTexture.height)
    };
    Rectangle yuhaDestinationArea = {
        gYuhaPosition.x, gYuhaPosition.y,
        170.0f, 170.0f
    };
    Vector2 yuhaOrigin = { 85.0f, 85.0f };
    DrawTexturePro(
        gYuhaTexture, yuhaTextureArea, yuhaDestinationArea,
        yuhaOrigin, 0.0f, WHITE
    );

    // Stella texture
    Rectangle stellaTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gStellaTexture.width),
        static_cast<float>(gStellaTexture.height)
    };
    Rectangle stellaDestinationArea = {
        gStellaPosition.x, gStellaPosition.y,
        170.0f, 170.0f
    };
    Vector2 stellaOrigin = { 85.0f, 85.0f };
    DrawTexturePro(
        gStellaTexture, stellaTextureArea, stellaDestinationArea,
        stellaOrigin, 0.0f, WHITE
    );

    // Juun texture
    Rectangle juunTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gJuunTexture.width),
        static_cast<float>(gJuunTexture.height)
    };
    Rectangle juunDestinationArea = {
        gJuunPosition.x, gJuunPosition.y,
        gScale.x, gScale.y
    };
    Vector2 juunOrigin = { gScale.x / 2.0f, gScale.y / 2.0f };
    DrawTexturePro(
        gJuunTexture, juunTextureArea, juunDestinationArea,
        juunOrigin, 0.0f, WHITE
    );

    // Ana texture 
    Rectangle anaTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gAnaTexture.width),
        static_cast<float>(gAnaTexture.height)
    };
    Rectangle anaDestinationArea = {
        gJuunPosition.x + gAnaPosition.x, gJuunPosition.y + gAnaPosition.y,
        170.0f, 170.0f
    };
    Vector2 anaOrigin = { 85.0f, 85.0f };
    DrawTexturePro(
        gAnaTexture, anaTextureArea, anaDestinationArea,
        anaOrigin, gAngle, WHITE
    );

    // Ian texture 
    Rectangle ianTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gIanTexture.width),
        static_cast<float>(gIanTexture.height)
    };
    Rectangle ianDestinationArea = {
        gIanPosition.x, gIanPosition.y,
        170.0f, 170.0f
    };
    Vector2 ianOrigin = { 85.0f, 85.0f };
    DrawTexturePro(
        gIanTexture, ianTextureArea, ianDestinationArea,
        ianOrigin, 0.0f, WHITE
    );

    // Yeon texture 
    Rectangle yeonTextureArea = {
        0.0f, 0.0f,
        static_cast<float>(gYeonTexture.width),
        static_cast<float>(gYeonTexture.height)
    };
    Rectangle yeonDestinationArea = {
        gYeonPosition.x, gYeonPosition.y,
        170.0f, 170.0f
    };
    Vector2 yeonOrigin = { 85.0f, 85.0f };
    DrawTexturePro(
        gYeonTexture, yeonTextureArea, yeonDestinationArea,
        yeonOrigin, 0.0f, WHITE
    );

    EndDrawing();
}

void shutdown()
{
    UnloadTexture(gBackgroundTexture);
    UnloadTexture(gJiwooTexture);
    UnloadTexture(gCarmenTexture);
    UnloadTexture(gYuhaTexture);
    UnloadTexture(gStellaTexture);
    UnloadTexture(gJuunTexture);
    UnloadTexture(gAnaTexture);
    UnloadTexture(gIanTexture);
    UnloadTexture(gYeonTexture);
    CloseWindow();
}

int main(void)
{
    initialise();
    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }
    shutdown();
    return 0;
}
