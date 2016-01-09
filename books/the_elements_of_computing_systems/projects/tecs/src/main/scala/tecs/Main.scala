import tecs.asm.Assembler
import tecs.vm.VM

object Main {
  def main(args: Array[String]) {
    args(0) match {
      case "asm" => Assembler.main(args.drop(1))
      case "vm" => VM.main(args.drop(1))
    }
  }
}
