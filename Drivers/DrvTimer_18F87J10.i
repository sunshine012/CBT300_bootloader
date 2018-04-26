#line 1 "DrvTimer_18F87J10.c"
#line 1 "DrvTimer_18F87J10.c"

#line 34 "DrvTimer_18F87J10.c"
 







#line 1 "./DrvPic18f67J10.h"

#line 5 "./DrvPic18f67J10.h"
 


#line 9 "./DrvPic18f67J10.h"

extern volatile near unsigned char       SSP2CON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
} SSP2CON2bits;
extern volatile near unsigned char       SSP2CON1;
extern volatile near struct {
  unsigned SSPM0:1;
  unsigned SSPM1:1;
  unsigned SSPM2:1;
  unsigned SSPM3:1;
  unsigned CKP:1;
  unsigned SSPEN:1;
  unsigned SSPOV:1;
  unsigned WCOL:1;
} SSP2CON1bits;
extern volatile near unsigned char       SSP2STAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSP2STATbits;
extern volatile near unsigned char       SSP2ADD;
extern volatile near unsigned char       SSP2BUF;
extern volatile near unsigned char       ECCP2DEL;
extern volatile near union {
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
    unsigned PRSEN:1;
  };
  struct {
    unsigned P2DC0:1;
    unsigned P2DC1:1;
    unsigned P2DC2:1;
    unsigned P2DC3:1;
    unsigned P2DC4:1;
    unsigned P2DC5:1;
    unsigned P2DC6:1;
    unsigned P2RSEN:1;
  };
} ECCP2DELbits;
extern volatile near unsigned char       ECCP2AS;
extern volatile near union {
  struct {
    unsigned PSSBD0:1;
    unsigned PSSBD1:1;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned PSS2BD0:1;
    unsigned PSS2BD1:1;
    unsigned PSS2AC0:1;
    unsigned PSS2AC1:1;
    unsigned ECCP2AS0:1;
    unsigned ECCP2AS1:1;
    unsigned ECCP2AS2:1;
    unsigned ECCP2ASE:1;
  };
} ECCP2ASbits;
extern volatile near unsigned char       ECCP3DEL;
extern volatile near union {
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
    unsigned PRSEN:1;
  };
  struct {
    unsigned P3DC0:1;
    unsigned P3DC1:1;
    unsigned P3DC2:1;
    unsigned P3DC3:1;
    unsigned P3DC4:1;
    unsigned P3DC5:1;
    unsigned P3DC6:1;
    unsigned P3RSEN:1;
  };
} ECCP3DELbits;
extern volatile near unsigned char       ECCP3AS;
extern volatile near union {
  struct {
    unsigned PSSBD0:1;
    unsigned PSSBD1:1;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned PSS3BD0:1;
    unsigned PSS3BD1:1;
    unsigned PSS3AC0:1;
    unsigned PSS3AC1:1;
    unsigned ECCP3AS0:1;
    unsigned ECCP3AS1:1;
    unsigned ECCP3AS2:1;
    unsigned ECCP3ASE:1;
  };
} ECCP3ASbits;
extern volatile near unsigned char       RCSTA2;
extern volatile near union {
  struct {
    unsigned RCD8:1;
    unsigned :5;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
} RCSTA2bits;
extern volatile near unsigned char       TXSTA2;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
} TXSTA2bits;
extern volatile near unsigned char       TXREG2;
extern volatile near unsigned char       RCREG2;
extern volatile near unsigned char       SPBRG2;
extern volatile near unsigned char       CCP5CON;
extern volatile near union {
  struct {
    unsigned CCP5M0:1;
    unsigned CCP5M1:1;
    unsigned CCP5M2:1;
    unsigned CCP5M3:1;
    unsigned DCCP5Y:1;
    unsigned DCCP5X:1;
  };
  struct {
    unsigned :4;
    unsigned DC5B0:1;
    unsigned DC5B1:1;
  };
} CCP5CONbits;
extern volatile near unsigned            CCPR5;
extern volatile near unsigned char       CCPR5L;
extern volatile near unsigned char       CCPR5H;
extern volatile near unsigned char       CCP4CON;
extern volatile near union {
  struct {
    unsigned CCP4M0:1;
    unsigned CCP4M1:1;
    unsigned CCP4M2:1;
    unsigned CCP4M3:1;
    unsigned DCCP4Y:1;
    unsigned DCCP4X:1;
  };
  struct {
    unsigned :4;
    unsigned DC4B0:1;
    unsigned DC4B1:1;
  };
} CCP4CONbits;
extern volatile near unsigned            CCPR4;
extern volatile near unsigned char       CCPR4L;
extern volatile near unsigned char       CCPR4H;
extern volatile near unsigned char       T4CON;
extern volatile near struct {
  unsigned T4CKPS0:1;
  unsigned T4CKPS1:1;
  unsigned TMR4ON:1;
  unsigned T4OUTPS0:1;
  unsigned T4OUTPS1:1;
  unsigned T4OUTPS2:1;
  unsigned T4OUTPS3:1;
} T4CONbits;
extern volatile near unsigned char       PR4;
extern volatile near unsigned char       TMR4;
extern volatile near unsigned char       ECCP1DEL;
extern volatile near union {
  struct {
    unsigned PDC0:1;
    unsigned PDC1:1;
    unsigned PDC2:1;
    unsigned PDC3:1;
    unsigned PDC4:1;
    unsigned PDC5:1;
    unsigned PDC6:1;
    unsigned PRSEN:1;
  };
  struct {
    unsigned P1DC0:1;
    unsigned P1DC1:1;
    unsigned P1DC2:1;
    unsigned P1DC3:1;
    unsigned P1DC4:1;
    unsigned P1DC5:1;
    unsigned P1DC6:1;
    unsigned P1RSEN:1;
  };
} ECCP1DELbits;
extern volatile near unsigned char       BAUDCON2;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :6;
    unsigned RCIDL:1;
  };
} BAUDCON2bits;
extern volatile near unsigned char       SPBRGH2;
extern volatile near unsigned char       BAUDCON;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :6;
    unsigned RCIDL:1;
  };
} BAUDCONbits;
extern volatile near unsigned char       BAUDCON1;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCMT:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :6;
    unsigned RCIDL:1;
  };
} BAUDCON1bits;
extern volatile near unsigned char       SPBRGH1;
extern volatile near unsigned char       PORTA;
extern volatile near union {
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
  };
  struct {
    unsigned AN0:1;
    unsigned AN1:1;
    unsigned AN2:1;
    unsigned AN3:1;
    unsigned T0CKI:1;
    unsigned AN4:1;
    unsigned OSC2:1;
  };
  struct {
    unsigned :2;
    unsigned VREFM:1;
    unsigned VREFP:1;
    unsigned :2;
    unsigned CLKO:1;
  };
} PORTAbits;
extern volatile near unsigned char       PORTB;
extern volatile near union {
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
  struct {
    unsigned INT0:1;
    unsigned INT1:1;
    unsigned INT2:1;
    unsigned INT3:1;
    unsigned KBI0:1;
    unsigned KBI1:1;
    unsigned KBI2:1;
    unsigned KBI3:1;
  };
  struct {
    unsigned :4;
    unsigned PGM:1;
    unsigned PGC:1;
    unsigned PGD:1;
  };
} PORTBbits;
extern volatile near unsigned char       PORTC;
extern volatile near union {
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned RC3:1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
  struct {
    unsigned T1OSO:1;
    unsigned T1OSI:1;
    unsigned CCP1:1;
    unsigned SCK:1;
    unsigned SDI:1;
    unsigned SDO:1;
    unsigned TX:1;
    unsigned RX:1;
  };
  struct {
    unsigned T13CKI:1;
    unsigned CCP2:1;
    unsigned :1;
    unsigned SCL:1;
    unsigned SDA:1;
    unsigned :1;
    unsigned CK:1;
    unsigned DT:1;
  };
} PORTCbits;
extern volatile near unsigned char       PORTD;
extern volatile near union {
  struct {
    unsigned RD0:1;
    unsigned RD1:1;
    unsigned RD2:1;
    unsigned RD3:1;
    unsigned RD4:1;
    unsigned RD5:1;
    unsigned RD6:1;
    unsigned RD7:1;
  };
  struct {
    unsigned PSP0:1;
    unsigned PSP1:1;
    unsigned PSP2:1;
    unsigned PSP3:1;
    unsigned PSP4:1;
    unsigned PSP5:1;
    unsigned PSP6:1;
    unsigned PSP7:1;
  };
  struct {
    unsigned AD00:1;
    unsigned AD01:1;
    unsigned AD02:1;
    unsigned AD03:1;
    unsigned AD04:1;
    unsigned AD05:1;
    unsigned AD06:1;
    unsigned AD07:1;
  };
  struct {
    unsigned :5;
    unsigned SDA2:1;
    unsigned SCL2:1;
    unsigned SS2:1;
  };
  struct {
    unsigned :4;
    unsigned SDO2:1;
    unsigned SDI2:1;
    unsigned SCK2:1;
  };
} PORTDbits;
extern volatile near unsigned char       PORTE;
extern volatile near union {
  struct {
    unsigned RE0:1;
    unsigned RE1:1;
    unsigned RE2:1;
    unsigned RE3:1;
    unsigned RE4:1;
    unsigned RE5:1;
    unsigned RE6:1;
    unsigned RE7:1;
  };
  struct {
    unsigned RD:1;
    unsigned WR:1;
    unsigned CS:1;
  };
  struct {
    unsigned AD8:1;
    unsigned AD9:1;
    unsigned AD10:1;
    unsigned AD11:1;
    unsigned AD12:1;
    unsigned AD13:1;
    unsigned AD14:1;
    unsigned AD15:1;
  };
} PORTEbits;
extern volatile near unsigned char       PORTF;
extern volatile near union {
  struct {
    unsigned :1;
    unsigned RF1:1;
    unsigned RF2:1;
    unsigned RF3:1;
    unsigned RF4:1;
    unsigned RF5:1;
    unsigned RF6:1;
    unsigned RF7:1;
  };
  struct {
    unsigned :1;
    unsigned AN6:1;
    unsigned AN7:1;
    unsigned AN8:1;
    unsigned AN9:1;
    unsigned AN10:1;
    unsigned AN11:1;
    unsigned SS:1;
  };
  struct {
    unsigned :3;
    unsigned CVREF:1;
  };
} PORTFbits;
extern volatile near unsigned char       PORTG;
extern volatile near union {
  struct {
    unsigned RG0:1;
    unsigned RG1:1;
    unsigned RG2:1;
    unsigned RG3:1;
    unsigned RG4:1;
  };
  struct {
    unsigned CCP3:1;
    unsigned TX2:1;
    unsigned RX2:1;
    unsigned CCP4:1;
    unsigned CCP5:1;
  };
  struct {
    unsigned :1;
    unsigned CK2:1;
    unsigned DT2:1;
  };
  struct {
    unsigned :6;
    unsigned REPU:1;
    unsigned RDPU:1;
  };
} PORTGbits;
extern volatile near unsigned char       LATA;
extern volatile near struct {
  unsigned LATA0:1;
  unsigned LATA1:1;
  unsigned LATA2:1;
  unsigned LATA3:1;
  unsigned LATA4:1;
  unsigned LATA5:1;
} LATAbits;
extern volatile near unsigned char       LATB;
extern volatile near struct {
  unsigned LATB0:1;
  unsigned LATB1:1;
  unsigned LATB2:1;
  unsigned LATB3:1;
  unsigned LATB4:1;
  unsigned LATB5:1;
  unsigned LATB6:1;
  unsigned LATB7:1;
} LATBbits;
extern volatile near unsigned char       LATC;
extern volatile near struct {
  unsigned LATC0:1;
  unsigned LATC1:1;
  unsigned LATC2:1;
  unsigned LATC3:1;
  unsigned LATC4:1;
  unsigned LATC5:1;
  unsigned LATC6:1;
  unsigned LATC7:1;
} LATCbits;
extern volatile near unsigned char       LATD;
extern volatile near struct {
  unsigned LATD0:1;
  unsigned LATD1:1;
  unsigned LATD2:1;
  unsigned LATD3:1;
  unsigned LATD4:1;
  unsigned LATD5:1;
  unsigned LATD6:1;
  unsigned LATD7:1;
} LATDbits;
extern volatile near unsigned char       LATE;
extern volatile near struct {
  unsigned LATE0:1;
  unsigned LATE1:1;
  unsigned LATE2:1;
  unsigned LATE3:1;
  unsigned LATE4:1;
  unsigned LATE5:1;
  unsigned LATE6:1;
  unsigned LATE7:1;
} LATEbits;
extern volatile near unsigned char       LATF;
extern volatile near struct {
  unsigned :1;
  unsigned LATF1:1;
  unsigned LATF2:1;
  unsigned LATF3:1;
  unsigned LATF4:1;
  unsigned LATF5:1;
  unsigned LATF6:1;
  unsigned LATF7:1;
} LATFbits;
extern volatile near unsigned char       LATG;
extern volatile near struct {
  unsigned LATG0:1;
  unsigned LATG1:1;
  unsigned LATG2:1;
  unsigned LATG3:1;
  unsigned LATG4:1;
} LATGbits;
extern volatile near unsigned char       DDRA;
extern volatile near struct {
  unsigned RA0:1;
  unsigned RA1:1;
  unsigned RA2:1;
  unsigned RA3:1;
  unsigned RA4:1;
  unsigned RA5:1;
} DDRAbits;
extern volatile near unsigned char       TRISA;
extern volatile near struct {
  unsigned TRISA0:1;
  unsigned TRISA1:1;
  unsigned TRISA2:1;
  unsigned TRISA3:1;
  unsigned TRISA4:1;
  unsigned TRISA5:1;
} TRISAbits;
extern volatile near unsigned char       DDRB;
extern volatile near struct {
  unsigned RB0:1;
  unsigned RB1:1;
  unsigned RB2:1;
  unsigned RB3:1;
  unsigned RB4:1;
  unsigned RB5:1;
  unsigned RB6:1;
  unsigned RB7:1;
} DDRBbits;
extern volatile near unsigned char       TRISB;
extern volatile near struct {
  unsigned TRISB0:1;
  unsigned TRISB1:1;
  unsigned TRISB2:1;
  unsigned TRISB3:1;
  unsigned TRISB4:1;
  unsigned TRISB5:1;
  unsigned TRISB6:1;
  unsigned TRISB7:1;
} TRISBbits;
extern volatile near unsigned char       DDRC;
extern volatile near struct {
  unsigned RC0:1;
  unsigned RC1:1;
  unsigned RC2:1;
  unsigned RC3:1;
  unsigned RC4:1;
  unsigned RC5:1;
  unsigned RC6:1;
  unsigned RC7:1;
} DDRCbits;
extern volatile near unsigned char       TRISC;
extern volatile near struct {
  unsigned TRISC0:1;
  unsigned TRISC1:1;
  unsigned TRISC2:1;
  unsigned TRISC3:1;
  unsigned TRISC4:1;
  unsigned TRISC5:1;
  unsigned TRISC6:1;
  unsigned TRISC7:1;
} TRISCbits;
extern volatile near unsigned char       DDRD;
extern volatile near struct {
  unsigned RD0:1;
  unsigned RD1:1;
  unsigned RD2:1;
  unsigned RD3:1;
  unsigned RD4:1;
  unsigned RD5:1;
  unsigned RD6:1;
  unsigned RD7:1;
} DDRDbits;
extern volatile near unsigned char       TRISD;
extern volatile near struct {
  unsigned TRISD0:1;
  unsigned TRISD1:1;
  unsigned TRISD2:1;
  unsigned TRISD3:1;
  unsigned TRISD4:1;
  unsigned TRISD5:1;
  unsigned TRISD6:1;
  unsigned TRISD7:1;
} TRISDbits;
extern volatile near unsigned char       DDRE;
extern volatile near struct {
  unsigned RE0:1;
  unsigned RE1:1;
  unsigned RE2:1;
  unsigned RE3:1;
  unsigned RE4:1;
  unsigned RE5:1;
  unsigned RE6:1;
  unsigned RE7:1;
} DDREbits;
extern volatile near unsigned char       TRISE;
extern volatile near struct {
  unsigned TRISE0:1;
  unsigned TRISE1:1;
  unsigned TRISE2:1;
  unsigned TRISE3:1;
  unsigned TRISE4:1;
  unsigned TRISE5:1;
  unsigned TRISE6:1;
  unsigned TRISE7:1;
} TRISEbits;
extern volatile near unsigned char       DDRF;
extern volatile near struct {
  unsigned :1;
  unsigned RF1:1;
  unsigned RF2:1;
  unsigned RF3:1;
  unsigned RF4:1;
  unsigned RF5:1;
  unsigned RF6:1;
  unsigned RF7:1;
} DDRFbits;
extern volatile near unsigned char       TRISF;
extern volatile near struct {
  unsigned :1;
  unsigned TRISF1:1;
  unsigned TRISF2:1;
  unsigned TRISF3:1;
  unsigned TRISF4:1;
  unsigned TRISF5:1;
  unsigned TRISF6:1;
  unsigned TRISF7:1;
} TRISFbits;
extern volatile near unsigned char       DDRG;
extern volatile near struct {
  unsigned RG0:1;
  unsigned RG1:1;
  unsigned RG2:1;
  unsigned RG3:1;
  unsigned RG4:1;
} DDRGbits;
extern volatile near unsigned char       TRISG;
extern volatile near struct {
  unsigned TRISG0:1;
  unsigned TRISG1:1;
  unsigned TRISG2:1;
  unsigned TRISG3:1;
  unsigned TRISG4:1;
} TRISGbits;
extern volatile near unsigned char       OSCTUNE;
extern volatile near struct {
  unsigned :6;
  unsigned PLLEN:1;
} OSCTUNEbits;
extern volatile near unsigned char       PIE1;
extern volatile near union {
  struct {
    unsigned TMR1IE:1;
    unsigned TMR2IE:1;
    unsigned CCP1IE:1;
    unsigned SSPIE:1;
    unsigned TXIE:1;
    unsigned RCIE:1;
    unsigned ADIE:1;
    unsigned PSPIE:1;
  };
  struct {
    unsigned :3;
    unsigned SSP1IE:1;
    unsigned TX1IE:1;
    unsigned RC1IE:1;
  };
} PIE1bits;
extern volatile near unsigned char       PIR1;
extern volatile near union {
  struct {
    unsigned TMR1IF:1;
    unsigned TMR2IF:1;
    unsigned CCP1IF:1;
    unsigned SSPIF:1;
    unsigned TXIF:1;
    unsigned RCIF:1;
    unsigned ADIF:1;
    unsigned PSPIF:1;
  };
  struct {
    unsigned :3;
    unsigned SSP1IF:1;
    unsigned TX1IF:1;
    unsigned RC1IF:1;
  };
} PIR1bits;
extern volatile near unsigned char       IPR1;
extern volatile near union {
  struct {
    unsigned TMR1IP:1;
    unsigned TMR2IP:1;
    unsigned CCP1IP:1;
    unsigned SSPIP:1;
    unsigned TXIP:1;
    unsigned RCIP:1;
    unsigned ADIP:1;
    unsigned PSPIP:1;
  };
  struct {
    unsigned :3;
    unsigned SSP1IP:1;
    unsigned TX1IP:1;
    unsigned RC1IP:1;
  };
} IPR1bits;
extern volatile near unsigned char       PIE2;
extern volatile near union {
  struct {
    unsigned CCP2IE:1;
    unsigned TMR3IE:1;
    unsigned :1;
    unsigned BCLIE:1;
    unsigned :2;
    unsigned CMIE:1;
    unsigned OSCFIE:1;
  };
  struct {
    unsigned :3;
    unsigned BCL1IE:1;
  };
} PIE2bits;
extern volatile near unsigned char       PIR2;
extern volatile near union {
  struct {
    unsigned CCP2IF:1;
    unsigned TMR3IF:1;
    unsigned :1;
    unsigned BCLIF:1;
    unsigned :2;
    unsigned CMIF:1;
    unsigned OSCFIF:1;
  };
  struct {
    unsigned :3;
    unsigned BCL1IF:1;
  };
} PIR2bits;
extern volatile near unsigned char       IPR2;
extern volatile near union {
  struct {
    unsigned CCP2IP:1;
    unsigned TMR3IP:1;
    unsigned :1;
    unsigned BCLIP:1;
    unsigned :2;
    unsigned CMIP:1;
    unsigned OSCFIP:1;
  };
  struct {
    unsigned :3;
    unsigned BCL1IP:1;
  };
} IPR2bits;
extern volatile near unsigned char       PIE3;
extern volatile near struct {
  unsigned CCP3IE:1;
  unsigned CCP4IE:1;
  unsigned CCP5IE:1;
  unsigned TMR4IE:1;
  unsigned TX2IE:1;
  unsigned RC2IE:1;
  unsigned BCL2IE:1;
  unsigned SSP2IE:1;
} PIE3bits;
extern volatile near unsigned char       PIR3;
extern volatile near struct {
  unsigned CCP3IF:1;
  unsigned CCP4IF:1;
  unsigned CCP5IF:1;
  unsigned TMR4IF:1;
  unsigned TX2IF:1;
  unsigned RC2IF:1;
  unsigned BCL2IF:1;
  unsigned SSP2IF:1;
} PIR3bits;
extern volatile near unsigned char       IPR3;
extern volatile near struct {
  unsigned CCP3IP:1;
  unsigned CCP4IP:1;
  unsigned CCP5IP:1;
  unsigned TMR4IP:1;
  unsigned TX2IP:1;
  unsigned RC2IP:1;
  unsigned BCL2IP:1;
  unsigned SSP2IP:1;
} IPR3bits;
extern volatile near unsigned char       EECON1;
extern volatile near struct {
  unsigned :1;
  unsigned WR:1;
  unsigned WREN:1;
  unsigned WRERR:1;
  unsigned FREE:1;
} EECON1bits;
extern volatile near unsigned char       EECON2;
extern volatile near unsigned char       RCSTA;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned RCD8:1;
    unsigned :5;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
} RCSTAbits;
extern volatile near unsigned char       RCSTA1;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned RCD8:1;
    unsigned :5;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
} RCSTA1bits;
extern volatile near unsigned char       TXSTA;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
} TXSTAbits;
extern volatile near unsigned char       TXSTA1;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
} TXSTA1bits;
extern volatile near unsigned char       TXREG;
extern volatile near unsigned char       TXREG1;
extern volatile near unsigned char       RCREG;
extern volatile near unsigned char       RCREG1;
extern volatile near unsigned char       SPBRG;
extern volatile near unsigned char       SPBRG1;
extern volatile near unsigned char       PSPCON;
extern volatile near struct {
  unsigned :4;
  unsigned PSPMODE:1;
  unsigned IBOV:1;
  unsigned OBF:1;
  unsigned IBF:1;
} PSPCONbits;
extern volatile near unsigned char       T3CON;
extern volatile near union {
  struct {
    unsigned TMR3ON:1;
    unsigned TMR3CS:1;
    unsigned T3SYNC:1;
    unsigned T3CCP1:1;
    unsigned T3CKPS0:1;
    unsigned T3CKPS1:1;
    unsigned T3CCP2:1;
    unsigned RD16:1;
  };
  struct {
    unsigned :2;
    unsigned T3INSYNC:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_T3SYNC:1;
  };
} T3CONbits;
extern volatile near unsigned char       TMR3L;
extern volatile near unsigned char       TMR3H;
extern volatile near unsigned char       CMCON;
extern volatile near struct {
  unsigned CM0:1;
  unsigned CM1:1;
  unsigned CM2:1;
  unsigned CIS:1;
  unsigned C1INV:1;
  unsigned C2INV:1;
  unsigned C1OUT:1;
  unsigned C2OUT:1;
} CMCONbits;
extern volatile near unsigned char       CVRCON;
extern volatile near struct {
  unsigned CVR0:1;
  unsigned CVR1:1;
  unsigned CVR2:1;
  unsigned CVR3:1;
  unsigned CVRSS:1;
  unsigned CVRR:1;
  unsigned CVROE:1;
  unsigned CVREN:1;
} CVRCONbits;
extern volatile near unsigned char       ECCP1AS;
extern volatile near union {
  struct {
    unsigned :2;
    unsigned PSSAC0:1;
    unsigned PSSAC1:1;
    unsigned ECCPAS0:1;
    unsigned ECCPAS1:1;
    unsigned ECCPAS2:1;
    unsigned ECCPASE:1;
  };
  struct {
    unsigned :2;
    unsigned PSS1AC0:1;
    unsigned PSS1AC1:1;
    unsigned ECCP1AS0:1;
    unsigned ECCP1AS1:1;
    unsigned ECCP1AS2:1;
    unsigned ECCP1ASE:1;
  };
} ECCP1ASbits;
extern volatile near unsigned char       CCP3CON;
extern volatile near union {
  struct {
    unsigned CCP3M0:1;
    unsigned CCP3M1:1;
    unsigned CCP3M2:1;
    unsigned CCP3M3:1;
    unsigned DC3B0:1;
    unsigned DC3B1:1;
    unsigned P3M0:1;
    unsigned P3M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP3Y:1;
    unsigned CCP3X:1;
  };
} CCP3CONbits;
extern volatile near unsigned char       ECCP3CON;
extern volatile near union {
  struct {
    unsigned CCP3M0:1;
    unsigned CCP3M1:1;
    unsigned CCP3M2:1;
    unsigned CCP3M3:1;
    unsigned DC3B0:1;
    unsigned DC3B1:1;
    unsigned P3M0:1;
    unsigned P3M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP3Y:1;
    unsigned CCP3X:1;
  };
} ECCP3CONbits;
extern volatile near unsigned            CCPR3;
extern volatile near unsigned char       CCPR3L;
extern volatile near unsigned char       CCPR3H;
extern volatile near unsigned char       CCP2CON;
extern volatile near union {
  struct {
    unsigned CCP2M0:1;
    unsigned CCP2M1:1;
    unsigned CCP2M2:1;
    unsigned CCP2M3:1;
    unsigned DC2B0:1;
    unsigned DC2B1:1;
    unsigned P2M0:1;
    unsigned P2M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP2Y:1;
    unsigned CCP2X:1;
  };
} CCP2CONbits;
extern volatile near unsigned char       ECCP2CON;
extern volatile near union {
  struct {
    unsigned CCP2M0:1;
    unsigned CCP2M1:1;
    unsigned CCP2M2:1;
    unsigned CCP2M3:1;
    unsigned DC2B0:1;
    unsigned DC2B1:1;
    unsigned P2M0:1;
    unsigned P2M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP2Y:1;
    unsigned CCP2X:1;
  };
} ECCP2CONbits;
extern volatile near unsigned              CCPR2;
extern volatile near unsigned char       CCPR2L;
extern volatile near unsigned char       CCPR2H;
extern volatile near unsigned char       CCP1CON;
extern volatile near union {
  struct {
    unsigned CCP1M0:1;
    unsigned CCP1M1:1;
    unsigned CCP1M2:1;
    unsigned CCP1M3:1;
    unsigned DC1B0:1;
    unsigned DC1B1:1;
    unsigned P1M0:1;
    unsigned P1M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP1Y:1;
    unsigned CCP1X:1;
  };
} CCP1CONbits;
extern volatile near unsigned char       ECCP1CON;
extern volatile near union {
  struct {
    unsigned CCP1M0:1;
    unsigned CCP1M1:1;
    unsigned CCP1M2:1;
    unsigned CCP1M3:1;
    unsigned DC1B0:1;
    unsigned DC1B1:1;
    unsigned P1M0:1;
    unsigned P1M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP1Y:1;
    unsigned CCP1X:1;
  };
} ECCP1CONbits;
extern volatile near unsigned            CCPR1;
extern volatile near unsigned char       CCPR1L;
extern volatile near unsigned char       CCPR1H;
extern volatile near unsigned char       ADCON2;
extern volatile near union {
  struct {
    unsigned ADCS0:1;
    unsigned ADCS1:1;
    unsigned ADCS2:1;
    unsigned ACQT0:1;
    unsigned ACQT1:1;
    unsigned ACQT2:1;
    unsigned :1;
    unsigned ADFM:1;
  };
  struct {                 
    unsigned ADCS: 3;      
    unsigned ACQT: 3;      
  };                        
} ADCON2bits;
extern volatile near unsigned char       ADCON1;
extern volatile near union {
  struct {
    unsigned PCFG0:1;
    unsigned PCFG1:1;
    unsigned PCFG2:1;
    unsigned PCFG3:1;
    unsigned VCFG0:1;
    unsigned VCFG1:1;
  };
  struct {                 
    unsigned PCFG: 4;      
    unsigned VCFG: 2;      
  };                        
} ADCON1bits;
extern volatile near unsigned char       ADCON0;
extern volatile near union {
  struct {
    unsigned :1;
    unsigned DONE:1;
  };
  struct {
    unsigned :1;
    unsigned GO_DONE:1;
  };
  struct {
    unsigned ADON:1;
    unsigned GO:1;
    unsigned CHS0:1;
    unsigned CHS1:1;
    unsigned CHS2:1;
    unsigned CHS3:1;
    unsigned :1;
    unsigned ADCAL:1;
  };
  struct {
    unsigned :1;
    unsigned NOT_DONE:1;
  };
  struct {                 
    unsigned :2;           
    unsigned CHS:4;        
  };                       
} ADCON0bits;
extern volatile near unsigned            ADRES;
extern volatile near unsigned char       ADRESL;
extern volatile near unsigned char       ADRESH;
extern volatile near unsigned char       SSP1CON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
} SSP1CON2bits;
extern volatile near unsigned char       SSPCON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
} SSPCON2bits;
extern volatile near unsigned char       SSP1CON1;
extern volatile near struct {
  unsigned SSPM0:1;
  unsigned SSPM1:1;
  unsigned SSPM2:1;
  unsigned SSPM3:1;
  unsigned CKP:1;
  unsigned SSPEN:1;
  unsigned SSPOV:1;
  unsigned WCOL:1;
} SSP1CON1bits;
extern volatile near unsigned char       SSPCON1;
extern volatile near struct {
  unsigned SSPM0:1;
  unsigned SSPM1:1;
  unsigned SSPM2:1;
  unsigned SSPM3:1;
  unsigned CKP:1;
  unsigned SSPEN:1;
  unsigned SSPOV:1;
  unsigned WCOL:1;
} SSPCON1bits;
extern volatile near unsigned char       SSP1STAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSP1STATbits;
extern volatile near unsigned char       SSPSTAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSPSTATbits;
extern volatile near unsigned char       SSP1ADD;
extern volatile near unsigned char       SSPADD;
extern volatile near unsigned char       SSP1BUF;
extern volatile near unsigned char       SSPBUF;
extern volatile near unsigned char       T2CON;
extern volatile near union {
  struct{
    unsigned T2CKPS0:1;
    unsigned T2CKPS1:1;
    unsigned TMR2ON:1;
    unsigned T2OUTPS0:1;
    unsigned T2OUTPS1:1;
    unsigned T2OUTPS2:1;
    unsigned T2OUTPS3:1;
  };
  struct {                       
    unsigned T2CKPS: 2;          
    unsigned :1;                 
    unsigned T2OUTPS: 4;         
  };                             
} T2CONbits;
extern volatile near unsigned char       PR2;
extern volatile near unsigned char       TMR2;
extern volatile near unsigned char       T1CON;
extern volatile near union {
  struct {
    unsigned TMR1ON:1;
    unsigned TMR1CS:1;
    unsigned T1SYNC:1;
    unsigned T1OSCEN:1;
    unsigned T1CKPS0:1;
    unsigned T1CKPS1:1;
    unsigned T1RUN:1;
    unsigned RD16:1;
  };
  struct {
    unsigned :2;
    unsigned T1INSYNC:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_T1SYNC:1;
  };
  struct {                       
    unsigned :4;                 
    unsigned T1CKPS: 2;          
  };                             
} T1CONbits;
extern volatile near unsigned char       TMR1L;
extern volatile near unsigned char       TMR1H;
extern volatile near unsigned char       RCON;
extern volatile near union {
  struct {
    unsigned NOT_BOR:1;
    unsigned NOT_POR:1;
    unsigned NOT_PD:1;
    unsigned NOT_TO:1;
    unsigned NOT_RI:1;
    unsigned :2;
    unsigned IPEN:1;
  };
  struct {
    unsigned BOR:1;
    unsigned POR:1;
    unsigned PD:1;
    unsigned TO:1;
    unsigned RI:1;
  };
} RCONbits;
extern volatile near unsigned char       WDTCON;
extern volatile near union {
  struct {
    unsigned SWDTE:1;
  };
  struct {
    unsigned SWDTEN:1;
  };
} WDTCONbits;
extern volatile near unsigned char       OSCCON;
extern volatile near struct {
  unsigned SCS0:1;
  unsigned SCS1:1;
  unsigned :1;
  unsigned OSTS:1;
  unsigned :3;
  unsigned IDLEN:1;
} OSCCONbits;
extern volatile near unsigned char       T0CON;
extern volatile near union {
  struct {
    unsigned T0PS0:1;
    unsigned T0PS1:1;
    unsigned T0PS2:1;
    unsigned PSA:1;
    unsigned T0SE:1;
    unsigned T0CS:1;
    unsigned T08BIT:1;
    unsigned TMR0ON:1;
  };
  struct {
    unsigned :3;
    unsigned T0PS3:1;
  };
  struct {                     
    unsigned T0PS: 3;          
  };                           
} T0CONbits;
extern volatile near unsigned char       TMR0L;
extern volatile near unsigned char       TMR0H;
extern          near unsigned char       STATUS;
extern          near struct {
  unsigned C:1;
  unsigned DC:1;
  unsigned Z:1;
  unsigned OV:1;
  unsigned N:1;
} STATUSbits;
extern          near unsigned            FSR2;
extern          near unsigned char       FSR2L;
extern          near unsigned char       FSR2H;
extern volatile near unsigned char       PLUSW2;
extern volatile near unsigned char       PREINC2;
extern volatile near unsigned char       POSTDEC2;
extern volatile near unsigned char       POSTINC2;
extern          near unsigned char       INDF2;
extern          near unsigned char       BSR;
extern          near unsigned            FSR1;
extern          near unsigned char       FSR1L;
extern          near unsigned char       FSR1H;
extern volatile near unsigned char       PLUSW1;
extern volatile near unsigned char       PREINC1;
extern volatile near unsigned char       POSTDEC1;
extern volatile near unsigned char       POSTINC1;
extern          near unsigned char       INDF1;
extern          near unsigned char       WREG;
extern          near unsigned            FSR0;
extern          near unsigned char       FSR0L;
extern          near unsigned char       FSR0H;
extern volatile near unsigned char       PLUSW0;
extern volatile near unsigned char       PREINC0;
extern volatile near unsigned char       POSTDEC0;
extern volatile near unsigned char       POSTINC0;
extern          near unsigned char       INDF0;
extern volatile near unsigned char       INTCON3;
extern volatile near union {
  struct {
    unsigned INT1F:1;
    unsigned INT2F:1;
    unsigned INT3F:1;
    unsigned INT1E:1;
    unsigned INT2E:1;
    unsigned INT3E:1;
    unsigned INT1P:1;
    unsigned INT2P:1;
  };
  struct {
    unsigned INT1IF:1;
    unsigned INT2IF:1;
    unsigned INT3IF:1;
    unsigned INT1IE:1;
    unsigned INT2IE:1;
    unsigned INT3IE:1;
    unsigned INT1IP:1;
    unsigned INT2IP:1;
  };
} INTCON3bits;
extern volatile near unsigned char       INTCON2;
extern volatile near union {
  struct {
    unsigned RBIP:1;
    unsigned INT3P:1;
    unsigned T0IP:1;
    unsigned INTEDG3:1;
    unsigned INTEDG2:1;
    unsigned INTEDG1:1;
    unsigned INTEDG0:1;
    unsigned NOT_RBPU:1;
  };
  struct {
    unsigned :1;
    unsigned INT3IP:1;
    unsigned TMR0IP:1;
    unsigned :4;
    unsigned RBPU:1;
  };
} INTCON2bits;
extern volatile near unsigned char       INTCON;
extern volatile near union {
  struct {
    unsigned RBIF:1;
    unsigned INT0F:1;
    unsigned T0IF:1;
    unsigned RBIE:1;
    unsigned INT0E:1;
    unsigned T0IE:1;
    unsigned PEIE:1;
    unsigned GIE:1;
  };
  struct {
    unsigned :1;
    unsigned INT0IF:1;
    unsigned TMR0IF:1;
    unsigned :1;
    unsigned INT0IE:1;
    unsigned TMR0IE:1;
    unsigned GIEL:1;
    unsigned GIEH:1;
  };
} INTCONbits;
extern          near unsigned            PROD;
extern          near unsigned char       PRODL;
extern          near unsigned char       PRODH;
extern volatile near unsigned char       TABLAT;
extern volatile near unsigned short long TBLPTR;
extern volatile near unsigned char       TBLPTRL;
extern volatile near unsigned char       TBLPTRH;
extern volatile near unsigned char       TBLPTRU;
extern volatile near unsigned short long PC;
extern volatile near unsigned char       PCL;
extern volatile near unsigned char       PCLATH;
extern volatile near unsigned char       PCLATU;
extern volatile near unsigned char       STKPTR;
extern volatile near union {
  struct {
    unsigned STKPTR0:1;
    unsigned STKPTR1:1;
    unsigned STKPTR2:1;
    unsigned STKPTR3:1;
    unsigned STKPTR4:1;
    unsigned :1;
    unsigned STKUNF:1;
    unsigned STKOVF:1;
  };
  struct {
    unsigned SP0:1;
    unsigned SP1:1;
    unsigned SP2:1;
    unsigned SP3:1;
    unsigned SP4:1;
    unsigned :2;
    unsigned STKFUL:1;
  };
} STKPTRbits;
extern          near unsigned short long TOS;
extern          near unsigned char       TOSL;
extern          near unsigned char       TOSH;
extern          near unsigned char       TOSU;



