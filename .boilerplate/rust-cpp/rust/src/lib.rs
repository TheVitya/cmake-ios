extern crate cxx;

#[cxx::bridge]
mod {{.ModuleName}}C {
    #[namespace = "{{.ModuleName}}Rust"]
    extern "Rust" {
        type RustExample;

        fn example_fn(&self);

        fn rust_fn();
    }

    unsafe extern "C++" {
        include!("{{.ModuleName}}/{{.ModuleName}}.hpp");

        fn c_fn();
    }
}

struct RustExample;

impl RustExample {
    fn example_fn(&self) {}
}

fn rust_fn() {
    {{.ModuleName}}C::c_fn();
}
