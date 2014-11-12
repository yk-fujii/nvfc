#ifndef __FUC_REG_H__
#define __FUC_REG_H__

#define FUC_INTR_TRIGGER 0x000
#define FUC_INTR_ACK 0x004
#define FUC_INTR 0x008
#define FUC_INTR_EN_SET 0x010
#define FUC_INTR_EN_CLR 0x014
#define FUC_INTR_EN_ 0x018
#define FUC_INTR_DISPATCH 0x01c

#define FUC_SCRATCH0 0x040
#define FUC_SCRATCH1 0x044

#define FUC_ACCESS_EN 0x048
#define FUC_AE_BIT_CHANNEL_SWITCH 0x1
#define FUC_AE_BIT_FIFO 0x2

#define FUC_DONE 0x400
#define FUC_MMCTX_INTR_ROUTE 0x404
#define FUC_BAR_REQMASK 0x40c
#define FUC_BAR 0x414
#define FUC_BAR_SET 0x418
#define FUC_CC_WATCHDOG 0x430
#define FUC_MMCTX_SAVE_SWBASE 0x700
#define FUC_MMCTX_LOAD_SWBASE 0x704
#define FUC_MMCTX_BASE 0x710
#define FUC_MMCTX_CTRL 0x714
#define FUC_MMCTX_MULTI_STRIDE 0x718
#define FUC_MMCTX_MULTI_MASK 0x71c
#define FUC_MMCTX_QUEUE 0x720
#define FUC_MMIO_CTRL 0x728
#define FUC_MMIO_RDVAL 0x72c
#define FUC_MMIO_WRVAL 0x730

#define FUC_NEWSCRATCH_BASE 0x800
#define FUC_NEWSCRATCH0 0x800
#define FUC_NEWSCRATCH1 0x804
#define FUC_NEWSCRATCH2 0x808
#define FUC_NEWSCRATCH3 0x80c
#define FUC_NEWSCRATCH4 0x810
#define FUC_NEWSCRATCH5 0x814
#define FUC_NEWSCRATCH6 0x818
#define FUC_NEWSCRATCH7 0x81c

#define FUC_NEWSCRATCH_SET_BASE 0x820
#define FUC_NEWSCRATCH_SET0 0x820
#define FUC_NEWSCRATCH_SET1 0x824
#define FUC_NEWSCRATCH_SET2 0x828
#define FUC_NEWSCRATCH_SET3 0x82c
#define FUC_NEWSCRATCH_SET4 0x830
#define FUC_NEWSCRATCH_SET5 0x834
#define FUC_NEWSCRATCH_SET6 0x838
#define FUC_NEWSCRATCH_SET7 0x83c

#define FUC_NEWSCRATCH_CLEAR_BASE 0x840
#define FUC_NEWSCRATCH_CLEAR0 0x840
#define FUC_NEWSCRATCH_CLEAR1 0x844
#define FUC_NEWSCRATCH_CLEAR2 0x848
#define FUC_NEWSCRATCH_CLEAR3 0x84c
#define FUC_NEWSCRATCH_CLEAR4 0x850
#define FUC_NEWSCRATCH_CLEAR5 0x854
#define FUC_NEWSCRATCH_CLEAR6 0x858
#define FUC_NEWSCRATCH_CLEAR7 0x85c

#define FUC_STRANDS 0x880

#define FUC_STRAND_SAVE_SWBASE 0x908
#define FUC_STRAND_LOAD_SWBASE 0x90c
#define FUC_STRAND_SIZE 0x910

#define FUC_MEM_BASE 0xa04
#define FUC_MEM_CHAN 0xa0c
#define FUC_MEM_TARGET 0xa20

#endif