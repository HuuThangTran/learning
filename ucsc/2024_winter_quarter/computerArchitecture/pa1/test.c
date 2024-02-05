
// b = 5 so 0
convert 0x0083b283 into binary:
0b0000_0000_1000_0011_1011_0010_1000_0011
00
Seperate the opcode and funct3 field:
00000000_1000_0011_1011_0010_1000_0011
opcode: 0000011 = 0x3
rd: 00101 
funct3: 011 = 0x3
from green card opcode = 0x3, funct3 = 0x3 is I-type ld
opcode: 0000011
rd: 00101
funct3: 011
rs1: 00111
immediate[11:0]: 00000001000
plus values into format
ld rd, immediate(rs1)
ld x5, 8(x7)


Conver 0xFFA18383 to binary
0b11111111101000011000001110000011
Seperate the opcode and funct3 field:
opcode:0000011 = 0x3
00111
funct3: 000 = 0x0
from green card opcode = 0x3, funct3 = 0x0 is I-type, so can parse rest
opcode:0000011 = 0x3
rd: 00111
funct3: 000 = 0x0
rs1: 00011
immediate[11:0]: 111111111010
plug values into format
lb rd, offset(rs1)
lb x7, -6(x3)

0xFFC2C193
0b1
Seperate the opcode and funct3 fied:
opcode: 0010011
00011
funct3: 100
from green card opcode = 0x13 , funct3 = 0x4 is I type xori
opcode: 0010011
rd: 00011
funct3: 100
rs1: 00101
immediate[11:0]: 11111111100
plug values into format
xori rd, rs1, imm
xori x3, x5, -4

rd: x3 = 00011
rs1: x4 = 00100
imm: 3 = 000000000011
we have rd, rs1, imme opcode and funct3 which is I type
=>
opcode: 0010011
funct3: 100 
encoded RV64I instruction in binary : 0b00000000001100100100000110010011
0x324193

(ii) lw x6, 11(x4)
lw rd, offset(rs1)
rd: x6 = 00110
imm: 11 = 000000010001
rs1: x4 = 00100
we have rd, rs1, imme opcode and funct3 which is i type
=> 
opcode: 0000011
funct3: 010
encoded RV64I instruction in binary: 00000001000100100010001100000011
0x1122303


z = 4a +16b - d;
    slli x5, x10, 2 //temp[x5] = 4a shift left by 2 equal to multiply by 4
    slli x6, x11, 4 //temp[x6] = 16b shift left by 4 equal to multiple by 16
    add  x5, x5, x6 // temp[x5] = temp[x5] + temp[x6]
    sub x10, x5, x12 // z = temp[x5] - d


result = result/4 -b[j] // assume base address of arraay b, of type doubleword, is in x10

srli x5, x11, 2     #
slli x6, x12, 3     #caculation of the byte offset
add x6, x5, x10     # Calculate the address of a[i]: temp = &a[i] (add the offset to the base address of the array)
ld x6, 0(x5)        # Load the doubleword value at the address into x5: temp = a[i]
sub x11, x5, x6 


B)


b/


