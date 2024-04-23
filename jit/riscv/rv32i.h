/* R-Type instructions */

unsigned instruction_add(char rd, char rs1, char rs2);
unsigned instruction_sub(char rd, char rs1, char rs2);
unsigned instruction_xor(char rd, char rs1, char rs2);
unsigned instruction_or(char rd, char rs1, char rs2);
unsigned instruction_and(char rd, char rs1, char rs2);
unsigned instruction_sll(char rd, char rs1, char rs2);
unsigned instruction_srl(char rd, char rs1, char rs2);
unsigned instruction_sra(char rd, char rs1, char rs2);
unsigned instruction_slt(char rd, char rs1, char rs2);
unsigned instruction_sltu(char rd, char rs1, char rs2);

/* I-Type instructions */

unsigned instruction_addi(char rd, char rs1, int imm12);
unsigned instruction_xori(char rd, char rs1, int imm12);
unsigned instruction_ori(char rd, char rs1, int imm12);
unsigned instruction_andi(char rd, char rs1, int imm12);
unsigned instruction_slli(char rd, char rs1, int imm12);
unsigned instruction_srli(char rd, char rs1, int imm12);
unsigned instruction_srai(char rd, char rs1, int imm12);
unsigned instruction_slti(char rd, char rs1, int imm12);
unsigned instruction_sltiu(char rd, char rs1, int imm12);
unsigned instruction_lb(char rd, char rs1, int imm12);
unsigned instruction_lh(char rd, char rs1, int imm12);
unsigned instruction_lw(char rd, char rs1, int imm12);
unsigned instruction_lbu(char rd, char rs1, int imm12);
unsigned instruction_lhu(char rd, char rs1, int imm12);

/* S-Type instructions */
unsigned instruction_sb(char rd, char rs1, int imm12);
unsigned instruction_sh(char rd, char rs1, int imm12);
unsigned instruction_sw(char rd, char rs1, int imm12);

/* B-Type instructions */
unsigned instruction_beq(char rd, char rs1, int imm12);
unsigned instruction_bne(char rd, char rs1, int imm12);
unsigned instruction_blt(char rd, char rs1, int imm12);
unsigned instruction_bge(char rd, char rs1, int imm12);
unsigned instruction_bltu(char rd, char rs1, int imm12);
unsigned instruction_bgeu(char rd, char rs1, int imm12);

/* J-Type instructions */
unsigned instruction_jal(char rd, int imm20);

/* etc I-Type instructions */
unsigned instruction_jalr(char rd, char rs1, int imm12);
unsigned instruction_ecall(char rd, char rs1, int imm12);
unsigned instruction_ebreak(char rd, char rs1, int imm12);

/* U-Type instructions */
unsigned instruction_lui(char rd, int imm20);
unsigned instruction_auipc(char rd, int imm20);
