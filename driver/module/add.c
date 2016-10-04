#include <linux/init.h>
#include <linux/module.h>

int add(int a, int b)
{
	return a+b;
}

static int add_init(void)
{

	return 0;
}

static void add_exit(void)
{
	
}

EXPORT_SYMBOL(add);

module_init(add_init);
module_exit(add_exit);