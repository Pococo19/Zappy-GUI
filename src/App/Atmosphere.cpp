/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** Atmosphere.cpp
*/

#include <App/Atmosphere.hpp>

/*
 * const std::string absolute_vert = zap::Filename::getPath("shader.vert");
 * const std::string absolute_frag = zap::Filename::getPath("shader.frag");
 * Shader shader = LoadShader(absolute_vert.c_str(), absolute_frag.c_str());
 *
 * if (shader.id == 0) {
 *     throw exception::Error("....", "...);
 * }
 */

// Atmosphere.cpp

namespace zappy {

Atmosphere::Atmosphere(Shader &shader, std::shared_ptr<zap::ZapModel> model, std::shared_ptr<zap::ZapCamera> camera)
    : ShaderModel(shader, model, camera) {}

void Atmosphere::draw() const
{
    ShaderModel::draw();
}

} // namespace zappy