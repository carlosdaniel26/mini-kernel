/*
 *
 * kernel.c - version 0.0.1 fork
 * 
 */

#include "screen.c"

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);

void k_main() 
{
	k_clear_screen();
	int line = 0;
	k_printf(" +--^----------,--------,-----,--------^-,         POW POW\n", line++);
	k_printf(" | |||||||||   `--------'     |          O\n", line++);
	k_printf(" `+---------------------------^----------|\n", line++);
	k_printf("   `\\_,---------,---------,--------------'\n", line++);
	k_printf("     / XXXXXX /'|       /'\n", line++);
	k_printf("    / XXXXXX /  `\\    /'\n", line++);
	k_printf("   / XXXXXX /`-------'\n", line++);
	k_printf("  / XXXXXX /\n", line++);
	k_printf(" / XXXXXX /\n", line++);
	k_printf("(________(\n", line++);
	k_printf(" `------'\n", line++);
};