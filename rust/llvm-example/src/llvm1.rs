
// --------------------
// int main() {
//   a = 10;
//   b = 11;
//   ret = a + b;
//   return ret;
// }
// --------------------

extern crate llvm_sys as llvm;

use std::ffi::CString;
use std::ptr;
use self::llvm::prelude::*;

pub unsafe fn run() {
    // Get context
    let context = llvm::core::LLVMGetGlobalContext();
    // this instr is the same to `LLVMModuleCreateWithNameInCotnext("~~~~~", LLVMGetGlobalContext)`
    // let module = llvm::core::LLVMModuleCreateWithName("playground\0".as_ptr() as *const _);
    let v = CString::new("playground").unwrap();
    let module = llvm::core::LLVMModuleCreateWithNameInContext(v.as_ptr(), context);
    // Create a bulder not in a global context, but in this context
    // let builder = llvm::core::LLVMCreateBuilder();
    // LLVMCreateBuilder() is the same as LLVMCreateBuilderInContext(Get)
    let builder = llvm::core::LLVMCreateBuilderInContext(context);

    // build  a function named "main"
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let fun_type = llvm::core::LLVMFunctionType(int_type, ptr::null_mut(), 0, 0);
    let fun_name = CString::new("main").unwrap();
    let fun = llvm::core::LLVMAddFunction(module, fun_name.as_ptr(), fun_type);

    // create basic block in a global context
    let bb_name = CString::new("entry").unwrap();
    let bb = llvm::core::LLVMAppendBasicBlock(fun, bb_name.as_ptr());

    // Set next insert positoin
    llvm::core::LLVMPositionBuilderAtEnd(builder, bb);

    // allocate a
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let cname = CString::new("a").unwrap();
    let pointer_a = llvm::core::LLVMBuildAlloca(builder, int_type, cname.as_ptr());

    // allocate b
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let cname = CString::new("b").unwrap();
    let pointer_b = llvm::core::LLVMBuildAlloca(builder, int_type, cname.as_ptr());

    // set a to 10
    let typ = llvm::core::LLVMInt64TypeInContext(context);
    let iv = llvm::core::LLVMConstInt(typ, 10, 0);
    llvm::core::LLVMBuildStore(builder, iv, pointer_a);

    // set b to 11
    let typ = llvm::core::LLVMInt64TypeInContext(context);
    let iv = llvm::core::LLVMConstInt(typ, 11, 0);
    llvm::core::LLVMBuildStore(builder, iv, pointer_b);

    // load a to new_a
    let name = CString::new("new_a").unwrap();
    let new_a = llvm::core::LLVMBuildLoad(builder, pointer_a, name.as_ptr());

    // load b new_b
    let name = CString::new("new_b").unwrap();
    let new_b = llvm::core::LLVMBuildLoad(builder, pointer_b, name.as_ptr());

    let name = CString::new("add_value").unwrap();
    let ret = llvm::core::LLVMBuildAdd(builder, new_a, new_b, name.as_ptr());
    llvm::core::LLVMBuildRet(builder, ret);

    // output stdout
    llvm::core::LLVMDumpModule(module);

    // Clean up. Values created in the context mostly get cleaned up there.
    llvm::core::LLVMDisposeBuilder(builder);
    llvm::core::LLVMDisposeModule(module);
    llvm::core::LLVMContextDispose(context);
}
