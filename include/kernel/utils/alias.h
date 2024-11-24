#define get_bit(A, B)    (((*(A)) >> (B & 7)) & 1)

#define set_bit(value, bit)   (*(value) |= (1UL << (bit)))
#define unset_bit(value, bit) (*(value) &= ~(1UL << (bit)))

void start_interrupts();
void stop_interrupts();