#line 1701 "./DrvPic18f67J10.h"
 
#line 1703 "./DrvPic18f67J10.h"
#line 1704 "./DrvPic18f67J10.h"


#line 1707 "./DrvPic18f67J10.h"
 
#line 1709 "./DrvPic18f67J10.h"
#line 1710 "./DrvPic18f67J10.h"
#line 1711 "./DrvPic18f67J10.h"
#line 1712 "./DrvPic18f67J10.h"

#line 1714 "./DrvPic18f67J10.h"
#line 1715 "./DrvPic18f67J10.h"
#line 1716 "./DrvPic18f67J10.h"
#line 1717 "./DrvPic18f67J10.h"
#line 1718 "./DrvPic18f67J10.h"


#line 1722 "./DrvPic18f67J10.h"
 
#line 1724 "./DrvPic18f67J10.h"


#line 1727 "./DrvPic18f67J10.h"
#line 42 "DrvTimer_18F87J10.c"


#line 1 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"

#line 29 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
 


#line 33 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"







#line 1 "./DrvPic18f67J10.h"

#line 5 "./DrvPic18f67J10.h"
 


#line 1701 "./DrvPic18f67J10.h"

#line 1707 "./DrvPic18f67J10.h"

#line 1722 "./DrvPic18f67J10.h"
#line 1727 "./DrvPic18f67J10.h"
#line 40 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"









