fn main() {
    let proj_dir = env!("CARGO_MANIFEST_DIR");

    println!("cargo:rerun-if-changed={}/lib/cmake-build", proj_dir);
    println!("cargo:rustc-link-search={}/lib/cmake-build", proj_dir);
}