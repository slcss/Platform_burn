#include "han.h"
#include <plat/dma.h>


#define OMAP_MCBSP_REG_RCR1		0x1C
#define OMAP_MCBSP_REG_RCR2		0x18	
#define OMAP_MCBSP_REG_XCR1		0x24
#define OMAP_MCBSP_REG_XCR2		0x20
#define OMAP_MCBSP_REG_SPCR1	0x14
#define OMAP_MCBSP_REG_SPCR2	0x10
#define OMAP_MCBSP_REG_MCR1		0x34
#define OMAP_MCBSP_REG_MCR2		0x30
#define OMAP_MCBSP_REG_SRGR1	0x2C
#define OMAP_MCBSP_REG_PCR0		0x48
#define OMAP_MCBSP_REG_SRGR2	0x28


   void omap_mcbsp_write(void __iomem *base, u16 reg, u32 val)
{
	
		__raw_writel(val, base + reg);
}

int omap_mcbsp_read(void __iomem *base, u16 reg)
{
	
		return __raw_readl(base + reg);
}





int reg_config(void)
{       
       	u32 w;
        w=/*RINTM(0)|*/DXENA;
	omap_mcbsp_write(base,OMAP_MCBSP_REG_SPCR1,w);
        /*w=XINTM(2);
        omap_mcbsp_write(base,OMAP_MCBSP_REG_SPCR2,w);*/
        
        w=FSXM | CLKXM ;
       omap_mcbsp_write(base,OMAP_MCBSP_REG_PCR0,w);
        
	 
        w=RWDLEN1(5)|RFRLEN1(0x7F);
        omap_mcbsp_write(base,OMAP_MCBSP_REG_RCR1,w);
	w=RDATDLY(1);
       omap_mcbsp_write(base,OMAP_MCBSP_REG_RCR2,w);
	
        w=XWDLEN1(5)|XFRLEN1(0x7F);
       omap_mcbsp_write(base,OMAP_MCBSP_REG_XCR1,w);
        w=XDATDLY(1) ;
        omap_mcbsp_write(base,OMAP_MCBSP_REG_XCR2,w);
         
	
	w = FWID(0) | CLKGDV(3);
	omap_mcbsp_write(base,OMAP_MCBSP_REG_SRGR1,w);
        w=CLKSM |FPER(4096-1);
        omap_mcbsp_write(base,OMAP_MCBSP_REG_SRGR2,w);
         
         
        w=XDISABLE;
       omap_mcbsp_write(base,OMAP_MCBSP_REG_XCCR,w);
        w=RFULL_CYCLE | RDISABLE ;
       omap_mcbsp_write(base,OMAP_MCBSP_REG_RCCR,w);

	/* ’‚æ‰ª∞ «∑Ò”–±ÿ“™Â**/
	w=RRDYEN;
	omap_mcbsp_write(base,OMAP_MCBSP_REG_IRQEN,w);
        
	w=0x7F;
        omap_mcbsp_write(base,OMAP_MCBSP_REG_THRSH1,w);
        w=0x0;
        omap_mcbsp_write(base,OMAP_MCBSP_REG_THRSH2,w);
	w= omap_mcbsp_read(base,OMAP_MCBSP_REG_THRSH1);
	
        
	w=REOFEN | XEOFEN;
	omap_mcbsp_write(base,OMAP_MCBSP_REG_IRQEN,w);
	
        w=REOFEN;
	omap_mcbsp_write(base,OMAP_MCBSP_REG_WAKEUPEN,w);
         return 0;
}
EXPORT_SYMBOL(reg_config);






	
