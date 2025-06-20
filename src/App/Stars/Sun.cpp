/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Sun.cpp
*/

#define ZAP_USE_RAYLIB_MATH
#include <App/Maths/Maths.hpp>
#include <App/Stars/Sun.hpp>

#include <ZapGUI/Filename.hpp>

/**
* public
*/

zappy::Sun::Sun(const std::shared_ptr<zap::ZapCamera> &camera, const f32 zappy_radius) : zap::ShaderModel(camera)
{
    _init();
    _model->setPosition({zappy_radius * 4.5f + zappy_radius, 0.0f, 0.0f});
    _zappy_radius = zappy_radius + 0.5f;
    _stars = LoadModelFromMesh(GenMeshSphere(0.05f, 4, 4));
    _sun_flare = LoadTexture(zap::Filename::getPath(ZAP_SUN_FLARE).c_str());
}

void zappy::Sun::addPlanet(const std::shared_ptr<zappy::BasePlanet> &planet)
{
    _planets.push_back(planet);
}

void zappy::Sun::draw() const
{
    const f32 time = static_cast<f32>(GetTime());

    _model->draw();

    for (u32 i = 0; i < _stars_positions.size(); ++i) {
        const Vector3 &pos = _stars_positions[i];
        const f32 twinkle = 0.5f + 0.5f * sinf(time * 3.0f + static_cast<f32>(i));

        DrawModelEx(_stars, pos, {0, 1, 0}, 0.0f, {1, 1, 1}, ColorAlpha(WHITE, twinkle));
    }
}

bool zappy::Sun::has2D() const
{
    return true;
}

/**
 * 2D flare and bloom effects
 */

static constexpr Color flare_colors[] = {
    {255, 100, 100, 255},//<< Red
    {100, 255, 100, 255},//<< Green
    {100, 100, 255, 255},//<< Blue
    {255, 255, 100, 255} //<< Yellow
};

static void _draw_lens_flare(const Vector2 &sun_pos, const Vector2 &screen_center, const f32 alpha, const Texture2D &sun_flare)
{
    const Vector2 sun_to_center = Vector2Subtract(screen_center, sun_pos);
    const f32 time = static_cast<f32>(GetTime());

    for (u8 i = 1; i <= 4; ++i) {
        const f32 t = static_cast<f32>(i) * 0.2f;
        const Vector2 flare_pos = Vector2Add(sun_pos, Vector2Scale(sun_to_center, t));

        const f32 flare_size = 50.0f + i * 15.0f;
        const f32 flare_alpha = alpha * (0.3f - i * 0.05f);

        if (flare_alpha <= EPSILON) {
            continue;
        }

        const Rectangle src = {0, 0, static_cast<f32>(sun_flare.width), static_cast<f32>(sun_flare.height)};
        const Rectangle dst = {flare_pos.x - flare_size * 0.5f, flare_pos.y - flare_size * 0.5f, flare_size, flare_size};

        const Color flare_color = ColorAlpha(flare_colors[i - 1], flare_alpha);

        DrawTexturePro(sun_flare, src, dst, {0, 0}, time * 10.0f * i, flare_color);
    }
}

static void _draw_bloom(const Vector2 &sun_pos, const f32 size, const f32 alpha)
{
    BeginBlendMode(BLEND_ALPHA);

    for (u8 i = 0.f; i < 3.f; ++i) {
        const f32 bloom_size = size * (1.0f + i * 0.5f);
        const f32 bloom_alpha = alpha * (0.1f / (i + 1));

        DrawCircleGradient(static_cast<i32>(sun_pos.x), static_cast<i32>(sun_pos.y), bloom_size * 0.5f, ColorAlpha({255, 255, 200, 255}, bloom_alpha),
            ColorAlpha(BLANK, 0.0f));
    }

    EndBlendMode();
}

