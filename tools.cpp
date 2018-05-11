#include "tools.h"
#include <stdio.h>
#include <string.h>

/*
 * u-law, A-law and linear PCM conversions.
 */
#define	SIGN_BIT	(0x80)		/* Sign bit for a A-law byte. */
#define	QUANT_MASK	(0xf)		/* Quantization field mask. */
#define	NSEGS		(8)		/* Number of A-law segments. */
#define	SEG_SHIFT	(4)		/* Left shift for segment number. */
#define	SEG_MASK	(0x70)		/* Segment field mask. */
#define	BIAS		(0x84)		/* Bias for linear code. */

static short seg_end[8] = { 0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0x7FFF };

static int search(int val, short *table, int size) {
    int i;

    for (i = 0; i < size; i++) {
        if (val <= *table++)
            return (i);
    }
    return (size);
}

static int ulaw2linear(unsigned char u_val) {
    int t;

    /* Complement to obtain normal u-law value. */
    u_val = ~u_val;

    /*
     * Extract and bias the quantization bits. Then
     * shift up by the segment number and subtract out the bias.
     */
    t = ((u_val & QUANT_MASK) << 3) + BIAS;
    t <<= ((unsigned) u_val & SEG_MASK) >> SEG_SHIFT;

    return ((u_val & SIGN_BIT) ? (BIAS - t) : (t - BIAS));
}

/*
 * linear2ulaw() - Convert a linear PCM value to u-law
 *
 */
static unsigned char linear2ulaw(int pcm_val) /* 2's complement (16-bit range) */
{
    int mask;
    int seg;
    unsigned char uval;

    /* Get the sign and the magnitude of the value. */
    if (pcm_val < 0) {
        pcm_val = BIAS - pcm_val;
        mask = 0x7F;
    } else {
        pcm_val += BIAS;
        mask = 0xFF;
    }

    /* Convert the scaled magnitude to segment number. */
    seg = search(pcm_val, seg_end, 8);

    /*
     * Combine the sign, segment, quantization bits;
     * and complement the code word.
     */
    if (seg >= 8) /* out of range, return maximum value. */
        return (0x7F ^ mask);
    else {
        uval = (seg << 4) | ((pcm_val >> (seg + 3)) & 0xF);
        return (uval ^ mask);
    }
}

Tools::Tools()
{

}

int Tools::g711u_decode(short amp[], const unsigned char g711u_data[], int g711u_bytes)
{
    int i;
    int samples;
    unsigned char code;
    int sl;

    for (samples = i = 0;;) {
        if (i >= g711u_bytes)
            break;
        code = g711u_data[i++];

        sl = ulaw2linear(code);

        amp[samples++] = (short) sl;
    }
    return samples * 2;
}

int Tools::g711u_encode(unsigned char g711_data[], const short amp[], int len)
{
    int i;

    for (i = 0; i < len; i++) {
        g711_data[i] = linear2ulaw(amp[i]);
    }
    return len;
}
QByteArray Tools::hexStringToArray(QString hex)
{
    QByteArray tmp=hex.toLatin1();
    QByteArray array;
    char *h=tmp.data();
    char *p=h;
    int v;

    while(p<h+tmp.length()){
        if(*p==' '){
            p++;
            continue;
        }
       // printf("%.2s",p);
        sscanf(p,"%02X", &v);
        array.append(v);
        p+=2;
    }
    return array;
}

QString Tools::arrayToHexString(QByteArray &array)
{
    QString hex;
    for(int i=0;i < array.length();i++){
       hex+= QString().sprintf("%02X ", (0xFF&array[i]));
    }
    return hex;
}

QString Tools::arrayToASCIIString(QByteArray &array)
{
    QString hex;
    for(int i=0;i < array.length();i++){
       if((0xFF&array[i])> 32 && (0xFF&array[i])<126)
         hex+= QString().sprintf("%c", (0xFF&array[i]));
       else
         hex+=" ";
    }
    return hex;
}
