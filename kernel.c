/*
 *
 * kernel.c - version 0.0.1 fork
 * 
 */

#include "screen.c"

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);

/* simple kernel written in C */
void k_main() 
{
	k_clear_screen();
	k_printf("Eae linha 1", 0);
	k_printf("Eae linha 2", 1);
};