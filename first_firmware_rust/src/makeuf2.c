
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "crcpico.h"
static unsigned int crc_pico[256]=
{
0x00000000, //crc table 0
0x04C11DB7, //crc table 1
0x09823B6E, //crc table 2
0x0D4326D9, //crc table 3
0x130476DC, //crc table 4
0x17C56B6B, //crc table 5
0x1A864DB2, //crc table 6
0x1E475005, //crc table 7
0x2608EDB8, //crc table 8
0x22C9F00F, //crc table 9
0x2F8AD6D6, //crc table 10
0x2B4BCB61, //crc table 11
0x350C9B64, //crc table 12
0x31CD86D3, //crc table 13
0x3C8EA00A, //crc table 14
0x384FBDBD, //crc table 15
0x4C11DB70, //crc table 16
0x48D0C6C7, //crc table 17
0x4593E01E, //crc table 18
0x4152FDA9, //crc table 19
0x5F15ADAC, //crc table 20
0x5BD4B01B, //crc table 21
0x569796C2, //crc table 22
0x52568B75, //crc table 23
0x6A1936C8, //crc table 24
0x6ED82B7F, //crc table 25
0x639B0DA6, //crc table 26
0x675A1011, //crc table 27
0x791D4014, //crc table 28
0x7DDC5DA3, //crc table 29
0x709F7B7A, //crc table 30
0x745E66CD, //crc table 31
0x9823B6E0, //crc table 32
0x9CE2AB57, //crc table 33
0x91A18D8E, //crc table 34
0x95609039, //crc table 35
0x8B27C03C, //crc table 36
0x8FE6DD8B, //crc table 37
0x82A5FB52, //crc table 38
0x8664E6E5, //crc table 39
0xBE2B5B58, //crc table 40
0xBAEA46EF, //crc table 41
0xB7A96036, //crc table 42
0xB3687D81, //crc table 43
0xAD2F2D84, //crc table 44
0xA9EE3033, //crc table 45
0xA4AD16EA, //crc table 46
0xA06C0B5D, //crc table 47
0xD4326D90, //crc table 48
0xD0F37027, //crc table 49
0xDDB056FE, //crc table 50
0xD9714B49, //crc table 51
0xC7361B4C, //crc table 52
0xC3F706FB, //crc table 53
0xCEB42022, //crc table 54
0xCA753D95, //crc table 55
0xF23A8028, //crc table 56
0xF6FB9D9F, //crc table 57
0xFBB8BB46, //crc table 58
0xFF79A6F1, //crc table 59
0xE13EF6F4, //crc table 60
0xE5FFEB43, //crc table 61
0xE8BCCD9A, //crc table 62
0xEC7DD02D, //crc table 63
0x34867077, //crc table 64
0x30476DC0, //crc table 65
0x3D044B19, //crc table 66
0x39C556AE, //crc table 67
0x278206AB, //crc table 68
0x23431B1C, //crc table 69
0x2E003DC5, //crc table 70
0x2AC12072, //crc table 71
0x128E9DCF, //crc table 72
0x164F8078, //crc table 73
0x1B0CA6A1, //crc table 74
0x1FCDBB16, //crc table 75
0x018AEB13, //crc table 76
0x054BF6A4, //crc table 77
0x0808D07D, //crc table 78
0x0CC9CDCA, //crc table 79
0x7897AB07, //crc table 80
0x7C56B6B0, //crc table 81
0x71159069, //crc table 82
0x75D48DDE, //crc table 83
0x6B93DDDB, //crc table 84
0x6F52C06C, //crc table 85
0x6211E6B5, //crc table 86
0x66D0FB02, //crc table 87
0x5E9F46BF, //crc table 88
0x5A5E5B08, //crc table 89
0x571D7DD1, //crc table 90
0x53DC6066, //crc table 91
0x4D9B3063, //crc table 92
0x495A2DD4, //crc table 93
0x44190B0D, //crc table 94
0x40D816BA, //crc table 95
0xACA5C697, //crc table 96
0xA864DB20, //crc table 97
0xA527FDF9, //crc table 98
0xA1E6E04E, //crc table 99
0xBFA1B04B, //crc table 100
0xBB60ADFC, //crc table 101
0xB6238B25, //crc table 102
0xB2E29692, //crc table 103
0x8AAD2B2F, //crc table 104
0x8E6C3698, //crc table 105
0x832F1041, //crc table 106
0x87EE0DF6, //crc table 107
0x99A95DF3, //crc table 108
0x9D684044, //crc table 109
0x902B669D, //crc table 110
0x94EA7B2A, //crc table 111
0xE0B41DE7, //crc table 112
0xE4750050, //crc table 113
0xE9362689, //crc table 114
0xEDF73B3E, //crc table 115
0xF3B06B3B, //crc table 116
0xF771768C, //crc table 117
0xFA325055, //crc table 118
0xFEF34DE2, //crc table 119
0xC6BCF05F, //crc table 120
0xC27DEDE8, //crc table 121
0xCF3ECB31, //crc table 122
0xCBFFD686, //crc table 123
0xD5B88683, //crc table 124
0xD1799B34, //crc table 125
0xDC3ABDED, //crc table 126
0xD8FBA05A, //crc table 127
0x690CE0EE, //crc table 128
0x6DCDFD59, //crc table 129
0x608EDB80, //crc table 130
0x644FC637, //crc table 131
0x7A089632, //crc table 132
0x7EC98B85, //crc table 133
0x738AAD5C, //crc table 134
0x774BB0EB, //crc table 135
0x4F040D56, //crc table 136
0x4BC510E1, //crc table 137
0x46863638, //crc table 138
0x42472B8F, //crc table 139
0x5C007B8A, //crc table 140
0x58C1663D, //crc table 141
0x558240E4, //crc table 142
0x51435D53, //crc table 143
0x251D3B9E, //crc table 144
0x21DC2629, //crc table 145
0x2C9F00F0, //crc table 146
0x285E1D47, //crc table 147
0x36194D42, //crc table 148
0x32D850F5, //crc table 149
0x3F9B762C, //crc table 150
0x3B5A6B9B, //crc table 151
0x0315D626, //crc table 152
0x07D4CB91, //crc table 153
0x0A97ED48, //crc table 154
0x0E56F0FF, //crc table 155
0x1011A0FA, //crc table 156
0x14D0BD4D, //crc table 157
0x19939B94, //crc table 158
0x1D528623, //crc table 159
0xF12F560E, //crc table 160
0xF5EE4BB9, //crc table 161
0xF8AD6D60, //crc table 162
0xFC6C70D7, //crc table 163
0xE22B20D2, //crc table 164
0xE6EA3D65, //crc table 165
0xEBA91BBC, //crc table 166
0xEF68060B, //crc table 167
0xD727BBB6, //crc table 168
0xD3E6A601, //crc table 169
0xDEA580D8, //crc table 170
0xDA649D6F, //crc table 171
0xC423CD6A, //crc table 172
0xC0E2D0DD, //crc table 173
0xCDA1F604, //crc table 174
0xC960EBB3, //crc table 175
0xBD3E8D7E, //crc table 176
0xB9FF90C9, //crc table 177
0xB4BCB610, //crc table 178
0xB07DABA7, //crc table 179
0xAE3AFBA2, //crc table 180
0xAAFBE615, //crc table 181
0xA7B8C0CC, //crc table 182
0xA379DD7B, //crc table 183
0x9B3660C6, //crc table 184
0x9FF77D71, //crc table 185
0x92B45BA8, //crc table 186
0x9675461F, //crc table 187
0x8832161A, //crc table 188
0x8CF30BAD, //crc table 189
0x81B02D74, //crc table 190
0x857130C3, //crc table 191
0x5D8A9099, //crc table 192
0x594B8D2E, //crc table 193
0x5408ABF7, //crc table 194
0x50C9B640, //crc table 195
0x4E8EE645, //crc table 196
0x4A4FFBF2, //crc table 197
0x470CDD2B, //crc table 198
0x43CDC09C, //crc table 199
0x7B827D21, //crc table 200
0x7F436096, //crc table 201
0x7200464F, //crc table 202
0x76C15BF8, //crc table 203
0x68860BFD, //crc table 204
0x6C47164A, //crc table 205
0x61043093, //crc table 206
0x65C52D24, //crc table 207
0x119B4BE9, //crc table 208
0x155A565E, //crc table 209
0x18197087, //crc table 210
0x1CD86D30, //crc table 211
0x029F3D35, //crc table 212
0x065E2082, //crc table 213
0x0B1D065B, //crc table 214
0x0FDC1BEC, //crc table 215
0x3793A651, //crc table 216
0x3352BBE6, //crc table 217
0x3E119D3F, //crc table 218
0x3AD08088, //crc table 219
0x2497D08D, //crc table 220
0x2056CD3A, //crc table 221
0x2D15EBE3, //crc table 222
0x29D4F654, //crc table 223
0xC5A92679, //crc table 224
0xC1683BCE, //crc table 225
0xCC2B1D17, //crc table 226
0xC8EA00A0, //crc table 227
0xD6AD50A5, //crc table 228
0xD26C4D12, //crc table 229
0xDF2F6BCB, //crc table 230
0xDBEE767C, //crc table 231
0xE3A1CBC1, //crc table 232
0xE760D676, //crc table 233
0xEA23F0AF, //crc table 234
0xEEE2ED18, //crc table 235
0xF0A5BD1D, //crc table 236
0xF464A0AA, //crc table 237
0xF9278673, //crc table 238
0xFDE69BC4, //crc table 239
0x89B8FD09, //crc table 240
0x8D79E0BE, //crc table 241
0x803AC667, //crc table 242
0x84FBDBD0, //crc table 243
0x9ABC8BD5, //crc table 244
0x9E7D9662, //crc table 245
0x933EB0BB, //crc table 246
0x97FFAD0C, //crc table 247
0xAFB010B1, //crc table 248
0xAB710D06, //crc table 249
0xA6322BDF, //crc table 250
0xA2F33668, //crc table 251
0xBCB4666D, //crc table 252
0xB8757BDA, //crc table 253
0xB5365D03, //crc table 254
0xB1F740B4  //crc table 255
};

