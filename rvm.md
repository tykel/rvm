00  No-op                   nop             --
01  Move                    mov r, t        -- r = t                                                                -- START LOAD/STORE
02  Move                    mov r, xxxx     -- r = xxxx                                     
03  Move                    mov r, [llll]   -- r = [llll]                                      
04  Move (byte-indexed)     mbi r, [llll]   -- r = [llll + i * 1]                                      
05  Move (word-indexed)     mwi r, [llll]   -- r = [llll + i * 2]                                      
06  Move                    mov r, [t]      -- r = [t]                                      
07  Move (byte-indexed)     mbi r, [t]      -- r = [t + i * 1]                                      
08  Move (word-indexed)     mwi r, [t]      -- r = [t + i * 2]                                      
09  Move                    mov [llll], t   -- [llll] = t                                      
0a  Move (byte-indexed)     mbi [llll], t   -- [llll + i * 1] = t                                      
0b  Move (word-indexed)     mwi [llll], t   -- [llll + i * 2] = t                                                      -- END LOAD/STORE
0c  Move                    mov [r], t      -- [r] = t                                      
0d  Move (byte-indexed)     mbi [r], t      -- [r + i * 1] = t                                      
0e  Move (word-indexed)     mwi [r], t      -- [r + i * 2] = t                                                      -- END LOAD/STORE
0f  Increment               inc r       -- r = r + 1                                                            -- START ARITHMETIC
10  Increment-double        ind r       -- r = r + 2                                        
11  Decrement               dec r       -- r = r - 1                                        
12  Decrement-double        ded r       -- r = r - 2                                        
13  Bitwise NOT             not r       -- r = ~r                                       
14  Add                     add r, t    -- r = r + t                                        
15  Subtract                sub r, t    -- r = r - t                                        
16  Subtract, unstored      cmp r, t    -- _ = r - t                                            
17  Logical Shift Left      lsl r, t    -- r = r << t                                       
18  Logical Shift Right     lsr r, t    -- r = r >> t (exp. zeroes)                                     
19  Arithmetic Shift Right  asr r, t    -- r = r >> t (exp. bit 31)                                     
1a  Bitwise OR              bor r, t    -- r = r & t                                        
1b  Bitwise AND             and r, t    -- r = r | t                                        
1c  Bitwise AND, unstored   tst r, t    -- _ = r | t                                        
1d  Bitwise XOR             xor r, t    -- r = r ^ t                                        
1e  Mutliply                mul r, t    -- r = r * t                                        
1f  Divide                  div r, t    -- r = r / t                                                            -- END ARITHMETIC
20  Jump to Subroutine      jsr xxxx    -- s = s + 2; s = p; p = xxxx                                           -- START JUMP/BRANCHES
21  Jump to Subroutine      jsr r       -- s = s + 2; s = p; p = r                                      
22  Jump                    jmp xxxx    -- p = xxxx                                     
23  Jump                    jmp r       -- p = r                                        
24  Branch If Zero          biz r       -- if f.z { p = r }                                     
25  Branch If Zero          biz xxxx    -- if f.z { p = xxxx }                                      
26  Branch if Not Zero      bnz r       -- if !f.z { p = r }                                        
27  Branch if Not Zero      bnz xxxx    -- if !f.z { p = xxxx }                                     
28  Branch If Overflow      bio r       -- if f.o { p = r }                                     
29  Branch If Overflow      bio xxxx    -- if f.o { p = xxxx }                                      
2a  Branch if Not Overflow  bno r       -- if !f.o { p = r }                                        
2b  Branch if Not Overflow  bno xxxx    -- if !f.o { p = xxxx }                                     
2c  Branch If Carry         bic r       -- if f.c { p = r }                                     
2d  Branch If Carry         bic xxxx    -- if f.c { p = xxxx }                                      
2e  Branch if Not Carry     bnc r       -- if !f.c { p = r }                                        
2f  Branch if Not Carry     bnc xxxx    -- if !f.c { p = xxxx }                                     
30  Branch If Negative      bin r       -- if f.n { p = r }                                     
31  Branch If Negative      bin xxxx    -- if f.n { p = xxxx }                                      
32  Branch if Not Negative  bnn r       -- if !f.n { p = r }                                        
33  Branch if Not Negative  bnn xxxx    -- if !f.n { p = xxxx }                                     
34  Return from subroutine  ret         -- p = s; s = s - 2                                                     -- END JUMP/BRANCHES
35  Software Interrupt      swi         -- [ push p; push other registers; jump [iv entry] ]        
36  Return from Interrupt   rti         -- [ pop other registers; pop p ]                           
---------------------------------------------------------------------------------------------------------
 OOOO OO__                          no args
 OOOO OORR R___                     1-reg
 OOOO OORR RTTT                     2-reg
 OOOO OORR R0__ XXXX XXXX           reg and 8-bit immediate
 OOOO OORR R1__ XXXX XXXX XXXX XXXX reg and 16-bit immediate
 OOOO OORR R0__ LLLL LLLL           reg and 8-bit memory offset
 OOOO OORR R1__ LLLL LLLL LLLL LLLL reg and absolute adress
---------------------------------------------------------------------------------------------------------

clock speed:    256*256*60 = 3,932,160 Hz (1 cycle per pixel)
                a full frame lasts 256*256 = 65,536 cycles
                vertical blanking lasts (256-192)*256 = 16,384 cycles   (can write to screen)
                non-vblank lasts 192*256 = 49,152 cycles

registers:  a       Scratch
            b       Scratch
            c       Scratch
            d       Scratch
            i       Scratch; Index register
            p       Program Counter
            s       Stack Pointer
            f       Flags

memory:     Address space:  2^16 
                            = 65,536 bytes                      (65 KiB)    
            Max memory:     (8,196 + 256 * 8,196) * 3       
                            = 6,319,116 bytes w/ bank switching (~6 MiB)    ROM
                            8,196 * 2
                            = 16,384 bytes                      (16 KiB)    RAM
                            
            0000 - 1fff :   General ROM,    fixed
            2000 - 3fff :   General ROM,    bank-switched
            4000 - 5fff :   Video ROM,      fixed
            6000 - 7fff :   Video ROM       bank-switched
            8000 - 9fff :   Audio ROM       fixed
            a000 - bfff :   Audio ROM       bank-switched
            c000 - dfff :   General RAM 1,  fixed
            e000 - ffff :   General RAM 2,  fixed   (incl. MMIO ports)
            

interrupts: SWI     software interrupt              Triggered by SWI instruction
            VBI     hardware interrupt              Triggered by device
            HBI     hardware interrupt              Triggered by device
            IAI     illegal-access interrupt        Triggered when a read/write fails (e.g. access non-existing memory bank, write to ROM, etc.)
            TCI     timer-complete interrupt        Triggered when a timer reaches zero

video:      60Hz polling device             The screen is refreshed at 60 Hz, on a scanline basis
            64 hardware sprites             A sprite is a tile moved in hardware to a group's coordinate (+- offsets)
            64 hardware groups              A group is used for positioning more than one sprite to the same position
            Pixel- and tile-unit scrolling  Virtual screen area is larger than actual output resolution
            256 avail. colors, 16 on-screen Hardware palette contains 256 fixed entries, 16 can be used at a time
            256 x 192 screen resolution

audio:      DPCM playback                   Playback 1-bit DPCM samples, 128 levels
            registers: volume, ?loop, level Modify playback at runtime

timer:      cycle or usec timing
