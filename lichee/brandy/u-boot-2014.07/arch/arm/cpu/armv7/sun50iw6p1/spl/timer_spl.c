/* 
 * Copyright (c) 2016 Allwinnertech Co., Ltd.
 * Author: zhouhuacai <zhouhuacai@allwinnertech.com>
 *
 *  This file define the timer function interface for spl
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <common.h>
#include <asm/io.h>
#include <asm/arch/ccmu.h>
#include <asm/arch/timer.h>

int timer_init(void)
{
	struct sunxi_timer_reg *timer_reg = (struct sunxi_timer_reg *)SUNXI_TIMER_BASE;

	writel(readl(CCMU_AVS_CLK_REG) | (1U << 31), CCMU_AVS_CLK_REG);

	timer_reg->tirqen  = 0;
	timer_reg->tirqsta |= 0x03f;
	/* start avs as counter */
	//ccm_reg->avs_clk_cfg |= (1 << 31);
	timer_reg->avs.ctl  = 3; //enable avs cnt0 and cnt1,source is 24M
	/* div cnt0 12000 to 2000hz, high 32 bit means 1000hz.*/
	/* div cnt 1 12 to 2000000hz ,high 32 bit means 1000000hz */
	timer_reg->avs.div   = 0xc2ee0;
	timer_reg->avs.cnt0  = 0;
	timer_reg->avs.cnt1  = 0;

	return 0;
}

/*
************************************************************************************************************
*
*                                             function
*
*    函数名称：
*
*    参数列表：
*
*    返回值  ：
*
*    说明    ：
*
*
************************************************************************************************************
*/
void __msdelay(unsigned long ms)
{
	u32 t1, t2;
	struct sunxi_timer_reg *timer_reg = (struct sunxi_timer_reg *)SUNXI_TIMER_BASE;

	t1 = timer_reg->avs.cnt0;
	t2 = t1 + ms;
	do
	{
		t1 = timer_reg->avs.cnt0;
	}
	while(t2 >= t1);

	return ;
}
/*
************************************************************************************************************
*
*                                             function
*
*    函数名称：
*
*    参数列表：
*
*    返回值  ：
*
*    说明    ：
*
*
************************************************************************************************************
*/
void __usdelay(unsigned long us)
{
	u32 t1, t2;
	struct sunxi_timer_reg *timer_reg = (struct sunxi_timer_reg *)SUNXI_TIMER_BASE;

	t1 = timer_reg->avs.cnt1;
	t2 = t1 + us;
	do
	{
		t1 = timer_reg->avs.cnt1;
	}
	while(t2 >= t1);

	return ;
}
/*
************************************************************************************************************
*
*                                             function
*
*    函数名称：
*
*    参数列表：
*
*    返回值  ：
*
*    说明    ：
*
*
************************************************************************************************************
*/
void timer_exit(void)
{
	;
}

void reboot(void)
{
	struct sunxi_timer_reg *timer_reg;
	struct sunxi_wdog *wdog;

	timer_reg = (struct sunxi_timer_reg *)SUNXI_TIMER_BASE;

	 /* enable watchdog */
	wdog = &timer_reg->wdog[0];
	printf("system will reboot\n");
	wdog->cfg = 1;
	wdog->mode = 1;
	while(1);

	return;
}