typedef  signed 	char 			INT8;
typedef  signed 	int 			INT16;
typedef  signed 	short long  INT24;
typedef  signed 	long 			INT32;
typedef  signed	void			INT64;

typedef  unsigned char 			UINT8;
typedef  unsigned int 			UINT16;
typedef  unsigned short long 	UINT24;
typedef  unsigned long 			UINT32;
typedef  unsigned	void			UINT64;


typedef signed    int         INT;
typedef unsigned  int         UINT;


typedef  float						FLT32;
typedef  void						FLT64;


typedef  unsigned char 			CHAR;
typedef  unsigned int 			WCHAR;



typedef  unsigned char        BIT;
typedef  unsigned char 			BYTE;
typedef  unsigned int 			WORD;
typedef  unsigned long 			DWORD;
typedef  unsigned short long 	TWORD;
typedef  unsigned void			QWORD;


typedef  unsigned int         BITS;


typedef enum {
	BOOL_FALSE  = 0,
	BOOL_TRUE	= 1
} _Bool, *BoolPtr;


#line 93 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 94 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"


#line 97 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 98 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"


#line 101 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 102 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"





typedef struct
{
   UINT8    Seconds;
   UINT8    Minutes;
   UINT8    Hours;
   UINT8    Date;
   UINT8    Month;
   UINT16   Year;
} _DateTime, *_DateTimePtr;








