#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <boost/asio.hpp>

using namespace std;

class ChessBoard {
public:
  enum class Color { WHITE,
                     BLACK };  

  class Piece {
  public:
    // Constructor 
    Piece(Color color) : color(color) {

    }

    virtual ~Piece() {}

    Color color;

    string color_string() const {
      if (color == Color::WHITE)
        return "white";
      else
        return "black";
    }

    // Return color and type of the chess piece
    virtual string type() const = 0;

    // Returns true if the given chess piece move is valid
    virtual bool valid_move(int from_x, int from_y, int to_x, int to_y) const = 0;
  };

  char to_letter(int n) const {
      if(n >= 1 && n <= 26) {
        return (char)('A' + n - 1);
      }
      return 0;
  }

  class King : public Piece {

    public: 
      // Constructor
      King(Color color) : Piece(color) {}

      // Implement type
      string type() const {
        if (color_string().find("black")) {
          return "BKI"; // black king
        }
        return "WKI"; // white king
      }

      bool valid_move(int from_x, int from_y, int to_x, int to_y) const {
        // Moving in y-direction
        if (from_x == to_x) {
          // Can only move 1 step in y-direction
          if(from_y - to_y == 1 || from_y - to_y == -1) {
              // Valid as long as it's not off the board
              if (0 < to_y < 9) {
                return true;
              }
          }
        }
        // Moving in x-direction
        else if (from_y == to_y) {
          // Can only move 1 step in x-direction
          if(from_x - to_x == 1 || from_x - to_x == -1) {
              // Valid as long as it's not off the board
              if (0 < to_x < 9) { // Could be that i am not able to test x this way due to lettering
                return true;
              }
          }
        }
        return false;
      };
  };

  class Knight : public Piece {
    
    public:
      // Constructor
      Knight(Color color) : Piece(color) {}

      // Implement type
      string type() const {
        if (color_string().find("black")) {
          return "BKN"; // black knight
        }
        return "WKN"; // white knight
      }
      
      bool valid_move(int from_x, int from_y, int to_x, int to_y) const {

        // Moving 2 steps in y-direction
        if (from_y - to_y == 2 || from_y - to_y == -2) {
          // Can only move 1 step in x-direction
          if(from_x - to_x == 1 || from_x - to_x == -1) {
            // Valid as long as it's not off the board
            if ((0 < to_y < 9) && (0 < to_x < 9)) {
              return true;
            }
          }
        }

        // Moving 2 steps in x-direction
        else if (from_x - to_x == 2 || from_x - to_x == -2) {
          // Can only move 1 step in y-direction
          if (from_y - to_y == 1 || from_y - to_y == -1) {
            // Valid as long as it's not off the board
            if ((0 < to_y < 9) && (0 < to_x < 9)) { // Could be that i am not able to test x this way due to lettering
              return true;
            }
          }
        }
        return false;
      };
  };

  ChessBoard() {
    // Initialize the squares stored in 8 columns and 8 rows:
    squares.resize(8);
    for (auto &square_column : squares)
      square_column.resize(8);
  }

  // Functions that will be expressed in constructor for ChessBoardPrint-class
  function<void(const ChessBoard &chessboard)> after_piece_move;
  function<void(const Piece &piece, const string &from, const string &to)> on_piece_move;
  function<void(const Piece &piece, const string &square)> on_piece_removed;
  function<void(Color color)> on_lost_game;
  function<void(const Piece &piece, const string &from, const string &to)> on_piece_move_invalid;
  function<void(const string &square)> on_piece_move_missing;

  /// 8x8 squares occupied by 1 or 0 chess pieces
  vector<vector<unique_ptr<Piece>>> squares;

