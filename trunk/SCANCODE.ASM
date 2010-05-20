CPU 686
BITS 32

%define EOI 20h 			; define EOI como valendo 0x20
%define PIC1_CMD  0x20 
%define DATA_REG  0x60
extern _scanCodeQueue 		; declara nome_var como acessível a módulos escritos em C
extern _queuePut
extern _beep
extern _scan
extern _makeEmpty

global _scancode_isr 		; o handler também deve ser global, para ser instalado


section .data 				; .data é a zona de dados inicializados

section .text 				; .text é a zona de código
_scancode_isr: 				; deve ser global para ser acedida em módulos escritos em C
	push eax
	STI 					;para habilitar as interrupçoes
	in al, DATA_REG			; lê a tecla
	push eax
	push _scanCodeQueue
	call _queuePut
	add esp, 8				; "pop" dos dois ultimos argumentos
	cmp eax, 1				;  queueput devolveu true (adicionou o scancode)
	je fim
	push _scanCodeQueue			;voltar a por a queue na stack
	;call _makeEmpty
	add esp, 4	;voltar para a posicao anterior ao esvaziamento stack
	;call _beep
fim:	
	mov byte [_scan], 1
	mov al, EOI 			; sinaliza EOI para o PIC-1
	out PIC1_CMD, al
	pop eax 				; todos os registos guardados
	CLI
	iretd
END ; fim de código fonte assembly