#line 125 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 126 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 127 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 128 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"







#line 136 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"

#line 138 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 139 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 140 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 141 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"

#line 143 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 144 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"








#line 153 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 154 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"







#line 162 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 44 "DrvTimer_18F87J10.c"

#line 1 "./DrvMdxP600.h"

#line 23 "./DrvMdxP600.h"
 


#line 27 "./DrvMdxP600.h"







#line 1 "./DrvPic18f67J10.h"

#line 5 "./DrvPic18f67J10.h"
 


#line 1701 "./DrvPic18f67J10.h"

#line 1707 "./DrvPic18f67J10.h"

#line 1722 "./DrvPic18f67J10.h"
#line 1727 "./DrvPic18f67J10.h"
#line 34 "./DrvMdxP600.h"


#line 1 "C:/MCC18/h/delays.h"

#line 3 "C:/MCC18/h/delays.h"


#line 13 "C:/MCC18/h/delays.h"
 

 
#line 1 "C:/MCC18/h/p18cxxx.h"

#line 3 "C:/MCC18/h/p18cxxx.h"

#line 5 "C:/MCC18/h/p18cxxx.h"
#line 7 "C:/MCC18/h/p18cxxx.h"
#line 9 "C:/MCC18/h/p18cxxx.h"
#line 11 "C:/MCC18/h/p18cxxx.h"
#line 13 "C:/MCC18/h/p18cxxx.h"
#line 15 "C:/MCC18/h/p18cxxx.h"
#line 17 "C:/MCC18/h/p18cxxx.h"
#line 19 "C:/MCC18/h/p18cxxx.h"
#line 21 "C:/MCC18/h/p18cxxx.h"
#line 23 "C:/MCC18/h/p18cxxx.h"
#line 25 "C:/MCC18/h/p18cxxx.h"
#line 27 "C:/MCC18/h/p18cxxx.h"
#line 29 "C:/MCC18/h/p18cxxx.h"
#line 31 "C:/MCC18/h/p18cxxx.h"
#line 33 "C:/MCC18/h/p18cxxx.h"
#line 35 "C:/MCC18/h/p18cxxx.h"
#line 37 "C:/MCC18/h/p18cxxx.h"
#line 39 "C:/MCC18/h/p18cxxx.h"
#line 41 "C:/MCC18/h/p18cxxx.h"
#line 43 "C:/MCC18/h/p18cxxx.h"
#line 45 "C:/MCC18/h/p18cxxx.h"
#line 47 "C:/MCC18/h/p18cxxx.h"
#line 49 "C:/MCC18/h/p18cxxx.h"
#line 51 "C:/MCC18/h/p18cxxx.h"
#line 53 "C:/MCC18/h/p18cxxx.h"
#line 55 "C:/MCC18/h/p18cxxx.h"
#line 57 "C:/MCC18/h/p18cxxx.h"
#line 59 "C:/MCC18/h/p18cxxx.h"
#line 61 "C:/MCC18/h/p18cxxx.h"
#line 63 "C:/MCC18/h/p18cxxx.h"
#line 65 "C:/MCC18/h/p18cxxx.h"
#line 67 "C:/MCC18/h/p18cxxx.h"
#line 69 "C:/MCC18/h/p18cxxx.h"
#line 71 "C:/MCC18/h/p18cxxx.h"
#line 73 "C:/MCC18/h/p18cxxx.h"
#line 75 "C:/MCC18/h/p18cxxx.h"
#line 77 "C:/MCC18/h/p18cxxx.h"
#line 79 "C:/MCC18/h/p18cxxx.h"
#line 81 "C:/MCC18/h/p18cxxx.h"
#line 83 "C:/MCC18/h/p18cxxx.h"
#line 85 "C:/MCC18/h/p18cxxx.h"
#line 87 "C:/MCC18/h/p18cxxx.h"
#line 89 "C:/MCC18/h/p18cxxx.h"
#line 91 "C:/MCC18/h/p18cxxx.h"
#line 93 "C:/MCC18/h/p18cxxx.h"
#line 95 "C:/MCC18/h/p18cxxx.h"
#line 97 "C:/MCC18/h/p18cxxx.h"
#line 99 "C:/MCC18/h/p18cxxx.h"
#line 101 "C:/MCC18/h/p18cxxx.h"
#line 103 "C:/MCC18/h/p18cxxx.h"
#line 105 "C:/MCC18/h/p18cxxx.h"
#line 107 "C:/MCC18/h/p18cxxx.h"
#line 109 "C:/MCC18/h/p18cxxx.h"
#line 111 "C:/MCC18/h/p18cxxx.h"
#line 113 "C:/MCC18/h/p18cxxx.h"
#line 115 "C:/MCC18/h/p18cxxx.h"
#line 117 "C:/MCC18/h/p18cxxx.h"
#line 119 "C:/MCC18/h/p18cxxx.h"
#line 121 "C:/MCC18/h/p18cxxx.h"
#line 123 "C:/MCC18/h/p18cxxx.h"
#line 125 "C:/MCC18/h/p18cxxx.h"
#line 127 "C:/MCC18/h/p18cxxx.h"
#line 129 "C:/MCC18/h/p18cxxx.h"
#line 131 "C:/MCC18/h/p18cxxx.h"
#line 133 "C:/MCC18/h/p18cxxx.h"
#line 135 "C:/MCC18/h/p18cxxx.h"
#line 137 "C:/MCC18/h/p18cxxx.h"
#line 139 "C:/MCC18/h/p18cxxx.h"
#line 141 "C:/MCC18/h/p18cxxx.h"
#line 143 "C:/MCC18/h/p18cxxx.h"
#line 145 "C:/MCC18/h/p18cxxx.h"
#line 147 "C:/MCC18/h/p18cxxx.h"
#line 149 "C:/MCC18/h/p18cxxx.h"
#line 151 "C:/MCC18/h/p18cxxx.h"
#line 153 "C:/MCC18/h/p18cxxx.h"
#line 155 "C:/MCC18/h/p18cxxx.h"
#line 157 "C:/MCC18/h/p18cxxx.h"
#line 159 "C:/MCC18/h/p18cxxx.h"
#line 161 "C:/MCC18/h/p18cxxx.h"
#line 163 "C:/MCC18/h/p18cxxx.h"
#line 165 "C:/MCC18/h/p18cxxx.h"
#line 167 "C:/MCC18/h/p18cxxx.h"
#line 169 "C:/MCC18/h/p18cxxx.h"
#line 171 "C:/MCC18/h/p18cxxx.h"
#line 173 "C:/MCC18/h/p18cxxx.h"
#line 175 "C:/MCC18/h/p18cxxx.h"
#line 177 "C:/MCC18/h/p18cxxx.h"
#line 179 "C:/MCC18/h/p18cxxx.h"
#line 181 "C:/MCC18/h/p18cxxx.h"
#line 183 "C:/MCC18/h/p18cxxx.h"
#line 185 "C:/MCC18/h/p18cxxx.h"
#line 187 "C:/MCC18/h/p18cxxx.h"
#line 189 "C:/MCC18/h/p18cxxx.h"
#line 191 "C:/MCC18/h/p18cxxx.h"
#line 193 "C:/MCC18/h/p18cxxx.h"
#line 195 "C:/MCC18/h/p18cxxx.h"
#line 197 "C:/MCC18/h/p18cxxx.h"
#line 199 "C:/MCC18/h/p18cxxx.h"
#line 201 "C:/MCC18/h/p18cxxx.h"
#line 203 "C:/MCC18/h/p18cxxx.h"
#line 205 "C:/MCC18/h/p18cxxx.h"
#line 207 "C:/MCC18/h/p18cxxx.h"
#line 209 "C:/MCC18/h/p18cxxx.h"
#line 211 "C:/MCC18/h/p18cxxx.h"
#line 213 "C:/MCC18/h/p18cxxx.h"
#line 215 "C:/MCC18/h/p18cxxx.h"
#line 217 "C:/MCC18/h/p18cxxx.h"
#line 219 "C:/MCC18/h/p18cxxx.h"
#line 221 "C:/MCC18/h/p18cxxx.h"
#line 223 "C:/MCC18/h/p18cxxx.h"
#line 225 "C:/MCC18/h/p18cxxx.h"
#line 227 "C:/MCC18/h/p18cxxx.h"
#line 229 "C:/MCC18/h/p18cxxx.h"
#line 231 "C:/MCC18/h/p18cxxx.h"
#line 233 "C:/MCC18/h/p18cxxx.h"
#line 235 "C:/MCC18/h/p18cxxx.h"
#line 237 "C:/MCC18/h/p18cxxx.h"
#line 239 "C:/MCC18/h/p18cxxx.h"
#line 241 "C:/MCC18/h/p18cxxx.h"
#line 243 "C:/MCC18/h/p18cxxx.h"
#line 245 "C:/MCC18/h/p18cxxx.h"
#line 247 "C:/MCC18/h/p18cxxx.h"
#line 249 "C:/MCC18/h/p18cxxx.h"
#line 251 "C:/MCC18/h/p18cxxx.h"
#line 253 "C:/MCC18/h/p18cxxx.h"
#line 255 "C:/MCC18/h/p18cxxx.h"
#line 257 "C:/MCC18/h/p18cxxx.h"
#line 259 "C:/MCC18/h/p18cxxx.h"
#line 261 "C:/MCC18/h/p18cxxx.h"
#line 1 "C:/MCC18/h/p18f67j10.h"

