#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/wait.h>
#include <linux/completion.h>
#include <linux/interrupt.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <linux/proc_fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <asm/io.h>
#include "han.h"
#include "cpu.h"
#include <plat/mcbsp.h>
#include <linux/time.h>
//#include "mcbsp.h"
#include <plat/dma.h>

#define MI_MAJOR_NUM		500		
#define MI_DEV_NAME			"McBSP1"
#define MI_MCBSP_NO			1						/* the mcbsp module no. for connect fpga */

/* offset of register address */
#define OMAP_MCBSP_REG_DRR1			0x04
#define OMAP_MCBSP_REG_DXR			0x08
#define OMAP_MCBSP_REG_SPCR1		0x14
#define OMAP_MCBSP_REG_SPCR2		0x10
#define OMAP_MCBSP_REG_DXR1			0x0C
#define OMAP_MCBSP_REG_DRR			0x00
#define OMAP_MCBSP_REG_DRR2			0x00
#define OMAP_MCBSP_REG_XBUFF   		0xB4
#define OMAP_MCBSP_REG_IRQEN		0xA4
#define MCBSP_DXR *(volatile unsigned int *)(0xfa074008)
#define MCBSP_DRR *(volatile unsigned int *)(0xfa074000)

/* global variables */
void __iomem *base ;
int fpga_id = MI_MCBSP_NO - 1;

extern struct hard_cache *rcv_cache;


static int fpga_open(struct inode* inode, struct file* file);
static int fpga_release(struct inode* inode, struct file* file);
static ssize_t fpga_read(struct file* file, char __user *buf, size_t len, loff_t* off);
static ssize_t fpga_write(struct file* file, const char __user *buf, size_t len, loff_t* off);
static long fpga_ioctl(struct file*, unsigned int, unsigned long);


struct file_operations fpga_fops = {
	.owner = THIS_MODULE,
	.open = fpga_open,
	.release = fpga_release,
	.read = fpga_read,
	.write = fpga_write,
	.unlocked_ioctl = fpga_ioctl,
};

static int __init fpga_init(void)
{
	int ret;

	/* register device */
    ret = register_chrdev(MI_MAJOR_NUM, MI_DEV_NAME, &fpga_fops);
	if(ret < 0)
	{
		printk("Ant_IF register failure\n");
		return ret;
	}
	else
		return 0;
}

static void __exit fpga_exit(void)
{
	unregister_chrdev(MI_MAJOR_NUM, MI_DEV_NAME);
	printk("Ant_IF unregister success\n");
}

extern u32 dst_phys ;
extern char *p;
static int fpga_open(struct inode* inode, struct file* file)
{
	/*struct omap_mcbsp *mcbsp;
	int dma_rx_ch;
	mcbsp = id_to_mcbsp_ptr(0);*/
	request_mem_region(0x48074000, 4*1024, MI_DEV_NAME);
	base = ioremap(0x48074000, SZ_4K);
	omap_mcbsp_set_io_type(0, /*OMAP_MCBSP_POLL_IO*/ OMAP_MCBSP_IRQ_IO);
	
	if(omap_mcbsp_request(0)<0)
	{ 
		printk("omap_mcbsp_repuest failure\n");
	} 
	
	if(hard_cache_init()<0)
	{ 
		printk("hard_cache_init failure\n");
	} 
	
	if (reg_config() < 0)
	{
		printk("reg_config failure\n");
		return -1;
	}
	omap_mcbsp_start(0,1,1);
	
	//p = kmalloc(50000,GFP_KERNEL);
	//memset(p,0,50000);
	
	/*if (omap_request_dma(mcbsp->dma_rx_sync, "McBSP RX",
				omap_mcbsp_rx_dma_callback,
				mcbsp,
				&dma_rx_ch)) {
		dev_err(mcbsp->dev, "Unable to request DMA channel for "
				"McBSP%d RX. Trying IRQ based RX\n",
				mcbsp->id);
		return -EAGAIN;
	}*/
	/*if(omap_mcbsp_recv_buffer(0,dst_phys,128)<0)
		printk("recv_buffer error\n");
printk("open p is 0x%x\n",dst_phys);*/
	return 0;
}