  /// Move a chess piece if it is a valid move.
  /// Does not test for check or checkmate.
  bool move_piece(const std::string &from, const std::string &to) 
    {
    int from_x = from[0] - 'a';
    int from_y = stoi(string() + from[1]) - 1;
    int to_x = to[0] - 'a';
    int to_y = stoi(string() + to[1]) - 1;

    auto &piece_from = squares[from_x][from_y];
    if (piece_from) 
    {
      // If valid move
      if (piece_from->valid_move(from_x, from_y, to_x, to_y)) 
      {
        // If the piece is moving
        if (on_piece_move) 
          on_piece_move(*piece_from, from, to);

        auto &piece_to = squares[to_x][to_y];

        if (piece_to) 
        {
          if (piece_from->color != piece_to->color) 
          {
            if (on_piece_removed)
              on_piece_removed(*piece_to, to);

            if (auto king = dynamic_cast<King *>(piece_to.get()))
              on_lost_game(king->color);
          } 
          else 
          {
            if(on_piece_move_invalid)
              // piece in the from square has the same color as the piece in the to square
              on_piece_move_invalid(*piece_from, from, to);
            return false;
          }
        }
        piece_to = move(piece_from);
        if (after_piece_move)
          after_piece_move(*this);
        return true; 
      }
      else 
      {
        if(on_piece_move_invalid) {
          on_piece_move_invalid(*piece_from, from, to);
        return false;
        }
      }
    } else {
        if (on_piece_move_missing)
          on_piece_move_missing(from);
        return false;
    }
  }

  friend ostream &operator<<(ostream &stream, const ChessBoard &board) {
    stream << "  a b c d e f g h" << "\n";

    // Print out the row from top to bottom
    for (int row = 8; row > 0; row--)
    {
      stream << row << " ";
      for (int col = 0; col < 8; col++)
      {
        // piece will hold a nullpointer if not present in current square
        auto &piece = board.squares[col][row];

        if(piece) {
          stream << piece->type() << " ";
        }
        else {
          stream << "--- ";
        }

      }
      stream << "\n";
    }
    return stream;
  }
};



class ChessBoardPrint {

  public:
    ChessBoardPrint(ChessBoard &chessBoard_){

      // 'color' is the color of the losing team
      chessBoard_.on_lost_game = [](ChessBoard::Color color) {
        if (color == ChessBoard::Color::WHITE)
          cout << "Black";
        else
          cout << "White";
      cout << " won the game" << endl;

      };
      chessBoard_.on_piece_move = [](const ChessBoard::Piece &piece, const string &from, const string &to) {
        cout << piece.type() << " is moving from " << from << " to " << to << endl; 
      };
      chessBoard_.on_piece_move_invalid = [](const ChessBoard::Piece &piece, const string &from, const string &to) {
        cout << "can not move " << piece.type() << " from " << from << " to " << to << endl;
      };
      chessBoard_.on_piece_move_missing = [](const string &square) {
        cout << "no piece at " << square << endl;
      };
      chessBoard_.on_piece_removed = [](const ChessBoard::Piece &piece, const string &square) {
        cout << piece.type() << " is being removed from " << square << endl;
      };
      // Works because of to string method in chessboard class
      chessBoard_.after_piece_move = [](const ChessBoard &chessBoard) {
        cout << chessBoard << endl; 
      };
    };
};

int main() {
  ChessBoard board;
  ChessBoardPrint print(board);

  board.squares[4][0] = make_unique<ChessBoard::King>(ChessBoard::Color::WHITE);
  board.squares[1][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);
  board.squares[6][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);

  board.squares[4][7] = make_unique<ChessBoard::King>(ChessBoard::Color::BLACK);
  board.squares[1][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);
  board.squares[6][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);

  cout << "Invalid moves:" << endl;
  board.move_piece("e3", "e2");
  board.move_piece("e1", "e3");
  board.move_piece("b1", "b2");
  cout << endl;

  cout << "A simulated game:" << endl;
  board.move_piece("e1", "e2");
  board.move_piece("g8", "h6");
  board.move_piece("b1", "c3");
  board.move_piece("h6", "g8");
  board.move_piece("c3", "d5");
  board.move_piece("g8", "h6");
  board.move_piece("d5", "f6");
  board.move_piece("h6", "g8");
  board.move_piece("f6", "e8");

  return 0;
}