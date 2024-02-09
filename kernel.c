/*
 *
 * kernel.c - version 0.0.1 fork
 * 
 */


#define WHITE_TXT 0x07 /* light gray on black text */

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);

/* simple kernel written in C */
void k_main() 
{
	k_clear_screen();
	for (int i=0; i<=100; i++)
	{
		k_printf("Hello, world! Welcomedsadads to my kernel.", 0);
	}
};