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

    // build "i64 main" function
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let fun_type = llvm::core::LLVMFunctionType(int_type, ptr::null_mut(), 0, 0);
    let fun_name = CString::new("main").unwrap();
    let main_fun = llvm::core::LLVMAddFunction(module, fun_name.as_ptr(), fun_type);

    // build "i64 inc(i64)" function
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let arg_types = &mut [int_type];
    let fun_type = llvm::core::LLVMFunctionType(int_type, arg_types.as_mut_ptr(), 1, 0);
    let fun_name = CString::new("inc").unwrap();
    let inc_fun = llvm::core::LLVMAddFunction(module, fun_name.as_ptr(), fun_type);

    // create "entry" basic block in "main" function
    let bb_name = CString::new("entry").unwrap();
    let bb = llvm::core::LLVMAppendBasicBlockInContext(context, main_fun, bb_name.as_ptr());

    // Set next insert position
    llvm::core::LLVMPositionBuilderAtEnd(builder, bb);

    // allocate `x` on stack (memory)
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let cname = CString::new("x").unwrap();
    let pointer_a = llvm::core::LLVMBuildAlloca(builder, int_type, cname.as_ptr());

    // store 2 to `x`.
    let typ = llvm::core::LLVMInt64TypeInContext(context);
    let iv = llvm::core::LLVMConstInt(typ, 2, 0);
    llvm::core::LLVMBuildStore(builder, iv, pointer_a);

    // load a to x (register)
    let name = CString::new("x").unwrap();
    let new_a = llvm::core::LLVMBuildLoad(builder, pointer_a, name.as_ptr());

    // call inc(x)
    let args = &mut [new_a];
    let cname = CString::new("ret").unwrap();
    let ret = llvm::core::LLVMBuildCall(builder,
                                        inc_fun,
                                        args.as_mut_ptr(),
                                        args.len() as u32,
                                        cname.as_ptr());

    // return ret
    llvm::core::LLVMBuildRet(builder, ret);

    // create basic block named "entry"
    let bb_name = CString::new("entry").unwrap();
    let inc_bb = llvm::core::LLVMAppendBasicBlockInContext(context, inc_fun, bb_name.as_ptr());

    // Set next insert positoin
    llvm::core::LLVMPositionBuilderAtEnd(builder, inc_bb);

    // load 1st arguments
    let lh = llvm::core::LLVMGetParam(inc_fun, 0);

    // create const value 1
    let typ = llvm::core::LLVMInt64TypeInContext(context);
    let rh = llvm::core::LLVMConstInt(typ, 1, 0);

    // 1 + 0th argument
    let name = CString::new("add_value").unwrap();
    let ret = llvm::core::LLVMBuildAdd(builder, lh, rh, name.as_ptr());

    // return value
    llvm::core::LLVMBuildRet(builder, ret);

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
