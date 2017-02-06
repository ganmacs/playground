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
    let condition_value = new_a;
    // create 0 value
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let zero = llvm::core::LLVMConstInt(int_type, 0, 0);

    // create an icmp instruction which compare whether a condition value is not zero
    let name = CString::new("is_nonzero").unwrap();
    let is_nonzero = llvm::core::LLVMBuildICmp(builder,
                                               llvm::LLVMIntPredicate::LLVMIntNE,
                                               condition_value,
                                               zero,
                                               name.as_ptr());

    // create a basic blocks "then", "else", "merge"
    let entry_name = CString::new("entry").unwrap();
    let then_block = llvm::core::LLVMAppendBasicBlockInContext(context, fun, entry_name.as_ptr());
    let else_block = llvm::core::LLVMAppendBasicBlockInContext(context, fun, entry_name.as_ptr());
    let merge_block = llvm::core::LLVMAppendBasicBlockInContext(context, fun, entry_name.as_ptr());

    llvm::core::LLVMBuildCondBr(builder, is_nonzero, then_block, else_block);

    // -- Then block --
    // set a inserstion position in "then" basic block
    llvm::core::LLVMPositionBuilderAtEnd(builder, then_block);

    // allocate a
    // let int_type = llvm::core::LLVMInt64TypeInContext(context);
    // let cname = CString::new("a").unwrap();
    // let pointer_a = llvm::core::LLVMBuildAlloca(builder, int_type, cname.as_ptr());

    // load a to then_a
    // let name = CString::new("then_a").unwrap();
    // let then_a = llvm::core::LLVMBuildLoad(builder, pointer_a, name.as_ptr());

    // a = 10
    let typ = llvm::core::LLVMInt64TypeInContext(context);
    let iv = llvm::core::LLVMConstInt(typ, 10, 0);
    llvm::core::LLVMBuildStore(builder, iv, pointer_a);

    // let then_return = codegen_node(cxt, builder, func, env, *then_body);
    // llvm::core::LLVMBuildBr(builder, merge_block);
    // let then_block = llvm::core::LLVMGetInsertBlock(builder);

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
    // llvm::core::LLVMDumpModule(module);

    // Instead of dumping to stdout, let's write out the IR to `out.ll`
    // let out_file = CString::new("out.ll").unwrap();
    // llvm::core::LLVMPrintModuleToFile(module, out_file.as_ptr(), ptr::null_mut());
    llvm::core::LLVMDumpModule(module);


    // Clean up. Values created in the context mostly get cleaned up there.
    llvm::core::LLVMDisposeBuilder(builder);
    llvm::core::LLVMDisposeModule(module);
    llvm::core::LLVMContextDispose(context);
}
