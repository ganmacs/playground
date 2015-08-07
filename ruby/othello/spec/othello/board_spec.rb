describe Othello::Board do
  let(:board) { described_class.new }

  describe '#put' do
    before do
      board.put(x: 4, y: 5, turn: Othello::WHITE)
    end

    it { expect(board.to_s).to eq Othello::WHITE }
  end
end