#define DSIZE 0x10000
unsigned int wdata[128];
unsigned char data[DSIZE<<1];

FILE *fp;

int main ( int argc, char *argv[] )
{
    unsigned int len;
    unsigned int ra;
    unsigned int rb;
    unsigned int crc;
    unsigned int blocks;
    unsigned int nblock;
    unsigned int add;
    unsigned int doff;

    if(argc<3)
    {
        printf("input and output files not specified\n");
        return(1);
    }
    fp=fopen(argv[1],"rb");
    if(fp==NULL)
    {
        printf("Error opening file [%s]\n",argv[1]);
        return(1);
    }
    memset(data,0x00,sizeof(data));
    len=fread(data,1,sizeof(data),fp);
    fclose(fp);
    printf("%u bytes read (0x%X)\n",len,len);
    if(len>DSIZE)
    {
        printf("too big\n");
        return(1);
    }
    if(len<512)
    {
        printf("too small\n");
        return(1);
    }
    blocks=(len+0xFF)>>8;
    printf("blocks 0x%X (0x%X)\n",blocks,len);

    crc=0xFFFFFFFF;
    for(ra=0;ra<(256-4);ra++)
    {
        unsigned char tableoff;

        tableoff=(crc>>24)&0xFF;
        tableoff^=data[ra];
        crc<<=8;
        crc^=crc_pico[tableoff];
    }
    //printf("0x%08X\n",crc);
    data[ra++]=(crc>> 0)&0xFF;
    data[ra++]=(crc>> 8)&0xFF;
    data[ra++]=(crc>>16)&0xFF;
    data[ra++]=(crc>>24)&0xFF;
    //printf("0x%02X%02X%02X%02X\n",
        //data[255],
        //data[254],
        //data[253],
        //data[252]);

    fp=fopen(argv[2],"wb");
    if(fp==NULL)
    {
        printf("Error creating file [%s]\n",argv[2]);
        return(1);
    }

    add=0x10000000; //FLASH
    doff=0;
    for(nblock=0;nblock<blocks;nblock++)
    {
        memset(wdata,0x00,sizeof(wdata));
        wdata[0]=0x0A324655;
        wdata[1]=0x9E5D5157;
        wdata[2]=0x00002000;
        wdata[3]=add;
        wdata[4]=0x00000100;
        wdata[5]=nblock;
        wdata[6]=blocks;
        wdata[7]=0xE48BFF56;
        memcpy(&wdata[8],&data[doff],256);
        wdata[127]=0x0AB16F30;
        fwrite(wdata,1,sizeof(wdata),fp);
        add+=0x100;
        doff+=0x100;
    }

    fclose(fp);
    return(0);
}

//-------------------------------------------------------------------------
//
// Copyright (c) 2021 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------