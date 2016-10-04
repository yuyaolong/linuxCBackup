#include <linux/init.h>
#include <linux/module.h>


extern int add(int a, int b);
MODULE_LICENSE("GPL");


int a =3;
char *p;
module_param(a, int, S_IRUGO|S_IWUSR);
module_param(p, charp, S_IRUGO|S_IWUSR);


static int hello_init(void)
{
	printk("Hello,world\n");
	printk("a = %d\n", a);
	printk("p = %s\n", p);
	return 0;
}

static void hello_exit(void)
{
	add(1,4);
	printk("Goodbye, world\n");
}

module_init(hello_init);
module_exit(hello_exit);