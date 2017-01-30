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
    let function = llvm::core::LLVMAddFunction(module, b"cool_module\0".as_ptr() as *const _, function_type);

    let bb = llvm::core::LLVMAppendBasicBlockInContext(context, function, b"entry\0".as_ptr() as *const _);
    llvm::core::LLVMPositionBuilderAtEnd(builder, bb);

    let env = &mut HashMap::new();
    let zero = llvm::core::LLVMConstInt(int_type, 0, 0);
    let mut ret = zero;

    for n in insts {
        ret = codegen_node(context, builder, function, env, n);
    }

    // Emit a `ret void` into the function
    llvm::core::LLVMBuildRet(builder, ret);

    // Dump the module as IR to stdout.
    llvm::core::LLVMDumpModule(module);

    // Clean up. Values created in the context mostly get cleaned up there.
    llvm::core::LLVMDisposeBuilder(builder);
    llvm::core::LLVMDisposeModule(module);

    llvm::core::LLVMContextDispose(context);
}

unsafe fn codegen_node(ctx: LLVMContextRef, builder: LLVMBuilderRef, func: LLVMValueRef, env: &mut HashMap<String, LLVMValueRef>, n: Node) -> LLVMValueRef {
    match n {
        Node::Aref(ref n) => {
            *env.get(n).unwrap()
        },
        Node::Assgn(name, value) => {
            let nv = codegen_node(ctx, builder, func, env, *value);
            env.insert(name, nv);
            nv
        },
        Node::Int(n) => {
            let v = llvm::core::LLVMInt64TypeInContext(ctx);
            llvm::core::LLVMConstInt(v, n, 0)
        },
        Node::Add(l, r) => {
            let ll = codegen_node(ctx, builder, func, env, *l);
            let rr = codegen_node(ctx, builder, func, env, *r);
            let name = CString::new("add_value").unwrap();
            llvm::core::LLVMBuildAdd(builder, ll, rr, name.as_ptr())
        }
        Node::If(cond, then_body, else_body) => {
            let evaled_cond = codegen_node(ctx, builder, func, env, *cond);

            let int_type = llvm::core::LLVMInt64TypeInContext(ctx);
            let zero = llvm::core::LLVMConstInt(int_type, 0, 0);
            // `is_nonzero` is a 1-bit integer
            let name = CString::new("is_nonzero").unwrap();
            let is_nonzero = llvm::core::LLVMBuildICmp(builder,
                                                       llvm::LLVMIntPredicate::LLVMIntNE,
                                                       evaled_cond,
                                                       zero,
                                                       name.as_ptr());

            let then_name = CString::new("ifcond.then").unwrap();
            let else_name = CString::new("ifcond.else").unwrap();
            let end_name = CString::new("ifcond.end").unwrap();
            let then_block = llvm::core::LLVMAppendBasicBlockInContext(ctx, func, then_name.as_ptr());
            let else_block = llvm::core::LLVMAppendBasicBlockInContext(ctx, func, else_name.as_ptr());
            let end_block = llvm::core::LLVMAppendBasicBlockInContext(ctx, func, end_name.as_ptr());

            llvm::core::LLVMBuildCondBr(builder, is_nonzero, then_block, else_block);

            // then
            llvm::core::LLVMPositionBuilderAtEnd(builder, then_block);
            codegen_node(ctx, builder, func, env, *then_body);

            llvm::core::LLVMBuildBr(builder, end_block);

            // else
            llvm::core::LLVMPositionBuilderAtEnd(builder, else_block);
            codegen_node(ctx, builder, func, env, *else_body);

            // end
            llvm::core::LLVMPositionBuilderAtEnd(builder, end_block);
            zero
        },
    }
}