#line 5 "C:/MCC18/h/p18f67j10.h"
 


#line 1671 "C:/MCC18/h/p18f67j10.h"

#line 1677 "C:/MCC18/h/p18f67j10.h"

#line 1692 "C:/MCC18/h/p18f67j10.h"
#line 1697 "C:/MCC18/h/p18f67j10.h"
#line 261 "C:/MCC18/h/p18cxxx.h"

#line 263 "C:/MCC18/h/p18cxxx.h"
#line 265 "C:/MCC18/h/p18cxxx.h"
#line 267 "C:/MCC18/h/p18cxxx.h"
#line 269 "C:/MCC18/h/p18cxxx.h"
#line 271 "C:/MCC18/h/p18cxxx.h"
#line 273 "C:/MCC18/h/p18cxxx.h"
#line 275 "C:/MCC18/h/p18cxxx.h"
#line 277 "C:/MCC18/h/p18cxxx.h"
#line 279 "C:/MCC18/h/p18cxxx.h"
#line 281 "C:/MCC18/h/p18cxxx.h"
#line 283 "C:/MCC18/h/p18cxxx.h"
#line 285 "C:/MCC18/h/p18cxxx.h"
#line 287 "C:/MCC18/h/p18cxxx.h"
#line 289 "C:/MCC18/h/p18cxxx.h"
#line 291 "C:/MCC18/h/p18cxxx.h"
#line 293 "C:/MCC18/h/p18cxxx.h"
#line 295 "C:/MCC18/h/p18cxxx.h"
#line 297 "C:/MCC18/h/p18cxxx.h"
#line 299 "C:/MCC18/h/p18cxxx.h"
#line 301 "C:/MCC18/h/p18cxxx.h"
#line 303 "C:/MCC18/h/p18cxxx.h"
#line 305 "C:/MCC18/h/p18cxxx.h"
#line 307 "C:/MCC18/h/p18cxxx.h"
#line 309 "C:/MCC18/h/p18cxxx.h"
#line 311 "C:/MCC18/h/p18cxxx.h"
#line 313 "C:/MCC18/h/p18cxxx.h"
#line 315 "C:/MCC18/h/p18cxxx.h"
#line 317 "C:/MCC18/h/p18cxxx.h"
#line 319 "C:/MCC18/h/p18cxxx.h"
#line 321 "C:/MCC18/h/p18cxxx.h"
#line 323 "C:/MCC18/h/p18cxxx.h"
#line 325 "C:/MCC18/h/p18cxxx.h"
#line 327 "C:/MCC18/h/p18cxxx.h"
#line 329 "C:/MCC18/h/p18cxxx.h"
#line 331 "C:/MCC18/h/p18cxxx.h"
#line 333 "C:/MCC18/h/p18cxxx.h"
#line 335 "C:/MCC18/h/p18cxxx.h"
#line 337 "C:/MCC18/h/p18cxxx.h"
#line 339 "C:/MCC18/h/p18cxxx.h"
#line 341 "C:/MCC18/h/p18cxxx.h"
#line 343 "C:/MCC18/h/p18cxxx.h"
#line 345 "C:/MCC18/h/p18cxxx.h"
#line 347 "C:/MCC18/h/p18cxxx.h"
#line 349 "C:/MCC18/h/p18cxxx.h"
#line 351 "C:/MCC18/h/p18cxxx.h"
#line 353 "C:/MCC18/h/p18cxxx.h"
#line 355 "C:/MCC18/h/p18cxxx.h"
#line 357 "C:/MCC18/h/p18cxxx.h"
#line 359 "C:/MCC18/h/p18cxxx.h"
#line 361 "C:/MCC18/h/p18cxxx.h"

