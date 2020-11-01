.code

MyProc1 proc 

mov rax, 0
mov rax, [rcx+16]

ret
MyProc1 endp


Jednorodny proc 

mov r8, 0 ;licznik
mov r9, 0 ;waga
mov rax, 0 ;wartosc
petla: mov r11, [rcx+r8]
cmp r11d, -1
je nastepny
add eax, r11d
add r9, 1
nastepny: add r8, 4
cmp r8, 32
jle petla
mov rdx, 0
div r9w

ret
Jednorodny endp

Wagowy proc 

mov r12, rdx ;waga jednostkowa (wskaznik)
mov r8d, 0 ;licznik
mov r9d, 0 ;waga
mov r10d, 0 ;wartosc
petla: mov r11, [rcx+r8]
cmp r11d, -1
je nastepny ;w wypadku gdy krawedzie bierzemy pod uwage
;je pomin ;w przypadku gdy krawedzie pozostawiamy bez zmian
mov eax, r11d
mov r11d, [r12+r8]
imul r11d
add r10d, eax
add r9d, [r12+r8]
nastepny: add r8, 4
cmp r8, 32
jle petla
mov rdx, 0
mov eax, r10d
cmp eax, 0
jl zerowanie


cmp r9w,0
je koniec


cmp r9w,0
jle niedziel
div r9w

niedziel: cmp eax, 256
jnl maksowanie 

jmp koniec

zerowanie: mov eax, 0
jmp koniec

;pomin: mov eax, [rcx+16]
;jmp koniec

maksowanie: mov eax, 255

koniec: ret
Wagowy endp


WagowyBezBrzegow proc 

;VMOVDQU ymm0, YMMWORD PTR [rcx]
MOVDQU xmm0, XMMWORD PTR [rcx]
MOVDQU xmm1, XMMWORD PTR [rcx+20]
VPCMPGTD xmm0, xmm2, xmm0 ;sprawdzanie czy ktorakolwiek z wartosci 0-3 jest ujemna
						  ;wartosc 4 z zalozenia nie moze byc ujemna
VPCMPGTD xmm1, xmm2, xmm1 ;sprawdzanie czy ktorakolwiek z wartosci 5-8 jest ujemna


PEXTRQ rax, xmm0, 3
cmp rax, 0
jne pomijane
PEXTRQ rax, xmm1, 3
cmp rax, 0
jne pomijane

;vpcmpgtd ymm0, ymm1, ymm0 ;sprawdzanie czy ktorakolwiek z wartosci 0-7 jest ujemna
;VMOVMSKPD rax, ymm0
;VEXTRACTI128 xmm1, ymm0, 8
;cvtss2si eax, xmm0
;PEXTRD eax, xmm0, 1
;VPMOVDB xmm1, ymm1
;VCVTSD2USI rax, xmm0
;VPCMPEQW ymm0


mov r12, rdx ;waga jednostkowa (wskaznik)
mov r8d, 0 ;licznik
mov r9d, 0 ;waga
mov r10d, 0 ;wartosc
petla: mov r11, [rcx+r8]
cmp r11d, -1
je nastepny
mov eax, r11d
mov r11d, [r12+r8]
imul r11d
add r10d, eax
add r9d, [r12+r8]
nastepny: add r8, 4
cmp r8, 32
jle petla
mov rdx, 0
mov eax, r10d
cmp eax, 0
jl zerowanie

cmp r9w,0
jle niedziel
div r9w
niedziel: cmp eax, 256
jnl maksowanie 

jmp koniec

zerowanie: mov eax, 0
jmp koniec
maksowanie: mov eax, 255
jmp koniec

pomijane:
mov rax, [rcx+16]
koniec: ret
WagowyBezBrzegow endp

end