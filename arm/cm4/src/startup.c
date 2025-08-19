#if 0
// #include <stdint.h>
#include <stdint.h>

/* リンカスクリプトで定義するシンボル */
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);

/* デフォルトハンドラ */
__attribute__((weak)) void Default_Handler(void) { while (1); }
__attribute__((weak)) void NMI_Handler(void)     { while (1); }
__attribute__((weak)) void HardFault_Handler(void) { while (1); }

/* Reset_Handler */
void Reset_Handler(void) {
    uint32_t *dst;

    /* .bss をゼロクリア */
    for (dst = &_sbss; dst < &_ebss; )
        *(dst++) = 0;

    /* main() を呼び出す */
    main();

    /* 戻った場合は停止 */
    while (1);
}

/* ベクタテーブル */
__attribute__((section(".isr_vector")))
const void *vector_table[] = {
    (void *)(0x20000000 + 64*1024), /* スタック初期値 (RAM末尾) */
    Reset_Handler,                  /* Reset */
    NMI_Handler,                    /* NMI */
    HardFault_Handler,               /* HardFault */
    Default_Handler,                 /* MemManage (オプション) */
    Default_Handler,                 /* BusFault (オプション) */
    Default_Handler,                 /* UsageFault (オプション) */
    /* ... 必要に応じて追加 ... */
};
#endif

#include <stdint.h>

/* 外部参照：main関数 */
extern int main(void);

/* リンカスクリプトで定義されるセクション */
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _ldata;  // データ初期値が格納されている場所
extern uint32_t _estack; // RAM末尾に設定

/* デフォルトハンドラ */
__attribute__((weak)) void Default_Handler(void) { while (1); }
__attribute__((weak)) void NMI_Handler(void)     { while (1); }
__attribute__((weak)) void HardFault_Handler(void) { while (1); }

/* Reset Handler */
__attribute__((noreturn))
void Reset_Handler(void)
{
    uint32_t *dst;

    /* SP 初期化 */
    __asm volatile("msr msp, %0" : : "r"(&_estack) : );

    /* .data をゼロクリア */
    for (dst = &_sdata; dst < &_edata; dst++) {
        *dst = 0;
    }

    /* .bss をゼロクリア */
    for (dst = &_sbss; dst < &_ebss; dst++)
    {
        *dst = 0;
    }

    /* main関数コール */
    main();

    /* mainから戻った場合は無限ループ */
    while (1);
}

/* 割り込みベクターテーブル */
__attribute__((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void(*)(void))&_estack, /* 初期SP */
    Reset_Handler,
    Default_Handler, /* NMI_Handler */
    Default_Handler, /* HardFault_Handler */
    Default_Handler, /* 他の例外は必要に応じて追加 */
};

