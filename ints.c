#include "ints.h"

/** Installs the ASM written function 'irq_func' as the interrupt
 * handler associated with interrupt 'irq', updating the 'old_irq'
 * structure with the current interrupt handler.  Returns 0 on success
 * or -1 on error, in which case the original interrupt handler
 * remains installed.
 * 
 * See reinstall_asm_irq_handler() to reinstall the original handler.
 */
int install_asm_irq_handler(int irq, void (*irq_func)(void), _go32_dpmi_seginfo *old_irq)
{
	_go32_dpmi_seginfo new_irq;
		
	_go32_dpmi_get_protected_mode_interrupt_vector(IRQ_VECTOR(irq), old_irq);
	
	new_irq.pm_selector = _go32_my_cs();
	new_irq.pm_offset = (unsigned long) irq_func;
		
	if(_go32_dpmi_set_protected_mode_interrupt_vector(IRQ_VECTOR(irq), &new_irq))
	{
		_go32_dpmi_set_protected_mode_interrupt_vector(IRQ_VECTOR(irq), old_irq);
		return -1;
	}
	return 0;
}

/** Installs the C written 'irq_func' interrupt handler at the
 * interrupt handler associated with interrupt 'irq', updating the
 * old_irq structure with the current interrupt handler.  Returns 0 on
 * success or -1 on error, in which case the original interrupt
 * handler remains installed.
 * 
 * See reinstall_c_irq_handler() to reinstall the original handler.
 */
int install_c_irq_handler(int irq, void (*irq_func)(void),
			    _go32_dpmi_seginfo *old_irq, _go32_dpmi_seginfo *new_irq)
{	
	/* Guarda endereco da rotina correntemente instalada */
	_go32_dpmi_get_protected_mode_interrupt_vector(IRQ_VECTOR(irq), old_irq);
	
	/* Prepara descritor da nova rotina */
	new_irq->pm_selector = _go32_my_cs();
	new_irq->pm_offset = (unsigned long) irq_func;
	/* Prepara funcao em assembly que chama a funcao em C */
	_go32_dpmi_allocate_iret_wrapper( new_irq );
	/* instala nova rotina de interrupcao */
	_go32_dpmi_set_protected_mode_interrupt_vector(IRQ_VECTOR(irq), new_irq);

	return 0;
}

/** Reinstalls the interrupt handler specified in 'old_irq' for interrupt
 * 'irq'. See install_asm_irq_handler().
 */
void reinstall_asm_irq_handler(int irq, _go32_dpmi_seginfo *old_irq)
{
	_go32_dpmi_set_protected_mode_interrupt_vector(IRQ_VECTOR(irq), old_irq);
}

/** Reinstalls the interrupt handler specified in 'old_irq' for interrupt
 * 'irq'. See install_c_irq_handler().
 */
void reinstall_c_irq_handler(int irq, _go32_dpmi_seginfo *old_irq, _go32_dpmi_seginfo *new_irq)
{
	_go32_dpmi_set_protected_mode_interrupt_vector(IRQ_VECTOR(irq), old_irq);
	
	_go32_dpmi_free_iret_wrapper( new_irq );
}

/** Mask the bit corresponding to 'irq', disabling its interrupts.
 * The correct PIC is used.
 */
void mask_pic(int irq)
{
	unsigned short pic;
	
	if (irq <= 7) // seleccao da mascara a alterar
		pic = PIC1_MASK;
	else
		pic = PIC2_MASK;
	
	unsigned char car = inportb(pic); // le o valor da mascara
	car |= IRQ_MASK_BIT(irq);         // altera o bit para 1
	outportb(pic, car); 	          //envia-o de volta
}

/** Unmask the bit corresponding to 'irq', enabling its interrupts.
 * The correct PIC is used.
*/
void unmask_pic(int irq)
{
unsigned short pic;
	
	if (irq <= 7) 
		pic = PIC1_MASK;
	else
		pic = PIC2_MASK;
		
	unsigned char car = inportb(pic); // le o valor da mascara
	car &= (~IRQ_MASK_BIT(irq));      // altera o valor do bit
	outportb(pic, car);               // envia-o de volta	
}
