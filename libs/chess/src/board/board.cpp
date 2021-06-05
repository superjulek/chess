#include "board/board.h"

#include <exception>
#include <sstream>
#include <utility>

Board::Board() : current_player(Piece::PieceColor::White)
{

  const int first_rank = 0;
  const int last_rank = 7;
  const int second_rank = 1;
  const int penultimate_rank = 6;
  const int first_empty_rank = 2;
  const int last_empty_rank = 5;
  const int first_file = 0;

  /* Rank in chess notation goes for rows, files for vertical columns*/

  /* Set ranks of Figures */

  auto set_figures_rank = [&](size_t rank, Piece::PieceColor color)
  {
    fields.at(0).at(rank) = std::make_unique<Pieces::Rook>(Pieces::Rook(color));
    fields.at(chess_size - 1).at(rank) =
        std::make_unique<Pieces::Rook>(Pieces::Rook(color));
    fields.at(1).at(rank) =
        std::make_unique<Pieces::Knight>(Pieces::Knight(color));
    fields.at(chess_size - 2).at(rank) =
        std::make_unique<Pieces::Knight>(Pieces::Knight(color));
    fields.at(2).at(rank) =
        std::make_unique<Pieces::Bishop>(Pieces::Bishop(color));
    fields.at(chess_size - 3).at(rank) =
        std::make_unique<Pieces::Bishop>(Pieces::Bishop(color));
    fields.at(3).at(rank) =
        std::make_unique<Pieces::Queen>(Pieces::Queen(color));
    fields.at(4).at(rank) = std::make_unique<Pieces::King>(Pieces::King(color));
  };

  set_figures_rank(first_rank, Piece::PieceColor::White);
  set_figures_rank(last_rank, Piece::PieceColor::Black);

  /* Set rank of white Pawns */
  for (size_t file = first_file; file < chess_size; ++file)
  {
    fields.at(file).at(second_rank) =
        std::make_unique<Pieces::Pawn>(Pieces::Pawn(Piece::PieceColor::White));
  }

  /* Set ranks of empty fields */
  for (size_t rank = first_empty_rank; rank <= last_empty_rank; ++rank)
  {
    for (size_t file = first_file; file < chess_size; ++file)
    {
      fields.at(file).at(rank) =
          std::make_unique<Pieces::Empty>(Pieces::Empty());
    }
  }

  /* Set rank of black Pawns */
  for (size_t file = first_file; file < chess_size; ++file)
  {
    fields.at(file).at(penultimate_rank) =
        std::make_unique<Pieces::Pawn>(Pieces::Pawn(Piece::PieceColor::Black));
  }
}

Board::BoardLayout Board::get_layout()
{
  Board::BoardLayout ret_layout;
  for (size_t file = 0; file < chess_size; ++file)
  {
    for (size_t rank = 0; rank < chess_size; ++rank)
    {
      ret_layout.layout.at(file).at(rank) = {
          fields.at(file).at(rank)->get_piece_id(),
          fields.at(file).at(rank)->get_piece_color()};
    }
  }
  return ret_layout;
}

Board::Board(const Board &other) : current_player(other.current_player)
{
  for (size_t file = 0; file < chess_size; ++file)
  {
    for (size_t rank = 0; rank < chess_size; ++rank)
    {
      fields.at(file).at(rank) = other.fields.at(file).at(rank)->clone();
    }
  }
}

