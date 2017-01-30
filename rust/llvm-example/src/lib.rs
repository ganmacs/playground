pub mod codegen;
pub mod node;

use node::Node;

pub fn compile(insts: Vec<Node>) {
    unsafe {
        codegen::codegen(insts);
    }
}