#line 363 "C:/MCC18/h/p18cxxx.h"
#line 16 "C:/MCC18/h/delays.h"


 
#line 20 "C:/MCC18/h/delays.h"

#line 22 "C:/MCC18/h/delays.h"

 
#line 25 "C:/MCC18/h/delays.h"


#line 31 "C:/MCC18/h/delays.h"
 
void Delay10TCYx(auto  unsigned char);


#line 38 "C:/MCC18/h/delays.h"
 
void Delay100TCYx(auto  unsigned char);


#line 45 "C:/MCC18/h/delays.h"
 
void Delay1KTCYx(auto  unsigned char);


#line 52 "C:/MCC18/h/delays.h"
 
void Delay10KTCYx(auto  unsigned char);

#line 56 "C:/MCC18/h/delays.h"
#line 36 "./DrvMdxP600.h"
















#line 53 "./DrvMdxP600.h"
#line 54 "./DrvMdxP600.h"
#line 55 "./DrvMdxP600.h"
#line 56 "./DrvMdxP600.h"
#line 57 "./DrvMdxP600.h"
#line 58 "./DrvMdxP600.h"

#line 60 "./DrvMdxP600.h"
#line 61 "./DrvMdxP600.h"
#line 62 "./DrvMdxP600.h"
#line 63 "./DrvMdxP600.h"
#line 64 "./DrvMdxP600.h"
#line 65 "./DrvMdxP600.h"
		

#line 68 "./DrvMdxP600.h"
#line 69 "./DrvMdxP600.h"
#line 70 "./DrvMdxP600.h"
#line 71 "./DrvMdxP600.h"
#line 72 "./DrvMdxP600.h"
#line 73 "./DrvMdxP600.h"
#line 74 "./DrvMdxP600.h"
#line 75 "./DrvMdxP600.h"
#line 76 "./DrvMdxP600.h"

#line 78 "./DrvMdxP600.h"
#line 79 "./DrvMdxP600.h"
#line 80 "./DrvMdxP600.h"
#line 81 "./DrvMdxP600.h"
#line 82 "./DrvMdxP600.h"
#line 83 "./DrvMdxP600.h"
#line 84 "./DrvMdxP600.h"
#line 85 "./DrvMdxP600.h"

#line 87 "./DrvMdxP600.h"


#line 90 "./DrvMdxP600.h"
#line 91 "./DrvMdxP600.h"
#line 92 "./DrvMdxP600.h"
#line 93 "./DrvMdxP600.h"
#line 94 "./DrvMdxP600.h"
#line 95 "./DrvMdxP600.h"
#line 96 "./DrvMdxP600.h"
#line 97 "./DrvMdxP600.h"
#line 98 "./DrvMdxP600.h"
#line 99 "./DrvMdxP600.h"

#line 101 "./DrvMdxP600.h"
#line 102 "./DrvMdxP600.h"
#line 103 "./DrvMdxP600.h"
#line 104 "./DrvMdxP600.h"
#line 105 "./DrvMdxP600.h"
#line 106 "./DrvMdxP600.h"
#line 107 "./DrvMdxP600.h"
#line 108 "./DrvMdxP600.h"


