# imgui-xeno: Dear ImGui backend for Xenoblade games

A [Dear ImGui](https://github.com/ocornut/imgui) backend that leverages NVN to support multiple Switch games.

## Main Credits

This implementation is a fork of [mp1r-practice-mod](https://github.com/MetroidPrimeModding/mp1r-practice-mod).   
In particular, it extracts [CraftyBoss](https://github.com/CraftyBoss)'s original NVN backend for use in other games.

It also includes some workarounds from the [Super Mario Odyssey adaptation](https://github.com/Amethyst-szs/smo-lunakit), 
made by [Amethyst-szs](https://github.com/Amethyst-szs).

## Building

This backend should be exported as a static library, for use in other modding projects.  
It is not recommended to use this repository as a base.

To get the library, install CMake, then run
```
make
```

The shared library (`libimgui_xeno.a`) can be found in the `cmake-build-minsizerel` directory.

## API usage

**The backend is meant to be launcher-agnostic**, meaning it can be used on all environments with access
to the NNSDK API: Skyline, exlaunch, etc.

To use the library in your project, you might also need to copy the `include/` directory.

### Example

```c
#include <imgui_xeno.h>
#include <imgui.h>

void ImGuiRenderCallback() {
    // For example, render the demo window
    ImGui::ShowDemoWindow();
}

void ImGuiInitCallback() {}

// Create a hook with your launcher of choice (e.g. skyline, exlaunch...)
// Replace the function "nvnBootstrapLoader" which has the same signature 
// as this hook.
void* NvnBootstrapHook(const char* name) {
    // get the pointer to the original function
    // (varies between launchers)
    void *originalFunction; 
    
    // let imgui_xeno handle it
    return imgui_xeno_bootstrap_hook(name, originalFunction);
}

int main() {
    // In your main function, initialize the library and register callbacks
    // (Make sure this is called before the nvnBootstrap hook)
    imgui_xeno_init(&ImGuiRenderCallback, &ImGuiInitCallback);
    return 0;
}
```

### skyline-rs

The library can also be statically linked to Rust code that uses [skyline-rs](https://github.com/skyline-rs/).

A working example can be found in the `examples/` directory.

```rust
// Also make sure the linker can find libimgui_xeno.a
#[link(name = "imgui_xeno")] 
extern "C" {
    fn imgui_xeno_init(init: *const c_void, draw: *const c_void);
    fn imgui_xeno_bootstrap_hook(name: *const c_char, original: *const c_void) -> *const c_void;
}

extern "C" {
    fn nvnBootstrapLoader(name: *const c_char) -> *const c_void;
}

unsafe extern "C" fn imgui_init() {}
unsafe extern "C" fn imgui_render() {}

#[skyline::hook(replace = nvnBootstrapLoader)]
unsafe fn nvn_bootstrap_hook(name: u64) -> u64 {
    imgui_xeno_bootstrap_hook(name, original!() as *const c_void)
}

#[skyline::main(name = "imgui_xeno_demo")]
pub fn main() {
    unsafe {
        imgui_xeno_init(
            imgui_init as *const c_void,
            imgui_render as *const c_void,
        );
        skyline::install_hooks!(nvn_bootstrap_hook);
    }
}
```

## Configuration

Most parameters can be configured in the `user_config` source directory.  
Particularly, you can add ImGui directives in the `imgui_user_config.h` file.

### Not Xenoblade?

Chances are this backend might also work in your game, even if it's not Xenoblade.  
You can try the provided configuration options to improve compatibility, or patch the backend directly.  
Note that if the required changes are too big to maintain for a non-Xenoblade title, it is probably
best that you fork this repository instead.

## Original repo credits

- [CraftyBoss](https://github.com/CraftyBoss/MP1R-Exlaunch-Base) - thanks for the base <3
- [exlaunch](https://github.com/shadowninja108/exlaunch/)
- [exlaunch-cmake](https://github.com/EngineLessCC/exlaunch-cmake/)
- [BDSP](https://github.com/Martmists-GH/BDSP)
- [Sanae](https://github.com/Sanae6)
- [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere)
- [oss-rtld](https://github.com/Thog/oss-rtld)
