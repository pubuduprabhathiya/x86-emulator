char *regs[] = { "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI" };

// struct operand decode_sib(){
//     unsigned char byte = get_next_byte();
//     int mod=byte>>6;
//     int rm=(byte & 0X38)>>3;
//     int reg=(byte & 0X07);
// }