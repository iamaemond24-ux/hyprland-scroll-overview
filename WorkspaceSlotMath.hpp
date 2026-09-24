#pragma once

#include <cstdint>
#include <optional>

// Slot arithmetic for stepping the overview viewport across numbered workspaces.
//
// The strip normally only carries workspaces that actually exist, and Hyprland destroys an empty
// workspace as soon as nothing strong refers to it — so walking into an empty slot means creating it
// on arrival, and leaving one destroys it again. That makes the step boundaries pure arithmetic over
// slot numbers, deliberately kept free of Hyprland types so they can be exercised on the host rather
// than only by restarting the compositor.
//
// Numbered IDs are unique system-wide and are the numbers the user sees, so the viewport steps in ID
// space, not in `images` index space.
namespace ScrollOverview::Slots {

    // What a step needs to know.
    struct SContext {
        uint32_t current = 1; // slot the viewport is on
    };

    // The slot a step moves to, or nullopt when the step is refused.
    //
    // Both directions are unbounded: the caller creates the slot on arrival if it is not there yet, and
    // leaving it destroys it again. Workspace 1 is the one fixed end of the strip, because Hyprland has
    // no workspace 0 — the only step this refuses.
    //
    // The step depends on nothing but `current`, and that is deliberate. A bound read from the set of
    // existing workspaces looks reasonable and is not: the walk rewrites that set, so with nothing
    // populated the monitor's lowest existing slot *is* wherever the walker stands, which makes the
    // bound measure the walk instead of the strip.
    inline std::optional<uint32_t> stepTarget(const SContext& context, bool up) {
        if (up)
            return context.current + 1;

        if (context.current <= 1)
            return std::nullopt;

        return context.current - 1;
    }
}
