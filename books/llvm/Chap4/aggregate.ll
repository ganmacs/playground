; ModuleID = 'aggregate.c'
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.11.0"

%struct.hoge2 = type { i8, double, %struct.hoge1 }
%struct.hoge1 = type { float, [10 x [20 x i32]] }

; Function Attrs: nounwind ssp uwtable
define i32* @getelem(%struct.hoge2* %hoge) #0 {
  %1 = alloca %struct.hoge2*, align 8
  store %struct.hoge2* %hoge, %struct.hoge2** %1, align 8
  %2 = load %struct.hoge2*, %struct.hoge2** %1, align 8
  %3 = getelementptr inbounds %struct.hoge2, %struct.hoge2* %2, i64 1
  %4 = getelementptr inbounds %struct.hoge2, %struct.hoge2* %3, i32 0, i32 2
  %5 = getelementptr inbounds %struct.hoge1, %struct.hoge1* %4, i32 0, i32 1
  %6 = getelementptr inbounds [10 x [20 x i32]], [10 x [20 x i32]]* %5, i64 0, i64 5
  %7 = getelementptr inbounds [20 x i32], [20 x i32]* %6, i64 0, i64 13
  ret i32* %7
}

attributes #0 = { nounwind ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"Apple LLVM version 7.3.0 (clang-703.0.29)"}
