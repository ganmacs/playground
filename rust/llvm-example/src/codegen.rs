extern crate llvm_sys as llvm;

use std::collections::HashMap;
use std::ffi::CString;
use std::ptr;
use self::llvm::prelude::*;
use node::Node;

pub unsafe fn codegen(insts: Vec<Node>) {
    let context = llvm::core::LLVMContextCreate();
    let module = llvm::core::LLVMModuleCreateWithName("cool_module\0".as_ptr() as *const _);
    let builder = llvm::core::LLVMCreateBuilderInContext(context);

    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let function_type = llvm::core::LLVMFunctionType(int_type, ptr::null_mut(), 0, 0);
    let function =
        llvm::core::LLVMAddFunction(module, b"cool_module\0".as_ptr() as *const _, function_type);
    let bb = llvm::core::LLVMAppendBasicBlockInContext(context,
                                                       function,
                                                       b"entry\0".as_ptr() as *const _);
    llvm::core::LLVMPositionBuilderAtEnd(builder, bb);

    let env = &mut HashMap::new();
    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let zero = llvm::core::LLVMConstInt(int_type, 0, 0);
    let mut ret = zero;

    for n in insts {
        ret = codegen_node(context, builder, function, env, n);
    }

    // Emit a `ret void` into the function
    llvm::core::LLVMBuildRet(builder, ret);

    // Dump the module as IR to stdout.
    llvm::core::LLVMDumpModule(module);
    let out_file = CString::new("out.ll").unwrap();
    llvm::core::LLVMPrintModuleToFile(module, out_file.as_ptr(), ptr::null_mut());


    // Clean up. Values created in the context mostly get cleaned up there.
    llvm::core::LLVMDisposeBuilder(builder);
    llvm::core::LLVMDisposeModule(module);
    llvm::core::LLVMContextDispose(context);
}

unsafe fn codegen_node(cxt: LLVMContextRef,
                       builder: LLVMBuilderRef,
                       func: LLVMValueRef,
                       env: &mut HashMap<String, LLVMValueRef>,
                       n: Node)
                       -> LLVMValueRef {
    match n {
        Node::Aref(n) => {
            let val = env.get(&n).unwrap();
            let name = CString::new(n).unwrap();
            llvm::core::LLVMBuildLoad(builder, *val, name.as_ptr())
        }
        Node::Assgn(name, value) => {
            let new_value = codegen_node(cxt, builder, func, env, *value);

            let pointer = llvm_alloc_int(cxt, builder, &name);
            llvm::core::LLVMBuildStore(builder, new_value, pointer);
            env.insert(name.to_owned(), pointer);

            new_value
        }
        Node::Int(n) => {
            let v = llvm::core::LLVMInt64TypeInContext(cxt);
            llvm::core::LLVMConstInt(v, n, 0)
        }
        Node::Add(l, r) => {
            let ll = codegen_node(cxt, builder, func, env, *l);
            let rr = codegen_node(cxt, builder, func, env, *r);
            let name = CString::new("add_value").unwrap();
            llvm::core::LLVMBuildAdd(builder, ll, rr, name.as_ptr())
        }
        Node::Sub(l, r) => {
            let ll = codegen_node(cxt, builder, func, env, *l);
            let rr = codegen_node(cxt, builder, func, env, *r);
            let name = CString::new("sub_value").unwrap();
            llvm::core::LLVMBuildSub(builder, ll, rr, name.as_ptr())
        }
        Node::If(condition, then_body, else_body) => {
            let condition_value = codegen_node(cxt, builder, func, env, *condition);
            let int_type = llvm::core::LLVMInt64TypeInContext(cxt);
            let zero = llvm::core::LLVMConstInt(int_type, 0, 0);

            let name = CString::new("is_nonzero").unwrap();
            let is_nonzero = llvm::core::LLVMBuildICmp(builder,
                                                       llvm::LLVMIntPredicate::LLVMIntNE,
                                                       condition_value,
                                                       zero,
                                                       name.as_ptr());

            let entry_name = CString::new("entry").unwrap();
            let then_block =
                llvm::core::LLVMAppendBasicBlockInContext(cxt, func, entry_name.as_ptr());
            let else_block =
                llvm::core::LLVMAppendBasicBlockInContext(cxt, func, entry_name.as_ptr());
            let merge_block =
                llvm::core::LLVMAppendBasicBlockInContext(cxt, func, entry_name.as_ptr());

            llvm::core::LLVMBuildCondBr(builder, is_nonzero, then_block, else_block);

            // then
            llvm::core::LLVMPositionBuilderAtEnd(builder, then_block);
            let then_return = codegen_node(cxt, builder, func, env, *then_body);
            llvm::core::LLVMBuildBr(builder, merge_block);
            let then_block = llvm::core::LLVMGetInsertBlock(builder);

            // else
            llvm::core::LLVMPositionBuilderAtEnd(builder, else_block);
            let else_return = codegen_node(cxt, builder, func, env, *else_body);
            llvm::core::LLVMBuildBr(builder, merge_block);
            let else_block = llvm::core::LLVMGetInsertBlock(builder);

            llvm::core::LLVMPositionBuilderAtEnd(builder, merge_block);

            let phi_name = CString::new("iftmp").unwrap();

            let phi = llvm::core::LLVMBuildPhi(builder, int_type, phi_name.as_ptr());

            let mut values = vec![then_return, else_return];
            let mut blocks = vec![then_block, else_block];

            llvm::core::LLVMAddIncoming(phi, values.as_mut_ptr(), blocks.as_mut_ptr(), 2);
            phi
        }
    }
}

pub unsafe fn playground() {
    // Get context
    let context = llvm::core::LLVMGetGlobalContext();
    // this instr is the same to `LLVMModuleCreateWithNameInCotnext("~~~~~", LLVMGetGlobalContext)`
    // let module = llvm::core::LLVMModuleCreateWithName("playground\0".as_ptr() as *const _);
    let module = llvm::core::LLVMModuleCreateWithNameInContext("playground\0".as_ptr() as *const _,
                                                               context);
    // Create a bulder not in a global context, but in this context
    // let builder = llvm::core::LLVMCreateBuilder();
    // LLVMCreateBuilder() is the same as LLVMCreateBuilderInContext(Get)
    let builder = llvm::core::LLVMCreateBuilderInContext(context);

    let int_type = get_int64_in_context(context);
    let function_type = llvm::core::LLVMFunctionType(int_type, ptr::null_mut(), 0, 0);
    let function =
        llvm::core::LLVMAddFunction(module, b"main\0".as_ptr() as *const _, function_type);


    // output stdout
    llvm::core::LLVMDumpModule(module);

    // Clean up. Values created in the context mostly get cleaned up there.
    llvm::core::LLVMDisposeBuilder(builder);
    llvm::core::LLVMDisposeModule(module);
    llvm::core::LLVMContextDispose(context);
}

fn get_int64_in_context(ctx: LLVMContextRef) -> LLVMTypeRef {
    unsafe { llvm::core::LLVMInt64TypeInContext(ctx) }
}

unsafe fn llvm_alloc_int(ctx: LLVMContextRef, builder: LLVMBuilderRef, name: &str) -> LLVMValueRef {
    let int_type = llvm::core::LLVMInt64TypeInContext(ctx);
    let cname = CString::new(name.as_bytes()).unwrap();
    llvm::core::LLVMBuildAlloca(builder, int_type, cname.as_ptr())
}
