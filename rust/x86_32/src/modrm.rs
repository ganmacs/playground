use emulator::Emulator;

// ModR/M
pub struct Modrm {
    // Mod
    mod_b: u8,

    // Register/ Opcode Field
    pub reg: u8,

    // R/M
    rm: u8,
}

impl Modrm {
    pub fn new(code: u8) -> Modrm {
        let v = Modrm {
            mod_b: (code & 0xC0) >> 6, // 0xC0 => 11000000
            reg: (code & 0x38) >> 3, // 0x38 => 00111000
            rm: (code & 0x07), // 0x07 => 00000111
        };
        v
    }

    pub fn get_rm32(&self, e: &mut Emulator) -> u32 {
        self.effective_address(e)
    }

    pub fn set_rm32(&self, e: &mut Emulator, v: u32) {
        if self.mod_b == 3 {
            // override effective_address
            e.set_register(self.rm as usize, v);
        } else {
            let addr = self.effective_address(e);
            e.set_memory32(addr as usize, v);
        }
    }

    fn effective_address(&self, e: &mut Emulator) -> u32 {
        match self.mod_b {
            0 => {
                match self.reg {
                    4 => unimplemented!(),
                    5 => e.read_imm32().unwrap(),
                    _ => e.get_register(self.reg as usize).unwrap(),
                }
            }
            1 => {
                match self.reg {
                    4 => unimplemented!(),
                    _ => {
                        let l = e.get_register(self.reg as usize).unwrap();
                        let r = e.read_imm32s(1).unwrap();
                        l.wrapping_add(r as u32)
                    }
                }
            }
            2 => {
                match self.reg {
                    4 => unimplemented!(),
                    _ => {
                        let l = e.get_register(self.reg as usize).unwrap();
                        let r = e.read_imm32s(1).unwrap();
                        l.wrapping_add(r as u32)
                    }
                }
            }
            3 => e.get_register(self.rm as usize).unwrap(),
            _ => unreachable!(),
        }
    }
}
