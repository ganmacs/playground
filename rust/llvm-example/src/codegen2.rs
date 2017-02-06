extern crate llvm_sys as llvm;
use std::ffi::CString;
use std::ptr;

use self::llvm::prelude::*;
use node::*;
use std::collections::HashMap;

// a = 10
//
// if (a) {
//   a = a + 1
// } else {
//   a = a + 2
// }
// a

pub fn run() {
    // a = 10
    // let inst1 = assign("a", inum(10));

    // // if ( ~ ) { ~ }  else { ~ }
    // let inst2 = ifexpr(refe("a"),
    //                    assign("a", add(refe("a"), inum(1))),
    //                    assign("a", add(refe("a"), inum(2))));
    // // a
    // let inst3 = refe("a");
    // unsafe { codegen(vec![inst1, inst2, inst3]) }

    // let inst1 = assign("a", inum(10));
    // unsafe { codegen(vec![inst1, inst3]) }

    let inst1 = assign("a", inum(10));
    let inst2 = assign("a", add(refe("a"), inum(1)));
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

            let int_type = llvm::core::LLVMInt64TypeInContext(ctx);
            let cname = CString::new(name.as_bytes()).unwrap();
            let ptr = llvm::core::LLVMBuildAlloca(builder, int_type, cname.as_ptr());

            llvm::core::LLVMBuildStore(builder, nval, ptr);
            env.insert(name, ptr);
            nval
        }
        Node::Add(lh, rh) => {
            let lh = gen_node(ctx, builder, fun, env, *lh);
            let rh = gen_node(ctx, builder, fun, env, *rh);
            let name = CString::new("add_value").unwrap();
            let tv = llvm::core::LLVMBuildAdd(builder, lh, rh, name.as_ptr());
            tv
        }
        // Node::If(cond, then_body, else_body) => {}
        _ => panic!("tmp"),
        // Node::Sub(lh, rh) => {}
    };
    v
}
