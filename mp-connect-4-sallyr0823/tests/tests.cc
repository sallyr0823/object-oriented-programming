// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
// #include <catch/catch.hpp>

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <cassert>
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[kBoardHeight][kBoardWidth],
              DiskType student[kBoardHeight][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Board Test Error", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);

  SECTION("require throw runtime_error") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 0),
                      std::runtime_error);
  }
  SECTION("require throw runtime_error") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, -1),
                      std::runtime_error);
  }
}

TEST_CASE("Out Of Bound Error", "[board_init]") {
  REQUIRE(BoardLocationInBounds(-1, 0) == false);
  REQUIRE(BoardLocationInBounds(0, -1) == false);
  REQUIRE(BoardLocationInBounds(0, 100) == false);
  REQUIRE(BoardLocationInBounds(100, 100) == false);
  REQUIRE(BoardLocationInBounds(100, 0) == false);
  REQUIRE(BoardLocationInBounds(0, 0) == true);
}

TEST_CASE("Check For Winner", "[board_init]") {
  Board student;
  InitBoard(student);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);
}

TEST_CASE("Search For Winner", "[board_init]") {
  Board student;
  InitBoard(student);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);

  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == true);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == false);

  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == true);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);

  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kRightDiag) == false);

  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);

  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == true);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == true);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);

  InitBoard(student);
  student.board[0][6] = DiskType::kPlayer1;
  student.board[1][5] = DiskType::kPlayer1;
  student.board[2][4] = DiskType::kPlayer1;
  student.board[3][3] = DiskType::kPlayer1;

  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == true);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == true);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);

  InitBoard(student);
  student.board[0][0] = DiskType::kPlayer1;
  student.board[1][1] = DiskType::kPlayer1;
  student.board[2][2] = DiskType::kPlayer1;
  student.board[3][3] = DiskType::kPlayer1;

  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == true);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == true);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);

  InitBoard(student);
  for (int i = 0; i < 3; i++) {
    student.board[i][0] = DiskType::kPlayer1;
    student.board[i][1] = DiskType::kPlayer1;
    student.board[i][2] = DiskType::kPlayer2;
    student.board[i][3] = DiskType::kPlayer1;
    student.board[i][4] = DiskType::kPlayer2;
    student.board[i][5] = DiskType::kPlayer2;
    student.board[i][6] = DiskType::kPlayer2;

    student.board[i + 3][0] = DiskType::kPlayer2;
    student.board[i + 3][1] = DiskType::kPlayer1;
    student.board[i + 3][2] = DiskType::kPlayer1;
    student.board[i + 3][3] = DiskType::kPlayer2;
    student.board[i + 3][4] = DiskType::kPlayer1;
    student.board[i + 3][5] = DiskType::kPlayer1;
    student.board[i + 3][6] = DiskType::kPlayer1;
  }
  student.board[2][1] = DiskType::kPlayer2;
  student.board[1][3] = DiskType::kPlayer2;
  student.board[1][5] = DiskType::kPlayer1;
  student.board[1][6] = DiskType::kPlayer1;
  student.board[4][5] = DiskType::kPlayer2;
  student.board[3][6] = DiskType::kPlayer2;

  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kVertical) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);
}
/////////////////////////////////////////////////////////////////////////////////////////////