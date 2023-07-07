use skyline::hook;
use skyline::libc::{c_char, c_void};

// This example works for all Xenoblade games.
// To build it, you can use the Makefile that builds both imgui-xeno and this example.
// Simply run "make" in the example's directory. To clean up, run "make clean".

#[link(name = "imgui_xeno")]
extern "C" {
    fn imgui_xeno_init(init: *const c_void, draw: *const c_void);

    fn imgui_xeno_bootstrap_hook(name: *const c_char, original_fn: *const c_void) -> *const c_void;

    // ImGui::ShowDemoWindow(bool *), provided by the static lib
    #[link_name = "_ZN5ImGui14ShowDemoWindowEPb"]
    fn imgui_show_demo_window(open: *const bool);
}

// Import nvnBootstrapLoader from main
extern "C" {
    fn nvnBootstrapLoader(name: *const c_char) -> *const c_void;
}

unsafe extern "C" fn on_imgui_init() {
    println!("ImGui initialization complete.");
}

unsafe extern "C" fn on_imgui_render() {
    let open = true;
    imgui_show_demo_window(&open as *const _);
}

#[hook(replace = nvnBootstrapLoader)]
unsafe fn nvn_bootstrap_hook(name: *const c_char) -> *const c_void {
    imgui_xeno_bootstrap_hook(name, original!() as *const c_void)
}

#[skyline::main(name = "skyline-rs-demo")]
pub fn main() {
    skyline::install_hook!(nvn_bootstrap_hook);

    unsafe {
        imgui_xeno_init(
            on_imgui_init as *const c_void,
            on_imgui_render as *const c_void
        );
    }
}
