use emulator::Emulator;
use errors::Error;
use modrm::Modrm;

pub fn opcode_83(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8()?;
    let m = Modrm::new(v);

    match m.reg {
        5 => sub_rm32_imm8(emu, &m),
        _ => unimplemented!(),
    }
}

pub fn sub_rm32_imm8(emu: &mut Emulator, modrm: &Modrm) -> Result<(), Error> {
    let rm = modrm.get_rm32(emu);
    let imm = emu.read_imm8s()? as u32;
    modrm.set_rm32(emu, (rm - imm) as u32);
    Ok(())
}