Board::Board(const std::string &notation)
{
  try
  {
    std::string buf;
    std::stringstream notation_ss(notation);

    std::getline(notation_ss, buf, ' ');
    current_player =
        buf.at(0) == 'w' ? Piece::PieceColor::White : Piece::PieceColor::Black;
    while (std::getline(notation_ss, buf, ' '))
    {
      char file = buf.at(0);
      char rank = buf.at(1);
      Piece::PieceColor piece_color = buf.at(2) == 'w'
                                          ? Piece::PieceColor::White
                                          : Piece::PieceColor::Black;
      ;
      Piece::PieceID piece_id = Piece::char_piece_map().at(buf.at(3));

      fields.at(Coordinates::file_map_rev.at(file))
          .at(Coordinates::rank_map_rev.at(rank)) =
          Pieces::get_piece_by_id(piece_id, piece_color);
    }
    for (size_t file = 0; file < chess_size; ++file)
    {
      for (size_t rank = 0; rank < chess_size; ++rank)
      {
        if (!fields.at(file).at(rank))
        {
          fields.at(file).at(rank) =
              std::make_unique<Pieces::Empty>(Pieces::Empty());
        }
      }
    }
  }
  catch (const std::exception &ex)
  {
    throw std::runtime_error(std::string("Parsing board notation failed: ") +
                             ex.what());
  }
}
bool Board::is_pat()
{
  /* Pat beacues lack of material
  On the board only 2 kings, or for each player 1 King 1 Knight/Bishop */
  size_t file = 0;
  size_t rank;
  int black = 0, white = 0;
  for (file = 0; file < chess_size; ++file)
  {
    for (rank = 0; rank < chess_size; ++rank)
    {
      if (fields.at(file).at(rank)->get_piece_id() == Piece::PieceID::Pawn ||
          fields.at(file).at(rank)->get_piece_id() == Piece::PieceID::Queen ||
          fields.at(file).at(rank)->get_piece_id() == Piece::PieceID::Rook)
      {
        return false;
      }
      else if (fields.at(file).at(rank)->get_piece_id() == Piece::PieceID::Knight ||
               fields.at(file).at(rank)->get_piece_id() == Piece::PieceID::Bishop)
      {
        if (fields.at(file).at(rank)->get_piece_color() == Piece::PieceColor::Black)
        {
          black += 1;
        }
        else
        {
          white += 1;
        }
      }
      if (white >= 2 && black >= 2)
      {
        return false;
      }
    }
  }
  return true;
}

bool Board::is_check(bool current)
{
  // Find king of current player
  size_t file;
  size_t rank;
  Piece::PieceColor tested_player = current ? current_player : !current_player;
  for (file = 0; file < chess_size; ++file)
  {
    for (rank = 0; rank < chess_size; ++rank)
    {
      if (fields.at(file).at(rank)->get_piece_id() == Piece::PieceID::King &&
          fields.at(file).at(rank)->get_piece_color() == tested_player)
      {
        goto found;
      }
    }
  }
  throw std::runtime_error("No King found when checking for check!");
found:
  // Check knights
  for (const auto &move : Pieces::Knight::knight_moves)
  {
    int file_checked = file + move.first;
    int rank_checked = rank + move.second;
    if (file_checked >= 0 && file_checked < static_cast<int>(chess_size) &&
        rank_checked >= 0 && rank_checked < static_cast<int>(chess_size))
    {
      Piece::PieceID piece_checked =
          fields.at(file_checked).at(rank_checked)->get_piece_id();
      Piece::PieceColor color_checked =
          fields.at(file_checked).at(rank_checked)->get_piece_color();
      if (piece_checked == Piece::PieceID::Knight &&
          color_checked != tested_player)
      {
        return true;
      }
    }
  }
  // Check pawns
  int next_rank = static_cast<int>(rank) +
                  ((tested_player == Piece::PieceColor::White) ? 1 : -1);
  if (next_rank >= 0 && next_rank < static_cast<int>(chess_size))
  {
    if (static_cast<int>(file) - 1 >= 0)
    {
      Piece::PieceID piece_checked =
          fields.at(file - 1).at(next_rank)->get_piece_id();
      Piece::PieceColor color_checked =
          fields.at(file - 1).at(next_rank)->get_piece_color();
      if (piece_checked == Piece::PieceID::Pawn &&
          color_checked != tested_player)
      {
        return true;
      }
    }
    if (static_cast<int>(file) + 1 < static_cast<int>(chess_size))
    {
      Piece::PieceID piece_checked =
          fields.at(file + 1).at(next_rank)->get_piece_id();
      Piece::PieceColor color_checked =
          fields.at(file + 1).at(next_rank)->get_piece_color();
      if (piece_checked == Piece::PieceID::Pawn &&
          color_checked != tested_player)
      {
        return true;
      }
    }
  }
  // Check lines for rooks, queen and bishops and king
  const std::array<int, 3> dirs = {-1, 0, 1};
  for (auto file_dir : dirs)
  {
    for (auto rank_dir : dirs)
    {
      if (file_dir == 0 && rank_dir == 0)
      {
        continue;
      }
      int file_checked = file + file_dir;
      int rank_checked = rank + rank_dir;
      bool first = true; // Nearest

      while (file_checked >= 0 && file_checked < static_cast<int>(chess_size) &&
             rank_checked >= 0 && rank_checked < static_cast<int>(chess_size))
      {
        Piece::PieceID piece_checked =
            fields.at(file_checked).at(rank_checked)->get_piece_id();
        Piece::PieceColor color_checked =
            fields.at(file_checked).at(rank_checked)->get_piece_color();
        if (piece_checked == Piece::PieceID::Empty)
        {
          file_checked += file_dir;
          rank_checked += rank_dir;
          first = false;
          continue;
        }
        if (color_checked == tested_player)
        {
          break;
        }
        if (piece_checked == Piece::PieceID::Queen)
        {
          return true;
        }
        if (piece_checked == Piece::PieceID::Rook && file_dir * rank_dir == 0)
        {
          return true;
        }
        if (piece_checked == Piece::PieceID::Bishop &&
            file_dir * rank_dir != 0)
        {
          return true;
        }
        if (piece_checked == Piece::PieceID::King && first)
        {
          return true;
        }
        // Other opponent's piece
        break;
      }
    }
  }
  return false;
}

