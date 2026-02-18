#include "../tbforth.c"
#include "../tbforth.img.h"

#include "periph/gpio.h"
#include "periph/pm.h"
#include "ztimer.h"

uint8_t rxc(void) {
  return fgetc(stdin);
}

void txc(uint8_t c) {
  fputc(c,stdout);
  fflush(stdout);
}

void txs(char* s, int cnt) {
  fwrite(s,cnt,1,stdout);
  fflush(stdout);
}
#define txs0(s) txs(s,strlen(s))

tbforth_stat c_handle(void) {
  RAMC r2, r1 = dpop();
  switch(r1) {
  case MCU_GPIO_MODE :
    r2 = dpop();
    gpio_init(r2,dpop());
    break;
  case MCU_GPIO_READ :
    r2 = dpop();
    dpush(gpio_read(r2));
    break;
  case MCU_GPIO_WRITE :
    r2 = dpop();
    gpio_write(r2,dpop());
    break;
  case MCU_RESTART:
    pm_reboot();
    break;
  case OS_SECS:
    dpush(ztimer_now(ZTIMER_SEC));
    break;
  case OS_MS:
    dpush(ztimer_now(ZTIMER_MSEC));
    break;
  case OS_US:
    dpush(ztimer_now(ZTIMER_USEC));
    break;
  case MCU_DELAY:
    ztimer_sleep(ZTIMER_MSEC,dpop());
    break;
  case MCU_SLEEP:
    ztimer_sleep(ZTIMER_SEC,dpop());
    break;
  case OS_EMIT:			/* emit */
    txc(dpop()&0xff);
    break;
  case OS_KEY:			/* key */
    dpush((CELL)rxc());
    break;
  }
  return U_OK;
}


static char line_read[128];

char * rl_gets (void) {
  int i = 0;
  char c;
  while (i < 128) {
    c = rxc();
    txc(c);
    switch (c) {
    case 3:
      txs0(" ^C\n");
      line_read[0] = '\0';
      return line_read;
    case '\n':
    case '\r':
      line_read[i] = '\0';
      txc('\n');
      return line_read;
    case '\b':
      if (i > 0) i--;
      break;
    default:
      line_read[i++] = c;
      break;
    }
  }
  line_read[127] = '\0';
  return line_read;
}

void console(void) {
  char *line;
  int stat;
  while (1) {
    txs0(" ok\r\n");
    line=rl_gets();
    if (line[0] == '\r' || line[0] == '\0') continue;
    stat = tbforth_interpret(line);
    switch(stat) {
    case E_NOT_A_WORD:
      txs0("\r\nHuh? >>> ");
      txs(&tbforth_iram->tib[tbforth_iram->tibwordidx],tbforth_iram->tibwordlen);
      txs0(" <<< ");
      txs(&tbforth_iram->tib[tbforth_iram->tibwordidx + tbforth_iram->tibwordlen],
	  tbforth_iram->tibclen - 
	  (tbforth_iram->tibwordidx + tbforth_iram->tibwordlen));
      txs0("\r\n");
      break;
    case E_ABORT:
      txs0("Abort!:<"); txs0(line); txs0(">\n");
      break;
    case E_STACK_UNDERFLOW:
      txs0("Stack underflow!\n");
      break;
    case E_DSTACK_OVERFLOW:
      txs0("Stack overflow!\n");
      break;
    case E_RSTACK_OVERFLOW:
      txs0("Return Stack overflow!\n");
      break;
    case U_OK:
      break;
    default:
      txs0("Ugh\n");
      break;
    }
  }
}

struct dict  *dict = &flashdict;

int main(void) {
  tbforth_init();
  tbforth_interpret("init");
  tbforth_interpret("cr memory cr");
  console();
}
