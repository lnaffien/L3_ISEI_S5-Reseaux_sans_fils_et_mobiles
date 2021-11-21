#include "commun.h"

int calculateur_crc8(unsigned char data[], int taille)
{
    unsigned int crc8 = 0x00;
    unsigned char polynome = 0x05;

    for(int octet = 0; octet < taille; octet++)
    {
        crc8 = crc8 ^ data[octet];
        for(int bit = 0; bit < 8; bit++)
        {
            // S'il y a une retenue, decalage de 2 bits
            if( crc8 && 1)
            {
                crc8 = crc8 ^ polynome;
                crc8 >> 1;
            }
            crc8 >> 1;
        }      
    }
    return crc8;
}

int main()
{
    // Pour hello : 0x68, 0x65, 0x6C, 0x6C, 0x6F
    unsigned char data[2] = {0x68, 0x6C};
    unsigned char crc = calculateur_crc8(data, 2);
    printf("CRC = %d\n", crc);
    return 0;
}