bool Board::is_constrain_ok(const PossibleMove::Constrain &constrain) const
{
  Piece::PieceID piece_id = fields.at(constrain.coords.file)
                                .at(constrain.coords.rank)
                                ->get_piece_id();
  Piece::PieceColor piece_color = fields.at(constrain.coords.file)
                                      .at(constrain.coords.rank)
                                      ->get_piece_color();
  if (constrain.type == PossibleMove::Constrain::ConstrainType::Free)
  {
    return piece_id == Piece::PieceID::Empty;
  }
  if (constrain.type ==
      PossibleMove::Constrain::ConstrainType::TakenByOpponent)
  {
    return piece_id != Piece::PieceID::Empty && piece_color != current_player;
  }
  return false; // Unknown constrain
}

bool Board::is_move_possible(const Move &move)
{
  Piece::PieceID piece_id_from =
      fields.at(move.from.file).at(move.from.rank)->get_piece_id();
  Piece::PieceColor piece_color_from =
      fields.at(move.from.file).at(move.from.rank)->get_piece_color();
  Piece::PieceID piece_id_to =
      fields.at(move.to.file).at(move.to.rank)->get_piece_id();
  Piece::PieceColor piece_color_to =
      fields.at(move.to.file).at(move.to.rank)->get_piece_color();

  if (piece_id_from == Piece::PieceID::Empty)
  {
    return false;
  }
  if (piece_color_from != current_player)
  {
    return false;
  }
  if (piece_id_to != Piece::PieceID::Empty &&
      piece_color_to == current_player)
  {
    return false;
  }
  auto pos_moves = fields.at(move.from.file)
                       .at(move.from.rank)
                       ->get_possible_moves(move.from);
  for (const auto &pos_mov : pos_moves)
  {
    if (pos_mov.to == move.to)
    {
      for (const auto &constrain : pos_mov.constrains)
      {
        if (!is_constrain_ok(constrain))
        {
          return false;
        }
      }
      Board board_played = *this;
      board_played.apply_move({move.from, move.to});
      return !board_played.is_check(false);
    }
  }
  return false;
}