#line 111 "./DrvMdxP600.h"
#line 112 "./DrvMdxP600.h"
#line 113 "./DrvMdxP600.h"
#line 114 "./DrvMdxP600.h"
#line 115 "./DrvMdxP600.h"
#line 116 "./DrvMdxP600.h"
#line 117 "./DrvMdxP600.h"
#line 118 "./DrvMdxP600.h"
    
#line 120 "./DrvMdxP600.h"
#line 121 "./DrvMdxP600.h"
#line 122 "./DrvMdxP600.h"
#line 123 "./DrvMdxP600.h"
#line 124 "./DrvMdxP600.h"
#line 125 "./DrvMdxP600.h"
#line 126 "./DrvMdxP600.h"
#line 127 "./DrvMdxP600.h"


#line 130 "./DrvMdxP600.h"


#line 133 "./DrvMdxP600.h"
#line 134 "./DrvMdxP600.h"
#line 135 "./DrvMdxP600.h"
#line 136 "./DrvMdxP600.h"
#line 137 "./DrvMdxP600.h"
#line 138 "./DrvMdxP600.h"
#line 139 "./DrvMdxP600.h"
#line 140 "./DrvMdxP600.h"

#line 142 "./DrvMdxP600.h"
#line 143 "./DrvMdxP600.h"
#line 144 "./DrvMdxP600.h"
#line 145 "./DrvMdxP600.h"
#line 146 "./DrvMdxP600.h"
#line 147 "./DrvMdxP600.h"
#line 148 "./DrvMdxP600.h"
#line 149 "./DrvMdxP600.h"


#line 152 "./DrvMdxP600.h"
#line 153 "./DrvMdxP600.h"
#line 154 "./DrvMdxP600.h"
#line 155 "./DrvMdxP600.h"
#line 156 "./DrvMdxP600.h"
#line 157 "./DrvMdxP600.h"
#line 158 "./DrvMdxP600.h"

#line 160 "./DrvMdxP600.h"
#line 161 "./DrvMdxP600.h"
#line 162 "./DrvMdxP600.h"
#line 163 "./DrvMdxP600.h"
#line 164 "./DrvMdxP600.h"
#line 165 "./DrvMdxP600.h"
#line 166 "./DrvMdxP600.h"


#line 169 "./DrvMdxP600.h"
#line 170 "./DrvMdxP600.h"
#line 171 "./DrvMdxP600.h"
#line 172 "./DrvMdxP600.h"
#line 173 "./DrvMdxP600.h"

#line 175 "./DrvMdxP600.h"
#line 176 "./DrvMdxP600.h"
#line 177 "./DrvMdxP600.h"
#line 178 "./DrvMdxP600.h"
#line 179 "./DrvMdxP600.h"












#line 192 "./DrvMdxP600.h"
#line 193 "./DrvMdxP600.h"
#line 194 "./DrvMdxP600.h"
#line 195 "./DrvMdxP600.h"


#line 198 "./DrvMdxP600.h"
#line 199 "./DrvMdxP600.h"
#line 200 "./DrvMdxP600.h"
#line 201 "./DrvMdxP600.h"

#line 203 "./DrvMdxP600.h"







void DrvCBT300Init( void );









#line 221 "./DrvMdxP600.h"
#line 45 "DrvTimer_18F87J10.c"



#line 1 "./DrvInt_18F87J10.h"

#line 30 "./DrvInt_18F87J10.h"
 


#line 34 "./DrvInt_18F87J10.h"







#line 1 "./DrvPic18f67J10.h"

#line 5 "./DrvPic18f67J10.h"
 


#line 1701 "./DrvPic18f67J10.h"

#line 1707 "./DrvPic18f67J10.h"

#line 1722 "./DrvPic18f67J10.h"
#line 1727 "./DrvPic18f67J10.h"
#line 41 "./DrvInt_18F87J10.h"


#line 1 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"

#line 29 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
 

#line 94 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 98 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 102 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 162 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 43 "./DrvInt_18F87J10.h"

#line 1 "./DrvMdxP600.h"

#line 23 "./DrvMdxP600.h"
 

#line 221 "./DrvMdxP600.h"
#line 44 "./DrvInt_18F87J10.h"









typedef enum {
   INT_ID_TIMER0,
   INT_ID_TIMER1,
	INT_ID_TIMER2,
   INT_ID_USART_1_RX,
   INT_ID_USART_2_RX,
   INT_ID_RB,
   INT_ID_ALL
} _IntId, *_IntIdPtr;








#line 71 "./DrvInt_18F87J10.h"
#line 72 "./DrvInt_18F87J10.h"

#line 74 "./DrvInt_18F87J10.h"
#line 75 "./DrvInt_18F87J10.h"

#line 77 "./DrvInt_18F87J10.h"
#line 78 "./DrvInt_18F87J10.h"

#line 80 "./DrvInt_18F87J10.h"
#line 81 "./DrvInt_18F87J10.h"













void DrvIntInit( void );
void DrvIntEnable( _IntId Id, _Bool Enable );







#line 104 "./DrvInt_18F87J10.h"





#line 48 "DrvTimer_18F87J10.c"


#line 1 "./DrvKey.h"

#line 31 "./DrvKey.h"
 


#line 35 "./DrvKey.h"







#line 1 "./DrvPic18f67J10.h"

#line 5 "./DrvPic18f67J10.h"
 


#line 1701 "./DrvPic18f67J10.h"

#line 1707 "./DrvPic18f67J10.h"

#line 1722 "./DrvPic18f67J10.h"
#line 1727 "./DrvPic18f67J10.h"
#line 42 "./DrvKey.h"


#line 1 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"

#line 29 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
 

#line 94 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 98 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 102 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 162 "C:/CBT/CBT-300 bootloader/Application/MpLabC18.h"
#line 44 "./DrvKey.h"

#line 1 "./DrvMdxP600.h"

#line 23 "./DrvMdxP600.h"
 

#line 221 "./DrvMdxP600.h"
#line 45 "./DrvKey.h"









typedef struct {
   BITS  States:      5; 
   _Bool New:         1; 
   _Bool Repeat:      1; 
   BITS  NotUsed:     1;
} _Keys, *_KeysPtr;












#line 73 "./DrvKey.h"
#line 74 "./DrvKey.h"
#line 75 "./DrvKey.h"
#line 76 "./DrvKey.h"
#line 77 "./DrvKey.h"

#line 79 "./DrvKey.h"
#line 80 "./DrvKey.h"
   

#line 83 "./DrvKey.h"
#line 84 "./DrvKey.h"
#line 85 "./DrvKey.h"
#line 86 "./DrvKey.h"
#line 87 "./DrvKey.h"
   

#line 90 "./DrvKey.h"
#line 91 "./DrvKey.h"
   



   

#line 98 "./DrvKey.h"
#line 99 "./DrvKey.h"
#line 100 "./DrvKey.h"
#line 101 "./DrvKey.h"
#line 102 "./DrvKey.h"
#line 103 "./DrvKey.h"
#line 104 "./DrvKey.h"

#line 106 "./DrvKey.h"
#line 107 "./DrvKey.h"
#line 108 "./DrvKey.h"
#line 109 "./DrvKey.h"
#line 110 "./DrvKey.h"
#line 111 "./DrvKey.h"







#line 119 "./DrvKey.h"


#line 122 "./DrvKey.h"
#line 123 "./DrvKey.h"
#line 124 "./DrvKey.h"


#line 127 "./DrvKey.h"
#line 128 "./DrvKey.h"
#line 129 "./DrvKey.h"
#line 130 "./DrvKey.h"















#line 146 "./DrvKey.h"
#line 147 "./DrvKey.h"
#line 148 "./DrvKey.h"







void  DrvKeyInit(  UINT8 BeepLengthMs );
void  DrvKeyScan10msIsr( void );
_Keys DrvKeyState( void );
_Bool DrvKeyDown( BYTE Mask, _Bool New, _Bool Repeat );







#line 167 "./DrvKey.h"

#line 50 "DrvTimer_18F87J10.c"

#line 1 "./DrvPower.h"

#line 29 "./DrvPower.h"
 


#line 33 "./DrvPower.h"







#line 1 "./DrvPic18f67J10.h"

#line 5 "./DrvPic18f67J10.h"
 


#line 1701 "./DrvPic18f67J10.h"

#line 1707 "./DrvPic18f67J10.h"

#line 1722 "./DrvPic18f67J10.h"
#line 1727 "./DrvPic18f67J10.h"
#line 40 "./DrvPower.h"


#line 1 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"

#line 29 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
 

#line 94 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 98 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 102 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 162 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 42 "./DrvPower.h"

#line 1 "./DrvMdxP600.h"

#line 23 "./DrvMdxP600.h"
 

#line 221 "./DrvMdxP600.h"
#line 43 "./DrvPower.h"



















#line 63 "./DrvPower.h"


#line 66 "./DrvPower.h"


#line 69 "./DrvPower.h"
#line 70 "./DrvPower.h"













void DrvPowerInit( UINT8 AutoOffTimeSec );
void DrvPower1sIsr( void ); 
void DrvPowerOn( void ); 
void DrvPowerOff( void ); 







#line 95 "./DrvPower.h"
#line 51 "DrvTimer_18F87J10.c"



#line 1 "./DrvTimer_18F87J10.h"

#line 31 "./DrvTimer_18F87J10.h"
 


#line 35 "./DrvTimer_18F87J10.h"







#line 1 "./DrvPic18f67J10.h"

#line 5 "./DrvPic18f67J10.h"
 