static int fpga_release(struct inode* inode, struct file* file)
{    
	omap_mcbsp_stop(0,1,1);
	hard_cache_exit();
	omap_mcbsp_free(0);
	iounmap(base);
	release_mem_region(0x48074000,4*1024);
	return 0;
}

//extern char readbuf[512];
int j=0;
int count[10000];
extern int number[];

static ssize_t fpga_read(struct file* file, char __user *buf, size_t len, loff_t* off)
{
	/* waiting for the whole frame end interrupt */
	//int i;
	int temp = 0;
	int k=0;
	int w = 0;
	u32 aa;
	//int stop = 0;
	//struct timeval startTime;
	//temp = rcv_cache->tail;

	//for(temp=0;temp<10;temp++)
		//printk("...%x\n",*(p+temp));
	//while(readl(base+OMAP_MCBSP_REG_SPCR1) & 0x2)
	//{
	/*printk("SPCR %x\n",readl(base+OMAP_MCBSP_REG_SPCR1));
	dma_wait_for_rx();
	copy_to_user(buf, p, 512);
	omap_mcbsp_recv_buffer(0,dst_phys,128);*/
	//}
	//mcbsp_wait_for_rx(0);
	
	
#if 0
	do_gettimeofday(&startTime);
	count[j]=1000*startTime.tv_usec ;
	j++;	
	if(j==10000)
	{
		for(k=0;k<10000;k++)
		{
			w=count[k]-number[k];
			if(w>=100000)			
				printk("time == %d\n",w);
		}
	}

	//if(rcv_cache->head == rcv_cache->tail)
	//{
		mcbsp_wait_for_rx(0);
	//}
#endif
	mcbsp_wait_for_rx(0);
	copy_to_user(buf, &rcv_cache->buf[rcv_cache->head], 512);
	rcv_cache->head = (rcv_cache->head+1)%CACHE_SIZE;
	//printk("size = %d\n",rcv_cache->head);		

	return 0;
}


//extern int irq_send;
static ssize_t fpga_write(struct file* file, const char __user *buf, size_t len, loff_t* off)
{	
	// irq_send = 1;
	int i;
	u32 ievents;
	u32 wdata, *pword = (u32 *)buf;
	u32 aa;
	struct timeval startTime ,endTime;
	int Timeuse;

	/* waiting for the end of last frame transmission */
	mcbsp_wait_for_tx(0);

	/* read enable events */
	ievents = omap_mcbsp_read(base, OMAP_MCBSP_REG_IRQEN);
	/* disable all interrupt events on mcbsp1 */
	//=====omap_mcbsp_write(base, OMAP_MCBSP_REG_IRQEN, 0);

	// w= readl( base + OMAP_MCBSP_REG_IRQEN);
	//printk("......2......[%x]\n",w);	
	//do_gettimeofday(&startTime);
	/*for(i = 0; i<128; i++)
	{
#if 1	
		wdata = pword[i];
		MCBSP_DXR = wdata;
#else
		MCBSP_DXR = pword[i];
#endif 
		
	}*/
	for(i = 0; i<128; i++)
	{
	aa = 0;
	aa = aa | buf[i*4 + 0];
	aa = aa<<8;
	aa = aa | buf[i*4 + 1];
	aa = aa<<8;
	aa = aa | buf[i*4 + 2];
	aa = aa<<8;
	aa = aa | buf[i*4 + 3];
	
	MCBSP_DXR = aa;
	}
	//do_gettimeofday(&endTime);
	//Timeuse=1000000*(endTime.tv_sec - startTime.tv_sec)+(endTime.tv_usec - startTime.tv_usec);
	//Timeuse /= 1000000;
	//printk("Timeuse = %d\n",Timeuse);
	//printk(".......irq_send1 = %d\n",irq_send);

	//=====omap_mcbsp_write(base, OMAP_MCBSP_REG_IRQEN, ievents);

	return len;
}


static long fpga_ioctl(struct file* fp, unsigned int cmd, unsigned long addr)
{
	return 0;
}


module_init(fpga_init);
module_exit(fpga_exit);
MODULE_LICENSE("GPL");







