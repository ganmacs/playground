use emulator::Emulator;
use errors::Error;
use register::*;
use modrm::Modrm;

pub fn jmp_rel32(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // op
    let n = emu.read_imm32s()?;

    emu.eip = emu.eip.wrapping_add(n as u32);
    Ok(())
}

pub fn js(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8s()?;
    if emu.is_set_sf() {
        emu.eip = emu.eip.wrapping_add(v as u32);
    }
    Ok(())
}

pub fn jle(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8s()?;

    if emu.is_set_zf() || (emu.is_set_sf() != emu.is_set_of()) {
        emu.eip = emu.eip.wrapping_add(v as u32);
    }
    Ok(())
}

pub fn cmp_r32_rm32(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8()?;
    let m = Modrm::new(v, emu);

    let r = m.get_r32(emu);
    let rm = m.get_rm32(emu);

    let v: i64 = (r as i64) - (rm as i64);
    emu.update_eflag_sub(r, rm, v as u64);
    Ok(())
}

pub fn add_rm32_r32(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8()?;
    let m = Modrm::new(v, emu);

    let rm = m.get_rm32(emu);
    let reg = m.get_r32(emu);

    m.set_rm32(emu, reg.wrapping_add(rm));
    Ok(())
}

pub fn opcode_83(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8()?;
    let m = Modrm::new(v, emu);

    match m.reg {
        0 => add_rm32_imm8(emu, m),
        5 => sub_rm32_imm8(emu, m),
        7 => cmp_rm32_imm8(emu, m),
        _ => unimplemented!(),
    }
}

pub fn cmp_rm32_imm8(emu: &mut Emulator, modrm: Modrm) -> Result<(), Error> {
    let rm = modrm.get_rm32(emu);
    let imm = emu.read_imm8s()?;
    let v: i64 = ((rm as i32) + (imm as i32)) as i64;
    emu.update_eflag_sub(rm, imm as u32, v as u64);
    Ok(())
}

pub fn add_rm32_imm8(emu: &mut Emulator, modrm: Modrm) -> Result<(), Error> {
    let rm = modrm.get_rm32(emu);
    let imm = emu.read_imm8s()? as u32;
    modrm.set_rm32(emu, rm.wrapping_add(imm as u32));
    Ok(())
}

pub fn sub_rm32_imm8(emu: &mut Emulator, modrm: Modrm) -> Result<(), Error> {
    let rm = modrm.get_rm32(emu);
    let imm = emu.read_imm8s()? as u32;
    modrm.set_rm32(emu, (rm - imm) as u32);
    Ok(())
}

pub fn mov_rm32_r32(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8()?;
    let m = Modrm::new(v, emu);

    let reg = m.get_r32(emu);

    m.set_rm32(emu, reg);
    Ok(())
}

pub fn mov_r32_rm32(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8()?;
    let m = Modrm::new(v, emu);

    let rm = m.get_rm32(emu);
    m.set_r32(emu, rm);
    Ok(())
}

pub fn mov_rm32_imm32(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8()?;
    let m = Modrm::new(v, emu);

    let imm = emu.read_imm32()?;
    m.set_rm32(emu, imm);
    Ok(())
}

pub fn code_ff(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8()?;
    let m = Modrm::new(v, emu);

    match m.reg {
        0 => inc_r32(emu, m)?,
        _ => unimplemented!(),
    }

    Ok(())
}

pub fn inc_r32(emu: &mut Emulator, modrm: Modrm) -> Result<(), Error> {
    let rm = modrm.get_rm32(emu);
    modrm.set_rm32(emu, rm.wrapping_add(1));
    Ok(())
}

pub fn push_r32(emu: &mut Emulator) -> Result<(), Error> {
    let reg = emu.read_imm8()? - 0x50;
    let v = emu.get_register(reg as usize)?;
    emu.push32(v);
    Ok(())
}

pub fn pop_r32(emu: &mut Emulator) -> Result<(), Error> {
    let reg = emu.read_imm8()? - 0x58;
    let v = emu.pop32();
    emu.set_register(reg as usize, v);
    Ok(())
}

pub fn push_i8(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8()?;
    let v = emu.read_imm8s()?;

    emu.push32(v as u32);
    Ok(())
}

pub fn call_rel32(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let addr = emu.read_imm32s()?;
    let v = emu.eip;
    emu.push32(v);

    emu.eip = emu.eip.wrapping_add(addr as u32);
    Ok(())
}

pub fn leave(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let esp_addr = emu.get_register(EBP)?;
    emu.set_register(ESP, esp_addr);

    let v = emu.pop32();
    emu.set_register(EBP, v);

    Ok(())
}

pub fn ret(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode
    emu.eip = emu.pop32();
    Ok(())
}

pub fn opcode_f7(emu: &mut Emulator) -> Result<(), Error> {
    let _ = emu.read_imm8(); // opcode

    let v = emu.read_imm8()?;
    let m = Modrm::new(v, emu);

    match m.reg {
        3 => neg(emu, m),
        _ => unimplemented!(),
    }
}

fn neg(emu: &mut Emulator, modrm: Modrm) -> Result<(), Error> {
    let v = modrm.get_rm32(emu) as i32 * -1;
    modrm.set_rm32(emu, v as u32);
    Ok(())
}
