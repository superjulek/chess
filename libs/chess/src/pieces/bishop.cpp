#include "pieces/bishop.h"

using namespace Pieces;

Bishop::Bishop(PieceColor color) : Piece(color, PieceID::Bishop) {}

std::vector<PossibleMove>
Bishop::get_possible_moves(const Coordinates &coords) {

  const std::array<std::pair<int, int>, 4> bishop_dirs = {
      std::make_pair(1, 1), std::make_pair(1, -1), std::make_pair(-1, 1),
      std::make_pair(-1, -1)};

  std::vector<PossibleMove> possible_moves;

  for (const auto &mv_dir : bishop_dirs) {
    int file_checked = coords.file + mv_dir.first;
    int rank_checked = coords.rank + mv_dir.second;

    std::vector<PossibleMove::Constrain> constrains;

    while (file_checked >= 0 && file_checked < static_cast<int>(chess_size) &&
           rank_checked >= 0 && rank_checked < static_cast<int>(chess_size)) {
      PossibleMove pos_mv;
      pos_mv.from = coords;
      pos_mv.to = {file_checked, rank_checked};
      pos_mv.constrains = constrains;
      possible_moves.push_back(pos_mv);
      constrains.push_back({PossibleMove::Constrain::ConstrainType::Free,
                            {file_checked, rank_checked}});
      file_checked += mv_dir.first;
      rank_checked += mv_dir.second;
    }
  }
  return possible_moves;
}

std::unique_ptr<Piece> Bishop::clone()
{
  return std::make_unique<Bishop> (*this);
}
