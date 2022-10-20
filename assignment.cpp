#include <iostream>
#include <memory>
#include <string>
#include <vector>

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


    // Destructor is virtual so that when a base-class pointer to a derived-class object is 
    // destroyed, the destructor of the derived class is called before this one
    virtual ~Piece() {}

    Color color;

    string color_string() const {
      if (color == Color::WHITE)
        return "W";
      else
        return "B";
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

  friend ostream &operator<<(ostream &stream, const ChessBoard &board) {
    stream << "\n" << "   a   b   c   d   e   f   g   h" << "\n";

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


  class King : public Piece {

    public:
      // Constructor
      King(Color color) : Piece(color) {}

      // Implement type
      string type() const {
        return color_string() + "Ki";
      }

      // X is a letter and y is a number
      // King can:
        // Move 1 step in x direction and zero steps in y direction
        // Move 1 step in y direction and zero steps in x dir// X is a letter and y is a number
      // King can:
        // Move 1 step in x direction and zero steps in y direction
        // Move 1 step in y direction and zero steps in x directionection
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
              if (0 < to_x < 9) { 
                return true;
              }
          }
        }
        return false;
      }
  };

  class Knight : public Piece {
    
    public:
      // Constructor
      Knight(Color color) : Piece(color) {}

      // Implement type
      string type() const {
        return color_string() + "Kn";
      }

      // X is a letter and y is a number
      // Knight can:
        // Move 2 step in x direction and 1 step in y direction
        // Move 2 step in y direction and 1 step in x direction
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
      }
  };

  ChessBoard() {
    // Initialize the squares stored in 8 columns and 8 rows:
    squares.resize(8);
    for (auto &square_column : squares)
      square_column.resize(8);
  }

  /// 8x8 squares occupied by 1 or 0 chess pieces
  vector<vector<unique_ptr<Piece>>> squares;

  /// Move a chess piece if it is a valid move.
  /// Does not test for check or checkmate.
  bool move_piece(const std::string &from, const std::string &to) {
    int from_x = from[0] - 'a';
    int from_y = stoi(string() + from[1]) - 1;
    int to_x = to[0] - 'a';
    int to_y = stoi(string() + to[1]) - 1;

    auto &piece_from = squares[from_x][from_y];
    if (piece_from) {
      if (piece_from->valid_move(from_x, from_y, to_x, to_y)) {
        cout << piece_from->type() << " is moving from " << from << " to " << to << endl;
        auto &piece_to = squares[to_x][to_y];
        if (piece_to) {
          if (piece_from->color != piece_to->color) {
            cout << piece_to->type() << " is being removed from " << to << endl;
            if (auto king = dynamic_cast<King *>(piece_to.get()))
              cout << king->color_string() << " lost the game" << endl;
          } else {
            // piece in the from square has the same color as the piece in the to square
            cout << "can not move " << piece_from->type() << " from " << from << " to " << to << endl;
            return false;
          }
        }
        piece_to = move(piece_from);
        return true;
      } else {
        cout << "can not move " << piece_from->type() << " from " << from << " to " << to << endl;
        return false;
      }
    } else {
      cout << "no piece at " << from << endl;
      return false;
    }
  }
};

int main() {
  ChessBoard board;

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
  cout << board << endl;
  board.move_piece("g8", "h6");
  cout << board << endl;
  board.move_piece("b1", "c3");
  cout << board << endl;
  board.move_piece("h6", "g8");
  cout << board << endl;
  board.move_piece("c3", "d5");
  cout << board << endl;
  board.move_piece("g8", "h6");
  cout << board << endl;
  board.move_piece("d5", "f6");
  cout << board << endl;
  board.move_piece("h6", "g8");
  cout << board << endl;
  board.move_piece("f6", "e8");
  cout << board << endl;
}