void zappy::Sun::draw2D() const
{
    if (!_camera->sees(_model->getPosition())) {
        return;
    }

    const Vector2 screen_pos = GetWorldToScreen(_model->getPosition(), _camera->get());
    const Vector2 center = {static_cast<f32>(GetScreenWidth()) / 2.0f, static_cast<f32>(GetScreenHeight()) / 2.0f};
    const f32 dist_to_sun = Vector3Distance(_camera->get().position, _model->getPosition());
    const f32 time = static_cast<f32>(GetTime());

    /** @brief calculate dynamic flare size based on distance to the sun */
    constexpr f32 base_flare_size = 400.0f;
    const f32 distance_factor = std::clamp(50.0f / dist_to_sun, 0.1f, 2.0f);
    const f32 flare_size = base_flare_size * distance_factor;

    /** @brief calculate the distance from the screen position to the center of the screen */
    const f32 center_dist = Vector2Distance(screen_pos, center);
    const f32 screen_diagonal = sqrtf(static_cast<f32>(GetScreenWidth() * GetScreenWidth() + GetScreenHeight() * GetScreenHeight()));

    /** @brief calculate atmospheric fade based on distance from the center of the screen */
    const f32 atmospheric_fade = 1.0f - powf(Clamp(center_dist / (screen_diagonal * 0.4f), 0.0f, 1.0f), 1.5f);

    const f32 pulse = 0.8f + 0.2f * sinf(time * 0.5f);
    const f32 final_alpha = atmospheric_fade * pulse;

    if (final_alpha <= EPSILON) {
        return;
    }

    BeginBlendMode(BLEND_ADDITIVE);

    /** @brief main sun glow */
    {
        const f32 glow_size = flare_size * 1.5f;
        const Rectangle src = {0, 0, static_cast<f32>(_sun_flare.width), static_cast<f32>(_sun_flare.height)};
        const Rectangle dst = {screen_pos.x - glow_size * 0.5f, screen_pos.y - glow_size * 0.5f, glow_size, glow_size};
        const Vector2 origin = {0, 0};
        const Color glow_color = ColorAlpha({255, 200, 100, 255}, final_alpha * 0.3f);

        DrawTexturePro(_sun_flare, src, dst, origin, 0.0f, glow_color);
    }

    /** @brief draw lens flare effects */
    {
        const Rectangle src = {0, 0, static_cast<f32>(_sun_flare.width), static_cast<f32>(_sun_flare.height)};
        const Rectangle dst = {screen_pos.x - flare_size * 0.5f, screen_pos.y - flare_size * 0.5f, flare_size, flare_size};
        const Vector2 origin = {0, 0};
        const Color core_color = ColorAlpha({255, 255, 200, 255}, final_alpha * 0.6f);

        DrawTexturePro(_sun_flare, src, dst, origin, 0.0f, core_color);
    }

    /** @brief draw the center of the sun */
    {
        const f32 center_size = flare_size * 0.3f;
        const Rectangle src = {0, 0, static_cast<f32>(_sun_flare.width), static_cast<f32>(_sun_flare.height)};
        const Rectangle dst = {screen_pos.x - center_size * 0.5f, screen_pos.y - center_size * 0.5f, center_size, center_size};
        const Vector2 origin = {0, 0};
        const Color center_color = ColorAlpha(WHITE, final_alpha * 0.9f);

        DrawTexturePro(_sun_flare, src, dst, origin, 0.0f, center_color);
    }

    if (center_dist < 100.0f) {
        _draw_lens_flare(screen_pos, center, final_alpha * 0.5f, _sun_flare);
    }

    EndBlendMode();
    _draw_bloom(screen_pos, flare_size, final_alpha);
}

/**
 * update
 */

void zappy::Sun::update(const f32 dt)
{
    constexpr Vector3 light_color = {1.0f, 0.95f, 0.8f};
    constexpr f32 light_intensity = 1.0f;

    /** @brief orbit the sun around the center of the zappy planet lol */
    const Vector3 orbit_position = maths::orbit_position(0.2f, _zappy_radius, dt, 5.5f);

    _model->setPosition(orbit_position);

    /** @brief rotate the sun around its own axis */
    _rotation += 0.5f;
    _model->setRotation({0.0f, _rotation, 0.0f});

    SetShaderValue(_shader, _timeLoc, &dt, SHADER_UNIFORM_FLOAT);
    SetShaderValue(_shader, _viewPosLoc, &_camera->get().position, SHADER_UNIFORM_VEC3);

    for (const auto &planet : _planets) {
        planet->applyLighting(orbit_position, light_color, light_intensity);
    }
}

/**
* protected
*/

void zappy::Sun::_init()
{
    const Mesh sun_mesh = GenMeshSphere(2.0f, 64, 64);
    const Model sun_model = LoadModelFromMesh(sun_mesh);

    _model = std::make_shared<zap::ZapModel>(sun_model);
    _shader = LoadShader(zap::Filename::getPath(ZAP_SHADER_SUN_VERT).c_str(), zap::Filename::getPath(ZAP_SHADER_SUN_FRAG).c_str());

    _timeLoc = GetShaderLocation(_shader, "time");
    _viewPosLoc = GetShaderLocation(_shader, "viewPos");

    _model->setShader(_shader);

    for (u32 i = 0; i < 500; ++i) {
        const f32 theta = maths::random<f32>(0.0f, 2.0f * PI);
        const f32 phi = acosf(maths::random<f32>(-1.0f, 1.0f));

        const f32 x = sinf(phi) * cosf(theta);
        const f32 y = sinf(phi) * sinf(theta);
        const f32 z = cosf(phi);

        const f32 radius = maths::random<f32>(15.0f, 50.0f);

        _stars_positions.push_back({x * radius, y * radius, z * radius});
    }
}
