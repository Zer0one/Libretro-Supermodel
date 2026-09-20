#include "Src/OSD/libretro/LibretroGunInput.h"

#include <cstdlib>
#include <iostream>

namespace
{
void Check(bool condition, const char *message)
{
    if (condition)
        return;
    std::cerr << "FAIL: " << message << '\n';
    std::exit(1);
}
}

int main()
{
    using LibretroGunInput::Actions;
    using LibretroGunInput::Resolve;
    using LibretroGunInput::State;

    State state;
    state.reloadProfile = true;
    state.mouseTrigger = true;
    Actions actions = Resolve(state);
    Check(actions.primary && !actions.secondary && !actions.useLightgun,
          "Standard keeps an ordinary mouse shot on-screen");

    state = {};
    state.reloadProfile = true;
    state.reloadShortcut = false;
    state.lightgunOffscreen = true;
    state.lightgunTrigger = true;
    actions = Resolve(state);
    Check(actions.useLightgun && !actions.primary && actions.secondary &&
              actions.physicalOffscreenReload,
          "Physical off-screen Trigger reloads even when shortcuts are disabled");

    state = {};
    state.reloadProfile = true;
    state.reloadShortcut = false;
    state.lightgunReload = true;
    state.mouseSecondary = true;
    state.analogSecondary = true;
    state.analogSecondaryAlt = true;
    actions = Resolve(state);
    Check(!actions.primary && !actions.secondary,
          "Disabled shortcut ignores Lightgun, Mouse and RetroPad reload aliases");

    state.reloadShortcut = true;
    actions = Resolve(state);
    Check(actions.secondary && actions.shortcutReload,
          "Enabled shortcut accepts explicit reload inputs");

    state = {};
    state.reloadProfile = true;
    state.mode = GunInput::Mouse;
    state.mouseTrigger = true;
    state.cursorAtEdge = true;
    actions = Resolve(state);
    Check(actions.primary && !actions.secondary,
          "Mouse edge remains an on-screen shot by default");

    state.mouseEdgeReload = true;
    actions = Resolve(state);
    Check(!actions.primary && actions.secondary && actions.mouseEdgeReload,
          "Optional Mouse edge reload converts edge Trigger to reload");

    state = {};
    state.reloadProfile = true;
    state.lightgunMoved = true;
    state.mouseTrigger = true;
    state.cursorAtEdge = true;
    state.mouseEdgeReload = true;
    actions = Resolve(state);
    Check(actions.useLightgun && actions.primary && !actions.secondary,
          "Lightgun ownership prevents a Mouse edge false positive");

    state = {};
    state.lightgunOffscreen = true;
    state.lightgunTrigger = true;
    state.lightgunAuxA = true;
    actions = Resolve(state);
    Check(actions.primary && actions.secondary &&
              !actions.physicalOffscreenReload,
          "Non-reload Gun games preserve independent left and right shots");

    std::cout << "Gun input checks passed\n";
    return 0;
}
