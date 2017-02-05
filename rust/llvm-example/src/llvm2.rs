// -------------------------------
// int main() {
//     a = 2;
//     if a {
//         a = 10
//     } else {
//         a = 11
//     }
//     return a;
// }
// --------------------------------

extern crate llvm_sys as llvm;
use std::ffi::CString;
use std::ptr;

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

    // set a to 2
    let typ = llvm::core::LLVMInt64TypeInContext(context);
    let iv = llvm::core::LLVMConstInt(typ, 2, 0);
    llvm::core::LLVMBuildStore(builder, iv, pointer_a);

    // load a to new_a
    let name = CString::new("new_a").unwrap();
    let new_a = llvm::core::LLVMBuildLoad(builder, pointer_a, name.as_ptr());

    // create if statment

    // let condition_value = codegen_node(cxt, builder, func, env, *condition);
    // let int_type = llvm::core::LLVMInt64TypeInContext(cxt);
    // let zero = llvm::core::LLVMConstInt(int_type, 0, 0);

    // let name = CString::new("is_nonzero").unwrap();
    // let is_nonzero = llvm::core::LLVMBuildICmp(builder,
    //                                            llvm::LLVMIntPredicate::LLVMIntNE,
    //                                            condition_value,
    //                                            zero,
    //                                                    name.as_ptr());

    //         let entry_name = CString::new("entry").unwrap();
    //         let then_block =
    //             llvm::core::LLVMAppendBasicBlockInContext(cxt, func, entry_name.as_ptr());
    //         let else_block =
    //             llvm::core::LLVMAppendBasicBlockInContext(cxt, func, entry_name.as_ptr());
    //         let merge_block =
    //             llvm::core::LLVMAppendBasicBlockInContext(cxt, func, entry_name.as_ptr());

    //         llvm::core::LLVMBuildCondBr(builder, is_nonzero, then_block, else_block);

    //         // then
    //         llvm::core::LLVMPositionBuilderAtEnd(builder, then_block);
    //         let then_return = codegen_node(cxt, builder, func, env, *then_body);
    //         llvm::core::LLVMBuildBr(builder, merge_block);
    //         let then_block = llvm::core::LLVMGetInsertBlock(builder);

    //         // else
    //         llvm::core::LLVMPositionBuilderAtEnd(builder, else_block);
    //         let else_return = codegen_node(cxt, builder, func, env, *else_body);
    //         llvm::core::LLVMBuildBr(builder, merge_block);
    //         let else_block = llvm::core::LLVMGetInsertBlock(builder);

    //         llvm::core::LLVMPositionBuilderAtEnd(builder, merge_block);

    //         let phi_name = CString::new("iftmp").unwrap();

    //         let phi = llvm::core::LLVMBuildPhi(builder, int_type, phi_name.as_ptr());

    //         let mut values = vec![then_return, else_return];
    //         let mut blocks = vec![then_block, else_block];

    //         llvm::core::LLVMAddIncoming(phi, values.as_mut_ptr(), blocks.as_mut_ptr(), 2);
    //         phi





    // output stdout
    llvm::core::LLVMDumpModule(module);

    // Clean up. Values created in the context mostly get cleaned up there.
    llvm::core::LLVMDisposeBuilder(builder);
    llvm::core::LLVMDisposeModule(module);
    llvm::core::LLVMContextDispose(context);
}
