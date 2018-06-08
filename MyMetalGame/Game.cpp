#include "GameFramework.hpp"

class Triangle
{
    Vector2 pos[3];
    Vector2 speed[3];
    Color colors[3];

public:
    Triangle(const Color& color) {
        for (int i = 0; i < 3; i++) {
            pos[i] = Vector2(Random::FloatRange(-1, 1), Random::FloatRange(-1, 1));
            speed[i] = Vector2(Random::FloatRange(-1, 1), Random::FloatRange(-1, 1));
        }
        colors[0] = color;
        colors[1] = color;
        colors[2] = color;
        colors[0] = Color::lightblue;
        colors[1] = Color::white;
        colors[2] = Color::blue.Alpha(0.0);
    }

    void Step() {
        for (int i = 0; i < 3; i++) {
            pos[i] += speed[i] * Time::deltaTime;
            if (pos[i].x > 1.0f) {
                pos[i].x = 1.0f;
                speed[i].x *= -1;
            }
            if (pos[i].x < -1.0f) {
                pos[i].x = -1.0f;
                speed[i].x *= -1;
            }
            if (pos[i].y > 1.0f) {
                pos[i].y = 1.0f;
                speed[i].y *= -1;
            }
            if (pos[i].y < -1.0f) {
                pos[i].y = -1.0f;
                speed[i].y *= -1;
            }
        }
    }

    void Draw() {
        FillTriangle(pos, colors);
    }
};

vector<Triangle *> triangles;
float t = 0.0f;

void Start()
{
    Color c1 = Color::white;
    Color c2 = Color::blue;
    for (int i = 0; i < 10; i++) {
        Color color = Color::Lerp(c1, c2, i / 99.0);
        triangles.push_back(new Triangle(color));
    }
}

void Update()
{
    t += Time::deltaTime;

    for (auto triangle : triangles) {
        triangle->Step();
    }

    Clear(Color::black);

    SetBlendMode(BlendModeAlpha);
    if (Input::GetKey(KeyCode::A)) {
        SetBlendMode(BlendModeScreen);
    } else if (Input::GetKey(KeyCode::S)) {
        SetBlendMode(BlendModeAdd);
    } else if (Input::GetKey(KeyCode::D)) {
        SetBlendMode(BlendModeMultiply);
    } else if (Input::GetKey(KeyCode::F)) {
        SetBlendMode(BlendModeInvert);
    } else if (Input::GetKey(KeyCode::G)) {
        SetBlendMode(BlendModeXOR);
    } else if (Input::GetKey(KeyCode::H)) {
        SetBlendMode(BlendModeCopy);
    } else if (Input::GetKey(KeyCode::J)) {
        SetBlendMode(BlendModeClear);
    }

    for (auto triangle : triangles) {
        triangle->Draw();
    }
}