#line 1701 "./DrvPic18f67J10.h"

#line 1707 "./DrvPic18f67J10.h"

#line 1722 "./DrvPic18f67J10.h"
#line 1727 "./DrvPic18f67J10.h"
#line 42 "./DrvTimer_18F87J10.h"


#line 1 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"

#line 29 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
 

#line 94 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 98 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 102 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 162 "C:/CBT/CBT-300 bootloader/Application/MplabC18.h"
#line 44 "./DrvTimer_18F87J10.h"

#line 1 "./DrvMdxP600.h"

#line 23 "./DrvMdxP600.h"
 

#line 221 "./DrvMdxP600.h"
#line 45 "./DrvTimer_18F87J10.h"








typedef enum {
   TIMER0_SEC_COUNTER_1 = 0,
   TIMER0_SEC_COUNTER_2 = 1,
   TIMER0_MS_COUNTER_1  = 2,
   TIMER0_MS_COUNTER_2  = 3
} _Timer0CounterId, *_Timer0CounterIdPtr;












#line 72 "./DrvTimer_18F87J10.h"
#line 73 "./DrvTimer_18F87J10.h"

#line 75 "./DrvTimer_18F87J10.h"
#line 76 "./DrvTimer_18F87J10.h"

#line 78 "./DrvTimer_18F87J10.h"
#line 79 "./DrvTimer_18F87J10.h"

#line 81 "./DrvTimer_18F87J10.h"
#line 82 "./DrvTimer_18F87J10.h"

#line 84 "./DrvTimer_18F87J10.h"
#line 85 "./DrvTimer_18F87J10.h"
   
#line 87 "./DrvTimer_18F87J10.h"
#line 88 "./DrvTimer_18F87J10.h"
#line 89 "./DrvTimer_18F87J10.h"
#line 90 "./DrvTimer_18F87J10.h"
#line 91 "./DrvTimer_18F87J10.h"
#line 92 "./DrvTimer_18F87J10.h"
#line 93 "./DrvTimer_18F87J10.h"
#line 94 "./DrvTimer_18F87J10.h"











#line 106 "./DrvTimer_18F87J10.h"
#line 107 "./DrvTimer_18F87J10.h"
#line 108 "./DrvTimer_18F87J10.h"
#line 109 "./DrvTimer_18F87J10.h"
#line 110 "./DrvTimer_18F87J10.h"
#line 111 "./DrvTimer_18F87J10.h"


#line 114 "./DrvTimer_18F87J10.h"
#line 115 "./DrvTimer_18F87J10.h"
#line 116 "./DrvTimer_18F87J10.h"
#line 117 "./DrvTimer_18F87J10.h"
#line 118 "./DrvTimer_18F87J10.h"











#line 130 "./DrvTimer_18F87J10.h"
#line 131 "./DrvTimer_18F87J10.h"

#line 133 "./DrvTimer_18F87J10.h"
#line 134 "./DrvTimer_18F87J10.h"

#line 136 "./DrvTimer_18F87J10.h"
#line 137 "./DrvTimer_18F87J10.h"

#line 139 "./DrvTimer_18F87J10.h"
#line 140 "./DrvTimer_18F87J10.h"

#line 142 "./DrvTimer_18F87J10.h"
#line 143 "./DrvTimer_18F87J10.h"
#line 144 "./DrvTimer_18F87J10.h"
#line 145 "./DrvTimer_18F87J10.h"

#line 147 "./DrvTimer_18F87J10.h"
#line 148 "./DrvTimer_18F87J10.h"

#line 150 "./DrvTimer_18F87J10.h"
#line 151 "./DrvTimer_18F87J10.h"




















#line 172 "./DrvTimer_18F87J10.h"

#line 174 "./DrvTimer_18F87J10.h"
#line 175 "./DrvTimer_18F87J10.h"
#line 176 "./DrvTimer_18F87J10.h"
#line 177 "./DrvTimer_18F87J10.h"

#line 179 "./DrvTimer_18F87J10.h"
#line 180 "./DrvTimer_18F87J10.h"
#line 181 "./DrvTimer_18F87J10.h"
#line 182 "./DrvTimer_18F87J10.h"

#line 184 "./DrvTimer_18F87J10.h"
#line 185 "./DrvTimer_18F87J10.h"
#line 186 "./DrvTimer_18F87J10.h"
#line 187 "./DrvTimer_18F87J10.h"

#line 189 "./DrvTimer_18F87J10.h"
#line 190 "./DrvTimer_18F87J10.h"
#line 191 "./DrvTimer_18F87J10.h"
#line 192 "./DrvTimer_18F87J10.h"

#line 194 "./DrvTimer_18F87J10.h"






#line 201 "./DrvTimer_18F87J10.h"
#line 202 "./DrvTimer_18F87J10.h"

#line 204 "./DrvTimer_18F87J10.h"
#line 205 "./DrvTimer_18F87J10.h"
#line 206 "./DrvTimer_18F87J10.h"

#line 208 "./DrvTimer_18F87J10.h"
#line 209 "./DrvTimer_18F87J10.h"
#line 210 "./DrvTimer_18F87J10.h"
#line 211 "./DrvTimer_18F87J10.h"
#line 212 "./DrvTimer_18F87J10.h"
#line 213 "./DrvTimer_18F87J10.h"
#line 214 "./DrvTimer_18F87J10.h"
#line 215 "./DrvTimer_18F87J10.h"
#line 216 "./DrvTimer_18F87J10.h"
#line 217 "./DrvTimer_18F87J10.h"
#line 218 "./DrvTimer_18F87J10.h"
#line 219 "./DrvTimer_18F87J10.h"
#line 220 "./DrvTimer_18F87J10.h"
#line 221 "./DrvTimer_18F87J10.h"
#line 222 "./DrvTimer_18F87J10.h"
#line 223 "./DrvTimer_18F87J10.h"









#line 233 "./DrvTimer_18F87J10.h"







#line 241 "./DrvTimer_18F87J10.h"
#line 242 "./DrvTimer_18F87J10.h"







extern UINT8   Timer0SecCounter1;
extern UINT8   Timer0SecCounter2;
extern UINT16  Timer0MsCounter1;
extern UINT16  Timer0MsCounter2;

void  DrvTimer0Init( void );
void  DrvTimer0Isr( void );
void  DrvTimer0SetCounter( _Timer0CounterId Counter, UINT16 Value );
_Bool DrvTimer0CounterDone( _Timer0CounterId Counter );

void  DrvTimer1Init( void );
void  DrvTimer1Isr( void );


void  DrvTimer2Init( void );
void  DrvTimer2Isr( void );







#line 273 "./DrvTimer_18F87J10.h"





#line 54 "DrvTimer_18F87J10.c"














UINT8    Timer0IntCounter;

UINT8    Timer0SecCounter1;
UINT8    Timer0SecCounter2;

UINT16   Timer0MsCounter1;
UINT16   Timer0MsCounter2;

BYTE     Timer0CounterFlags;




























void DrvTimer0Init( void ) 
{
   
   T0CONbits.TMR0ON  = 0 ;             

   
   Timer0IntCounter     = 0;
   Timer0MsCounter1     = 0;
   Timer0MsCounter2     = 0;  
   Timer0SecCounter1    = 0;
   Timer0SecCounter2    = 0;  

   Timer0CounterFlags   = 0b00000000 ;
   
   
   T0CONbits.T08BIT  = 0 ;       
   T0CONbits.T0CS    = 0 ;     
   T0CONbits.PSA     = 0 ;       
   T0CONbits.T0PS    = 0b010 ;         

   
   TMR0H = (((0xFFFF  - 10000 )  >> 8) & 0xFF) ;
   TMR0L = ((0xFFFF  - 10000 )  & 0xFF) ;
   
   
   DrvIntEnable( INT_ID_TIMER0, BOOL_TRUE );

   
   T0CONbits.TMR0ON  = 1 ; 
}
















void DrvTimer0Isr( void )
{

   
   TMR0H = (((0xFFFF  - 10000 )  >> 8) & 0xFF) ;
   TMR0L = ((0xFFFF  - 10000 )  & 0xFF) ;

   
   if( Timer0MsCounter1 ) 
   {
      Timer0MsCounter1--;
   }
   else
   {
      Timer0CounterFlags |= 0b00000100 ;
   }

   if( Timer0MsCounter2 )
   {
      Timer0MsCounter2--;
   }
   else
   {
      Timer0CounterFlags |= 0b00001000 ;
   }

}

void DrvTimer0SetCounter( _Timer0CounterId Counter, UINT16 Value )
{
}

_Bool DrvTimer0CounterDone( _Timer0CounterId Counter )
{
   UINT16 Result;

   return( Result );
}




















void DrvTimer1Init( void ) 
{
   
   T1CONbits.TMR1ON  = 0 ;

   
   T1CONbits.TMR1CS  = 0  ;
   T1CONbits.T1OSCEN = 0 ;
   T1CONbits.T1CKPS  = 0b00 ;
   T1CONbits.RD16    = 1 ;

   
   T1CONbits.TMR1ON  = 0 ;
}

void DrvEnableTimer1( _Bool Mode )
{
   
   
}
















void DrvTimer2Init( void ) 
{
   
   T2CONbits.TMR2ON  = 0 ;             

   
   T2CONbits.T2CKPS  = 0b10 ;        
   T2CONbits.T2OUTPS = 0b0000 ;        
   PR2               = 100 ;              

   
   TMR2              = 0;
   
   
   T2CONbits.TMR2ON  = 1 ;              
}
















void DrvTimer2Isr( void )
{
}

