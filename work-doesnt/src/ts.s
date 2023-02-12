        .global  running, scheduler, tswitch
tswitch:
SAVE:   pushq %rax
        pushq %rbx
        pushq %rcx
        pushq %rdx
        pushq %rbp
        pushq %rsi
        pushq %rdi
        pushfq
        movq running,%rbx 
        movq %rsp,8(%rbx)
FIND:   call  scheduler
RESUME: movq running,%rbx
        movq 8(%rbx),%rsp
        popfq
        popq  %rdi
        popq  %rsi
        popq  %rbp
        popq  %rdx
        popq  %rcx
        popq  %rbx
        popq  %rax
        retq
# stack contents = |retPC|rax|rbx|rcx|rdx|rbp|rsi|rdi|rflag|
#                    -1   -2  -3  -4  -5  -6  -7  -8   -9

        #.global  running, scheduler, tswitch
#tswitch:
#SAVE:   pushq %rax
        #pushq %rbx
        #pushq %rcx
        #pushq %rdx
        #pushq %rbp
        #pushq %rsi
        #pushq %rdi
        #pushfl
        #movl  running,%rbx 
        #movl  %rsp,4(%rbx)
#FIND:   call  scheduler
#RESUME: movl  running,%rbx
        #movl  4(%rbx),%rsp
        #popfl
        #popq  %rdi
        #popq  %rsi
        #popq  %rbp
        #popq  %rdx
        #popq  %rcx
        #popq  %rbx
        #popq  %rax
        #ret
