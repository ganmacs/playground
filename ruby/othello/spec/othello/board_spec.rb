describe Othello::Board do
  let(:board) { described_class.new }

  describe '#put' do
    before do
      board.set(4, 5, Othello::Stone.black)
    end

    it { expect(board.to_s).to eq Othello::WHITE }
  end
end
