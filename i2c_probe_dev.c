#include	<linux/err.h>
#include	<linux/errno.h>
#include	<linux/delay.h>
#include	<linux/fs.h>
#include	<linux/input.h>
#include	<linux/uaccess.h>
#include	<linux/workqueue.h>
#include	<linux/irq.h>
#include	<linux/gpio.h>
#include	<linux/interrupt.h>
#include    <mach/irqs.h>
#include    <linux/slab.h>
#include	<linux/earlysuspend.h>
#include	<linux/gpio.h>
#include	<plat/gpio-cfg.h>
#include	<linux/i2c.h>

#define I2C_PROBE_DEV_NAME "i2c_dummy"

static void i2c_probe_test_func(struct i2c_adapter *adapter)
{
	int err;
	int i;
	char buf[4];
//	struct i2c_adapter *adapter = i2c_get_adapter(bus);

	struct i2c_msg msgs[] = {
		{
			.addr = 0x00,
			.flags = 0,
			.len = 0,
			.buf = buf,
		},
	};
	
	for (i = 0;i < 0x7f; i++) {
		msgs[0].addr = i;
		err = i2c_transfer(adapter, msgs, 1);
		if (err != 1) {
			printk("error 0x%02x\n", i);
		} else {
			printk("ok -----> 0x%02x\n", i);
		}
		msleep_interruptible(10);
	}

	return;
}

static int __init i2c_probe_dev_init(void)
{
	struct i2c_adapter *adapter = i2c_get_adapter(10);
	printk("i2c probe dev init driver \n");
	i2c_probe_test_func(adapter);
	return 0;
}

static void __exit i2c_probe_dev_exit(void)
{
	printk("i2c probe dev exit driver\n");
	return;
}

module_init(i2c_probe_dev_init);
module_exit(i2c_probe_dev_exit);
MODULE_DESCRIPTION("i2c probe device address driver");
MODULE_AUTHOR("gechunming@evisioncom.com");
MODULE_LICENSE("GPL");
