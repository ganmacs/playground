// create if expression using phi fnction.
// -------------------------------
// int main() {
//   x = 2
//   return add(x)
// }
//
// int inc(int x) { return x + 1}
// --------------------------------

extern crate llvm_sys as llvm;
use std::ffi::CString;
use std::ptr;
use self::llvm::prelude::*;

pub unsafe fn run() {
    let context = llvm::core::LLVMGetGlobalContext();
    let mod_name = CString::new("playground").unwrap();
    let module = llvm::core::LLVMModuleCreateWithNameInContext(mod_name.as_ptr(), context);
    let builder = llvm::core::LLVMCreateBuilderInContext(context);

    // build a function named "main"
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let fun_type = llvm::core::LLVMFunctionType(int_type, ptr::null_mut(), 0, 0);
    let fun_name = CString::new("main").unwrap();
    let fun = llvm::core::LLVMAddFunction(module, fun_name.as_ptr(), fun_type);

    // create basic block named "entry"
    let bb_name = CString::new("entry").unwrap();
    let bb = llvm::core::LLVMAppendBasicBlockInContext(context, fun, bb_name.as_ptr());

    // Set next insert positoin
    llvm::core::LLVMPositionBuilderAtEnd(builder, bb);

    // allocate `x` on stack (memory)
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let cname = CString::new("x").unwrap();
    let pointer_a = llvm::core::LLVMBuildAlloca(builder, int_type, cname.as_ptr());

    // store 2 to `x`. `x` is a pointer.
    let typ = llvm::core::LLVMInt64TypeInContext(context);
    let iv = llvm::core::LLVMConstInt(typ, 2, 0);
    llvm::core::LLVMBuildStore(builder, iv, pointer_a);

    // load a to a_value (register)
    let name = CString::new("x").unwrap();
    let new_a = llvm::core::LLVMBuildLoad(builder, pointer_a, name.as_ptr());

    // build a function named "inc"
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let vk = &mut [int_type];
    let fun_type = llvm::core::LLVMFunctionType(int_type, vk.as_mut_ptr(), 1, 0);
    let fun_name = CString::new("inc").unwrap();
    let fun = llvm::core::LLVMAddFunction(module, fun_name.as_ptr(), fun_type);

    // create basic block named "entry"
    let bb_name = CString::new("entry").unwrap();
    let inc_bb = llvm::core::LLVMAppendBasicBlockInContext(context, fun, bb_name.as_ptr());

    // Set next insert positoin
    llvm::core::LLVMPositionBuilderAtEnd(builder, inc_bb);

    let typ = llvm::core::LLVMInt64TypeInContext(context);
    let iv = llvm::core::LLVMConstInt(typ, 2, 0);
    let vv = &mut [iv];

    let cname = CString::new("what").unwrap();
    llvm::core::LLVMBuildCall(builder, fun, vv.as_mut_ptr(), 1, cname.as_ptr());


    // dump code both stdout and file
    llvm::core::LLVMDumpModule(module);
    let out_file = CString::new("out.ll").unwrap();
    llvm::core::LLVMPrintModuleToFile(module, out_file.as_ptr(), ptr::null_mut());
    // llvm::core::LLVMDumpModule(module);

    // Clean up. Values created in the context mostly get cleaned up there.
    llvm::core::LLVMDisposeBuilder(builder);
    llvm::core::LLVMDisposeModule(module);
    llvm::core::LLVMContextDispose(context);
}