void Board::apply_move(const Move &move)
{
  try
  {
    fields.at(move.to.file).at(move.to.rank) =
        std::move(fields.at(move.from.file).at(move.from.rank));
    fields.at(move.from.file).at(move.from.rank) =
        std::make_unique<Pieces::Empty>(Pieces::Empty());
    current_player = !current_player;
  }
  catch (const std::exception &ex)
  {
    throw std::runtime_error(std::string("Failed when applying move: ") +
                             ex.what());
  }
}

void Board::apply_move(const StoredMove &move, bool forward)
{
  if (forward)
  {
    apply_move({move.from, move.to});
  }
  else
  {
    apply_move({move.to, move.from});
    if (move.piece_captured != Piece::PieceID::Empty)
    {
      fields.at(move.to.file).at(move.to.rank) =
          // Current player is already changed
          Pieces::get_piece_by_id(move.piece_captured, !current_player);
    }
  }
}

std::vector<PossibleMove> Board::get_possible_moves() const
{ // NOLINT

  std::vector<PossibleMove> possible_moves;
  for (size_t file = 0; file < chess_size; ++file)
  {
    for (size_t rank = 0; rank < chess_size; ++rank)
    {
      Piece::PieceID piece_id = fields.at(file).at(rank)->get_piece_id();
      Piece::PieceColor piece_color =
          fields.at(file).at(rank)->get_piece_color();
      if (piece_id == Piece::PieceID::Empty || piece_color != current_player)
      {
        continue;
      }
      std::vector<PossibleMove> current_possible_moves =
          fields.at(file).at(rank)->get_possible_moves(
              {static_cast<int>(file), static_cast<int>(rank)});
      for (auto move : current_possible_moves)
      {
        bool constrains_ok = true;
        Piece::PieceID piece_id_to =
            fields.at(move.to.file).at(move.to.rank)->get_piece_id();
        Piece::PieceColor piece_color_to =
            fields.at(move.to.file).at(move.to.rank)->get_piece_color();
        if (piece_id_to != Piece::PieceID::Empty &&
            piece_color_to == current_player)
        {
          continue;
        }

        for (const auto &constrain : move.constrains)
        {
          if (!is_constrain_ok(constrain))
          {
            constrains_ok = false;
            break;
          }
        }
        if (!constrains_ok)
        {
          continue;
        }
        Board board_played = *this;
        board_played.apply_move({move.from, move.to});
        if (!board_played.is_check(false))
        {
          possible_moves.push_back(move);
        }
      }
    }
  }
  return possible_moves;
}

bool Board::is_checkmate()
{
  return is_check(true) && get_possible_moves().empty();
}

bool operator==(const Board::BoardLayout &bl1, const Board::BoardLayout &bl2)
{
  for (size_t file = 0; file < chess_size; ++file)
  {
    for (size_t rank = 0; rank < chess_size; ++rank)
    {
      if (bl1.layout.at(file).at(rank).piece_id !=
              bl2.layout.at(file).at(rank).piece_id ||
          bl1.layout.at(file).at(rank).color !=
              bl2.layout.at(file).at(rank).color)
      {
        return false;
      }
    }
  }
  return true;
}


std::string move_to_str(Move mv)
{
  std::string ret;
  ret = Coordinates::file_map.at(mv.from.file);
  ret += Coordinates::rank_map.at(mv.from.rank);
  ret += Coordinates::file_map.at(mv.to.file);
  ret += Coordinates::rank_map.at(mv.to.rank);
  return ret;
}
Move move_from_string(std::string mv_string)
{
  Move ret_mv;
  ret_mv.from.file = Coordinates::file_map_rev.at(mv_string.at(0));
  ret_mv.from.rank = Coordinates::rank_map_rev.at(mv_string.at(1));
  ret_mv.to.file = Coordinates::file_map_rev.at(mv_string.at(2));
  ret_mv.to.rank = Coordinates::rank_map_rev.at(mv_string.at(3));
  return ret_mv;
}
