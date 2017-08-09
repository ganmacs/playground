use emulator::Emulator;

// ModR/M
pub struct Modrm {
    // Mod
    mod_b: u8,

    // Register/ Opcode Field
    pub reg: u8,

    // R/M
    rm: u8,

    disp8: Option<u8>,

    disp32: Option<u32>,
}

impl Modrm {
    pub fn new(code: u8, emu: &mut Emulator) -> Modrm {
        let mod_b = (code & 0xC0) >> 6; // 0xC0 => 11000000
        let reg = (code & 0x38) >> 3; // 0x38 => 00111000
        let rm = code & 0x07; // 0x07 => 00000111

        let disp8 = if mod_b == 1 && reg != 4 {
            Some(emu.read_imm8().unwrap())
        } else {
            None
        };

        let disp32 = if mod_b == 2 && reg != 4 {
            Some(emu.read_imm32().unwrap())
        } else {
            None
        };

        Modrm {
            mod_b: mod_b,
            reg: reg,
            rm: rm,
            disp8: disp8,
            disp32: disp32,
        }
    }

    pub fn get_rm32(&self, e: &mut Emulator) -> u32 {
        if self.mod_b == 3 {
            // override effective_address
            e.get_register(self.rm as usize).unwrap()
        } else {
            let addr = self.effective_address(e);
            e.get_memory32(addr as usize).unwrap()
        }
    }

    pub fn set_rm32(&self, e: &mut Emulator, v: u32) {
        if self.mod_b == 3 {
            // override effective_address
            e.set_register(self.rm as usize, v);
        } else {
            let addr = self.effective_address(e);
            let v = e.set_memory32(addr as usize, v);
            v
        }
    }

    pub fn get_r32(&self, e: &mut Emulator) -> u32 {
        e.get_register(self.reg as usize).unwrap()
    }

    pub fn set_r32(&self, e: &mut Emulator, v: u32) {
        e.set_register(self.reg as usize, v)
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
                        let l = e.get_register(self.rm as usize).unwrap();
                        let r = self.disp8.unwrap();
                        l.wrapping_add(r as u32)
                    }
                }
            }
            2 => {
                match self.reg {
                    4 => unimplemented!(),
                    _ => {
                        let l = e.get_register(self.rm as usize).unwrap();
                        let r = self.disp32.unwrap();
                        l.wrapping_add(r as u32)
                    }
                }
            }
            3 => e.get_register(self.rm as usize).unwrap(),
            _ => unreachable!(),
        }
    }
}
