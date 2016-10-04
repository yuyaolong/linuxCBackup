#include <stdio.h>
void blow_stack() {
	blow_stack();
}

void *orig_stack_pointer;
int main(int argc, char const *argv[])
{
	__asm__("movl %esp, orig_stack_pointer");
	blow_stack();
	return 0;
}
