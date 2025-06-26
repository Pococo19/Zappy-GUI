/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** ModelAnim.hpp
*/

#pragma once

#include <ZapGUI/Drawable.hpp>
#include <ZapGUI/Drawable/ModelBase.hpp>

namespace zap {

class ZapModelAnim : public abstract::ModelBase, public abstract::Drawable
{

    public:
        explicit ZapModelAnim(const std::string &glb_path);

        ~ZapModelAnim() override;

        void draw() const override;
        void update(const f32 dt) override;

    protected:
        i32 _anim_count = 0;
        i32 _frame = 0;
        i32 _anim_index = 0;
        ModelAnimation *_animations;

    private:
        void _load_glb_animated(const std::string &glb_path);
};
}// namespace zap
