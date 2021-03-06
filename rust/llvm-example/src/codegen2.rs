extern crate llvm_sys as llvm;
use std::ffi::CString;
use std::ptr;
use std::collections::HashMap;
use std::collections::hash_map::Entry;
use self::llvm::prelude::*;
use node::*;

// a = 10

// if (a) {
//   a = a + 1
// } else {
//   a = a + 2
// }
// a

pub fn run() {
    // a = 10
    let inst1 = assign("a", inum(10));

    // if (a) { a = a + 1 } else { a = a + 2 }
    let inst2 = ifexpr(refe("a"),
                       assign("a", add(refe("a"), inum(1))),
                       assign("a", add(refe("a"), inum(2))));
    // a
    let inst3 = refe("a");
    unsafe { codegen(vec![inst1, inst2, inst3]) }
}

unsafe fn codegen(insts: Vec<Node>) {
    let module_name = CString::new("cool_module").unwrap();
    let fn_name = CString::new("main").unwrap();
    let bb_name = CString::new("entry").unwrap();

    let context = llvm::core::LLVMContextCreate();
    let module = llvm::core::LLVMModuleCreateWithName(module_name.as_ptr());
    let builder = llvm::core::LLVMCreateBuilderInContext(context);

    let int_type = llvm::core::LLVMInt64TypeInContext(context);
    let function_type = llvm::core::LLVMFunctionType(int_type, ptr::null_mut(), 0, 0);
    let function = llvm::core::LLVMAddFunction(module, fn_name.as_ptr(), function_type);
    let bb = llvm::core::LLVMAppendBasicBlockInContext(context, function, bb_name.as_ptr());
    llvm::core::LLVMPositionBuilderAtEnd(builder, bb);

    gen_body(context, builder, function, insts);

    llvm::core::LLVMDumpModule(module);
    let out_file = CString::new("out.ll").unwrap();
    llvm::core::LLVMPrintModuleToFile(module, out_file.as_ptr(), ptr::null_mut());

    // Clean up
    llvm::core::LLVMDisposeBuilder(builder);
    llvm::core::LLVMDisposeModule(module);
    llvm::core::LLVMContextDispose(context);
}

unsafe fn gen_body(ctx: LLVMContextRef, builder: LLVMBuilderRef, fun: LLVMValueRef, v: Vec<Node>) {
    let env = &mut HashMap::new();
    let int_type = llvm::core::LLVMInt64TypeInContext(ctx);
    let zero = llvm::core::LLVMConstInt(int_type, 0, 0);
    let mut ret = zero;

    for n in v {
        ret = gen_node(ctx, builder, fun, env, n);
    }

    llvm::core::LLVMBuildRet(builder, ret);
}

unsafe fn gen_node(ctx: LLVMContextRef,
                   builder: LLVMBuilderRef,
                   fun: LLVMValueRef,
                   env: &mut HashMap<String, LLVMValueRef>,
                   n: Node)
                   -> LLVMValueRef {
    let v = match n {
        Node::Int(val) => {
            let typ = llvm::core::LLVMInt64TypeInContext(ctx);
            llvm::core::LLVMConstInt(typ, val, 0)
        }
        Node::Ref(var) => {
            let ptr = env.get(&var).unwrap();
            let name = CString::new(var.as_bytes()).unwrap();
            llvm::core::LLVMBuildLoad(builder, *ptr, name.as_ptr())
        }
        Node::Assign(name, val) => {
            let nval = gen_node(ctx, builder, fun, env, *val);
            let ptr = match env.entry(name.to_owned()) {
                Entry::Occupied(occu) => *occu.get(),
                Entry::Vacant(en) => {
                    let int_type = llvm::core::LLVMInt64TypeInContext(ctx);
                    let cname = CString::new(name).unwrap();
                    let ptr = llvm::core::LLVMBuildAlloca(builder, int_type, cname.as_ptr());
                    en.insert(ptr);
                    ptr
                }
            };
            llvm::core::LLVMBuildStore(builder, nval, ptr);
            nval
        }
        Node::Add(lh, rh) => {
            let lh = gen_node(ctx, builder, fun, env, *lh);
            let rh = gen_node(ctx, builder, fun, env, *rh);
            let name = CString::new("add_value").unwrap();
            let tv = llvm::core::LLVMBuildAdd(builder, lh, rh, name.as_ptr());
            tv
        }
        Node::Sub(lh, rh) => {
            let lh = gen_node(ctx, builder, fun, env, *lh);
            let rh = gen_node(ctx, builder, fun, env, *rh);
            let name = CString::new("sub_value").unwrap();
            let tv = llvm::core::LLVMBuildSub(builder, lh, rh, name.as_ptr());
            tv
        }
        Node::If(cond, then_body, else_body) => {
            let cond = gen_node(ctx, builder, fun, env, *cond);

            let int_type = llvm::core::LLVMInt64TypeInContext(ctx);
            let zero = llvm::core::LLVMConstInt(int_type, 0, 0);

            let name = CString::new("is_nonzero").unwrap();
            let is_nonzero = llvm::core::LLVMBuildICmp(builder,
                                                       llvm::LLVMIntPredicate::LLVMIntNE,
                                                       cond,
                                                       zero,
                                                       name.as_ptr());

            let entry_lable = CString::new("entry").unwrap();

            let then_block =
                llvm::core::LLVMAppendBasicBlockInContext(ctx, fun, entry_lable.as_ptr());
            let else_block =
                llvm::core::LLVMAppendBasicBlockInContext(ctx, fun, entry_lable.as_ptr());
            let merge_block =
                llvm::core::LLVMAppendBasicBlockInContext(ctx, fun, entry_lable.as_ptr());

            llvm::core::LLVMBuildCondBr(builder, is_nonzero, then_block, else_block);

            // then
            llvm::core::LLVMPositionBuilderAtEnd(builder, then_block);
            let then_return = gen_node(ctx, builder, fun, env, *then_body);
            llvm::core::LLVMBuildBr(builder, merge_block);
            let then_block = llvm::core::LLVMGetInsertBlock(builder);

            // else
            llvm::core::LLVMPositionBuilderAtEnd(builder, else_block);
            let else_return = gen_node(ctx, builder, fun, env, *else_body);
            llvm::core::LLVMBuildBr(builder, merge_block);
            let else_block = llvm::core::LLVMGetInsertBlock(builder);

            // merge
            llvm::core::LLVMPositionBuilderAtEnd(builder, merge_block);
            // phi
            let phi_name = CString::new("iftmp").unwrap();
            let phi = llvm::core::LLVMBuildPhi(builder, int_type, phi_name.as_ptr());

            let mut values = vec![then_return, else_return];
            let mut blocks = vec![then_block, else_block];

            llvm::core::LLVMAddIncoming(phi, values.as_mut_ptr(), blocks.as_mut_ptr(), 2);

            phi
        }
        _ => panic!("not support"),
    };
    v
}
