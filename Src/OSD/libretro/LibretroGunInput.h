#ifndef LIBRETRO_GUN_INPUT_H
#define LIBRETRO_GUN_INPUT_H

#include "CoreOptionsTypes.h"

namespace LibretroGunInput
{

struct State
{
    GunInput mode = GunInput::Hybrid;
    bool reloadProfile = false;
    bool reloadShortcut = true;
    bool mouseEdgeReload = false;
    bool cursorAtEdge = false;
    bool lightgunMoved = false;
    bool lightgunOffscreen = false;
    bool lightgunTrigger = false;
    bool lightgunReload = false;
    bool lightgunAuxA = false;
    bool mouseTrigger = false;
    bool mouseSecondary = false;
    bool analogTrigger = false;
    bool analogTriggerAlt = false;
    bool analogSecondary = false;
    bool analogSecondaryAlt = false;
};

struct Actions
{
    bool useLightgun = false;
    bool primary = false;
    bool secondary = false;
    bool physicalOffscreenReload = false;
    bool shortcutReload = false;
    bool mouseEdgeReload = false;
};

inline Actions Resolve(const State &state)
{
    const bool allowLightgun = state.mode == GunInput::Hybrid ||
                               state.mode == GunInput::Lightgun;
    const bool allowMouse = state.mode == GunInput::Hybrid ||
                            state.mode == GunInput::MouseAnalog ||
                            state.mode == GunInput::Mouse;
    const bool allowAnalog = state.mode == GunInput::Hybrid ||
                             state.mode == GunInput::MouseAnalog ||
                             state.mode == GunInput::AnalogSticks;
    const bool lightgunAction = allowLightgun &&
        (state.lightgunTrigger || state.lightgunReload ||
         state.lightgunAuxA || state.lightgunOffscreen);

    Actions actions;
    actions.useLightgun = state.mode == GunInput::Lightgun ||
        (state.mode == GunInput::Hybrid &&
         (state.lightgunMoved || lightgunAction));

    const bool lightgunPrimary = actions.useLightgun &&
                                 state.lightgunTrigger;
    const bool mousePrimary = allowMouse && state.mouseTrigger;
    const bool analogPrimary = allowAnalog &&
        (state.analogTrigger || state.analogTriggerAlt);

    if (state.reloadProfile)
    {
        // A real Libretro Lightgun supplies off-screen status directly. This
        // cabinet action must remain available independently of shortcuts.
        actions.physicalOffscreenReload = actions.useLightgun &&
            state.lightgunOffscreen && state.lightgunTrigger;
        actions.shortcutReload = state.reloadShortcut &&
            ((actions.useLightgun && state.lightgunReload) ||
             (allowMouse && state.mouseSecondary) ||
             (allowAnalog &&
              (state.analogSecondary || state.analogSecondaryAlt)));
        actions.mouseEdgeReload = state.mouseEdgeReload && allowMouse &&
            state.mouseTrigger && !actions.useLightgun && state.cursorAtEdge;

        actions.primary =
            (lightgunPrimary && !actions.physicalOffscreenReload) ||
            (mousePrimary && !actions.mouseEdgeReload) || analogPrimary;
        actions.secondary = actions.physicalOffscreenReload ||
                            actions.shortcutReload ||
                            actions.mouseEdgeReload;
        return actions;
    }

    actions.primary = lightgunPrimary || mousePrimary || analogPrimary;
    actions.secondary =
        (actions.useLightgun &&
         (state.lightgunAuxA ||
          (state.lightgunReload && !state.lightgunOffscreen))) ||
        (allowMouse && state.mouseSecondary) ||
        (allowAnalog && state.analogSecondary);
    return actions;
}

} // namespace LibretroGunInput

#endif
