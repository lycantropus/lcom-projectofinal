[CPU 686]
[BITS 32]

%define EOI 20h
%define PIC1_CMD 20h

[GLOBAL _contador_mili]
[GLOBAL _contador_secs]

[GLOBAL _t0_isr]

[SECTION .data]
_contador_mili: dd 0
_contador_secs: dd 0
_tmp_mili_aux:  dd 1000

[SECTION .text]

_t0_isr:
	; push dos registos usados
	push eax
	
	; instrucoes;

	; Como o timer0 esta a uma frequencia de 1000Hz,
	; cada chamada corresponde a um milisegundo
	inc dword [_contador_mili]
	inc dword [_tmp_mili_aux]
	cmp dword [_tmp_mili_aux], 0
	jz cont_t0_isr
	
	dec dword [_contador_secs]
	mov dword [_tmp_mili_aux], 1000
	
cont_t0_isr:
	; indicar a pic que terminou o processamento da interrupcao
	mov al, EOI
	out PIC1_CMD, al
	
	; pop dos registos usados
	pop eax
	
	iretd
