/*
** EPITECH PROJECT, 2024
** GUI-ZAPPY
** File description:
** ModelAnim.hpp
*/

#pragma once

#include <ZapGUI/Drawable.hpp>
#include <ZapGUI/Drawable/ModelBase.hpp>

#include <memory>


namespace zap {

class ZapModelAnim final : public abstract::ModelBase, public abstract::Drawable
{

    public: 
        explicit ZapModelAnim(const std::string &glb_path);
        explicit ZapModelAnim(const Model &model);

        ~ZapModelAnim() override;

        void draw() const override;
        void update(const f32 dt) override;
        
        void _load_glb_animated(const std::string &glb_path);

    private:
        int _animCount = 0;
        f32 _frame = 0;
        ModelAnimation *_animations;
};
} // namespace zap