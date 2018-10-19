#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define STAT_REG        0x64
#define KBC_CMD_REG     0x64
#define OUT_BUF         0x60


#define OBF             BIT(0)
#define IBF             BIT(1)

#define PAR_ERR         BIT(7)
#define TO_ERR          BIT(6)

#define WAIT_KBC 		100

#endif /* _LCOM_I8042_H_ */
