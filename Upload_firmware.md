# Upload Firmware
In order to upload the firmware, you need to put the board into upload mode.  
To do so, you juste have to press the **BOOTSET** button while powering the chip.

Once it's in upload mode, it exposes a mass storage through USB.  
To upload the new firmware, you have to paste it in **UF2 format** 

## UF2 Format
The UF2 file format consists of 512 bytes chunks.  
Each chunks have the following structure:  
```c
struct UF2_Block {
    // 32 byte header
    uint32_t magicStart0;
    uint32_t magicStart1;
    uint32_t flags;
    uint32_t targetAddr;
    uint32_t payloadSize;
    uint32_t blockNo;
    uint32_t numBlocks;
    uint32_t fileSize; // or familyID;
    uint8_t data[476];
    uint32_t magicEnd;
} UF2_Block;
```

A typical use case in raspberry firmware is to have the second stage booloader (256 bytes) in the first chunk and the rest in the following chunks 

## References
U2F Technical spec
- https://github.com/Microsoft/uf2  
- https://makecode.com/blog/one-chip-to-flash-them-all