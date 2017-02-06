pub mod llvm1;
pub mod llvm2;
pub mod llvm3;
pub mod llvm4;
pub mod codegen;
pub mod codegen2;
pub mod node;

use node::Node;

pub fn compile(insts: Vec<Node>) {
    unsafe {
        codegen::codegen(insts);
    }
}
