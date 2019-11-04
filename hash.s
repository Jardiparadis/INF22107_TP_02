	.file	"hash.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4,,15
	.globl	_Z4hashPKc
	.type	_Z4hashPKc, @function
_Z4hashPKc:
.LFB0:
	.cfi_startproc
	xor rax, rax #set result (h) to 0
	mov r9, 0 #r9 -> counter
	.loop:
	    xor r8, r8
	    mov r8b, BYTE PTR [rdi + r9]
	    cmp r8b, 0 #check if the current char is null
	    je .done #if current char is null, go to done
	    ror rax, 19 #rotate eax by 19 bits
	    not rax #negate rax
	    add rax, r8 #add current char to rax
	    inc r9 #increment counter
	    jmp .loop #loop over the next character
	.done:
	    ret #return rax
	.cfi_endproc
.LFE0:
	.size	_Z4hashPKc, .-_Z4hashPKc
	.ident	"GCC: (Ubuntu 8.3.0-6ubuntu1) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
