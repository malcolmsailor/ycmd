// Copyright (C) 2018 ycmd contributors
//
// This file is part of ycmd.
//
// ycmd is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ycmd is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ycmd.  If not, see <http://www.gnu.org/licenses/>.

#include "Character.h"
#include "CharacterRepository.h"
#include "TestUtils.h"
#include "Word.h"

#include <array>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::TestWithParam;
using ::testing::ValuesIn;

namespace YouCompleteMe {

class WordTest : public TestWithParam< WordTuple > {
protected:
  WordTest()
    : repo_( CharacterRepository::Instance() ) {
  }

  virtual void SetUp() {
    repo_.ClearCharacters();
    word_ = WordTuple( GetParam() );
  }

  CharacterRepository &repo_;
  WordTuple word_;
};


std::ostream& operator<<( std::ostream& os,
                          const CharacterSequence &characters ) {
  os << PrintToString( characters );
  return os;
}


TEST_P( WordTest, BreakIntoCharacters ) {
  std::vector< std::string > characters;
  for ( const auto &character : word_.characters_ ) {
    characters.push_back( character );
  }
  EXPECT_THAT( Word( word_.text_ ).Characters(),
               ContainsPointees( repo_.GetCharacters( characters ) ) );
}


// Tests generated from
// https://www.unicode.org/Public/UCD/latest/ucd/auxiliary/GraphemeBreakTest.txt
const WordTuple tests[] = {
  { "  ", { " ", " " } },
  { " ̈ ", { " ̈", " " } },
  { " \r", { " ", "\r" } },
  { " ̈\r", { " ̈", "\r" } },
  { " \n", { " ", "\n" } },
  { " ̈\n", { " ̈", "\n" } },
  { " ", { " ", "" } },
  { " ̈", { " ̈", "" } },
  { " ͏", { " ͏" } },
  { " ̈͏", { " ̈͏" } },
  { " 🇦", { " ", "🇦" } },
  { " ̈🇦", { " ̈", "🇦" } },
  { " ؀", { " ", "؀" } },
  { " ̈؀", { " ̈", "؀" } },
  { " ः", { " ः" } },
  { " ̈ः", { " ̈ः" } },
  { " ᄀ", { " ", "ᄀ" } },
  { " ̈ᄀ", { " ̈", "ᄀ" } },
  { " ᅠ", { " ", "ᅠ" } },
  { " ̈ᅠ", { " ̈", "ᅠ" } },
  { " ᆨ", { " ", "ᆨ" } },
  { " ̈ᆨ", { " ̈", "ᆨ" } },
  { " 가", { " ", "가" } },
  { " ̈가", { " ̈", "가" } },
  { " 각", { " ", "각" } },
  { " ̈각", { " ̈", "각" } },
  { " ⌚", { " ", "⌚" } },
  { " ̈⌚", { " ̈", "⌚" } },
  { " ̀", { " ̀" } },
  { " ̈̀", { " ̈̀" } },
  { " ‍", { " ‍" } },
  { " ̈‍", { " ̈‍" } },
  { " ͸", { " ", "͸" } },
  { " ̈͸", { " ̈", "͸" } },
  { "\r ", { "\r", " " } },
  { "\r̈ ", { "\r", "̈", " " } },
  { "\r\r", { "\r", "\r" } },
  { "\r̈\r", { "\r", "̈", "\r" } },
  { "\r\n", { "\r\n" } },
  { "\r̈\n", { "\r", "̈", "\n" } },
  { "\r", { "\r", "" } },
  { "\r̈", { "\r", "̈", "" } },
  { "\r͏", { "\r", "͏" } },
  { "\r̈͏", { "\r", "̈͏" } },
  { "\r🇦", { "\r", "🇦" } },
  { "\r̈🇦", { "\r", "̈", "🇦" } },
  { "\r؀", { "\r", "؀" } },
  { "\r̈؀", { "\r", "̈", "؀" } },
  { "\rः", { "\r", "ः" } },
  { "\r̈ः", { "\r", "̈ः" } },
  { "\rᄀ", { "\r", "ᄀ" } },
  { "\r̈ᄀ", { "\r", "̈", "ᄀ" } },
  { "\rᅠ", { "\r", "ᅠ" } },
  { "\r̈ᅠ", { "\r", "̈", "ᅠ" } },
  { "\rᆨ", { "\r", "ᆨ" } },
  { "\r̈ᆨ", { "\r", "̈", "ᆨ" } },
  { "\r가", { "\r", "가" } },
  { "\r̈가", { "\r", "̈", "가" } },
  { "\r각", { "\r", "각" } },
  { "\r̈각", { "\r", "̈", "각" } },
  { "\r⌚", { "\r", "⌚" } },
  { "\r̈⌚", { "\r", "̈", "⌚" } },
  { "\r̀", { "\r", "̀" } },
  { "\r̈̀", { "\r", "̈̀" } },
  { "\r‍", { "\r", "‍" } },
  { "\r̈‍", { "\r", "̈‍" } },
  { "\r͸", { "\r", "͸" } },
  { "\r̈͸", { "\r", "̈", "͸" } },
  { "\n ", { "\n", " " } },
  { "\n̈ ", { "\n", "̈", " " } },
  { "\n\r", { "\n", "\r" } },
  { "\n̈\r", { "\n", "̈", "\r" } },
  { "\n\n", { "\n", "\n" } },
  { "\n̈\n", { "\n", "̈", "\n" } },
  { "\n", { "\n", "" } },
  { "\n̈", { "\n", "̈", "" } },
  { "\n͏", { "\n", "͏" } },
  { "\n̈͏", { "\n", "̈͏" } },
  { "\n🇦", { "\n", "🇦" } },
  { "\n̈🇦", { "\n", "̈", "🇦" } },
  { "\n؀", { "\n", "؀" } },
  { "\n̈؀", { "\n", "̈", "؀" } },
  { "\nः", { "\n", "ः" } },
  { "\n̈ः", { "\n", "̈ः" } },
  { "\nᄀ", { "\n", "ᄀ" } },
  { "\n̈ᄀ", { "\n", "̈", "ᄀ" } },
  { "\nᅠ", { "\n", "ᅠ" } },
  { "\n̈ᅠ", { "\n", "̈", "ᅠ" } },
  { "\nᆨ", { "\n", "ᆨ" } },
  { "\n̈ᆨ", { "\n", "̈", "ᆨ" } },
  { "\n가", { "\n", "가" } },
  { "\n̈가", { "\n", "̈", "가" } },
  { "\n각", { "\n", "각" } },
  { "\n̈각", { "\n", "̈", "각" } },
  { "\n⌚", { "\n", "⌚" } },
  { "\n̈⌚", { "\n", "̈", "⌚" } },
  { "\ǹ", { "\n", "̀" } },
  { "\n̈̀", { "\n", "̈̀" } },
  { "\n‍", { "\n", "‍" } },
  { "\n̈‍", { "\n", "̈‍" } },
  { "\n͸", { "\n", "͸" } },
  { "\n̈͸", { "\n", "̈", "͸" } },
  { " ", { "", " " } },
  { "̈ ", { "", "̈", " " } },
  { "\r", { "", "\r" } },
  { "̈\r", { "", "̈", "\r" } },
  { "\n", { "", "\n" } },
  { "̈\n", { "", "̈", "\n" } },
  { "", { "", "" } },
  { "̈", { "", "̈", "" } },
  { "͏", { "", "͏" } },
  { "̈͏", { "", "̈͏" } },
  { "🇦", { "", "🇦" } },
  { "̈🇦", { "", "̈", "🇦" } },
  { "؀", { "", "؀" } },
  { "̈؀", { "", "̈", "؀" } },
  { "ः", { "", "ः" } },
  { "̈ः", { "", "̈ः" } },
  { "ᄀ", { "", "ᄀ" } },
  { "̈ᄀ", { "", "̈", "ᄀ" } },
  { "ᅠ", { "", "ᅠ" } },
  { "̈ᅠ", { "", "̈", "ᅠ" } },
  { "ᆨ", { "", "ᆨ" } },
  { "̈ᆨ", { "", "̈", "ᆨ" } },
  { "가", { "", "가" } },
  { "̈가", { "", "̈", "가" } },
  { "각", { "", "각" } },
  { "̈각", { "", "̈", "각" } },
  { "⌚", { "", "⌚" } },
  { "̈⌚", { "", "̈", "⌚" } },
  { "̀", { "", "̀" } },
  { "̈̀", { "", "̈̀" } },
  { "‍", { "", "‍" } },
  { "̈‍", { "", "̈‍" } },
  { "͸", { "", "͸" } },
  { "̈͸", { "", "̈", "͸" } },
  { "͏ ", { "͏", " " } },
  { "͏̈ ", { "͏̈", " " } },
  { "͏\r", { "͏", "\r" } },
  { "͏̈\r", { "͏̈", "\r" } },
  { "͏\n", { "͏", "\n" } },
  { "͏̈\n", { "͏̈", "\n" } },
  { "͏", { "͏", "" } },
  { "͏̈", { "͏̈", "" } },
  { "͏͏", { "͏͏" } },
  { "͏̈͏", { "͏̈͏" } },
  { "͏🇦", { "͏", "🇦" } },
  { "͏̈🇦", { "͏̈", "🇦" } },
  { "͏؀", { "͏", "؀" } },
  { "͏̈؀", { "͏̈", "؀" } },
  { "͏ः", { "͏ः" } },
  { "͏̈ः", { "͏̈ः" } },
  { "͏ᄀ", { "͏", "ᄀ" } },
  { "͏̈ᄀ", { "͏̈", "ᄀ" } },
  { "͏ᅠ", { "͏", "ᅠ" } },
  { "͏̈ᅠ", { "͏̈", "ᅠ" } },
  { "͏ᆨ", { "͏", "ᆨ" } },
  { "͏̈ᆨ", { "͏̈", "ᆨ" } },
  { "͏가", { "͏", "가" } },
  { "͏̈가", { "͏̈", "가" } },
  { "͏각", { "͏", "각" } },
  { "͏̈각", { "͏̈", "각" } },
  { "͏⌚", { "͏", "⌚" } },
  { "͏̈⌚", { "͏̈", "⌚" } },
  { "͏̀", { "͏̀" } },
  { "͏̈̀", { "͏̈̀" } },
  { "͏‍", { "͏‍" } },
  { "͏̈‍", { "͏̈‍" } },
  { "͏͸", { "͏", "͸" } },
  { "͏̈͸", { "͏̈", "͸" } },
  { "🇦 ", { "🇦", " " } },
  { "🇦̈ ", { "🇦̈", " " } },
  { "🇦\r", { "🇦", "\r" } },
  { "🇦̈\r", { "🇦̈", "\r" } },
  { "🇦\n", { "🇦", "\n" } },
  { "🇦̈\n", { "🇦̈", "\n" } },
  { "🇦", { "🇦", "" } },
  { "🇦̈", { "🇦̈", "" } },
  { "🇦͏", { "🇦͏" } },
  { "🇦̈͏", { "🇦̈͏" } },
  { "🇦🇦", { "🇦🇦" } },
  { "🇦̈🇦", { "🇦̈", "🇦" } },
  { "🇦؀", { "🇦", "؀" } },
  { "🇦̈؀", { "🇦̈", "؀" } },
  { "🇦ः", { "🇦ः" } },
  { "🇦̈ः", { "🇦̈ः" } },
  { "🇦ᄀ", { "🇦", "ᄀ" } },
  { "🇦̈ᄀ", { "🇦̈", "ᄀ" } },
  { "🇦ᅠ", { "🇦", "ᅠ" } },
  { "🇦̈ᅠ", { "🇦̈", "ᅠ" } },
  { "🇦ᆨ", { "🇦", "ᆨ" } },
  { "🇦̈ᆨ", { "🇦̈", "ᆨ" } },
  { "🇦가", { "🇦", "가" } },
  { "🇦̈가", { "🇦̈", "가" } },
  { "🇦각", { "🇦", "각" } },
  { "🇦̈각", { "🇦̈", "각" } },
  { "🇦⌚", { "🇦", "⌚" } },
  { "🇦̈⌚", { "🇦̈", "⌚" } },
  { "🇦̀", { "🇦̀" } },
  { "🇦̈̀", { "🇦̈̀" } },
  { "🇦‍", { "🇦‍" } },
  { "🇦̈‍", { "🇦̈‍" } },
  { "🇦͸", { "🇦", "͸" } },
  { "🇦̈͸", { "🇦̈", "͸" } },
  { "؀ ", { "؀ " } },
  { "؀̈ ", { "؀̈", " " } },
  { "؀\r", { "؀", "\r" } },
  { "؀̈\r", { "؀̈", "\r" } },
  { "؀\n", { "؀", "\n" } },
  { "؀̈\n", { "؀̈", "\n" } },
  { "؀", { "؀", "" } },
  { "؀̈", { "؀̈", "" } },
  { "؀͏", { "؀͏" } },
  { "؀̈͏", { "؀̈͏" } },
  { "؀🇦", { "؀🇦" } },
  { "؀̈🇦", { "؀̈", "🇦" } },
  { "؀؀", { "؀؀" } },
  { "؀̈؀", { "؀̈", "؀" } },
  { "؀ः", { "؀ः" } },
  { "؀̈ः", { "؀̈ः" } },
  { "؀ᄀ", { "؀ᄀ" } },
  { "؀̈ᄀ", { "؀̈", "ᄀ" } },
  { "؀ᅠ", { "؀ᅠ" } },
  { "؀̈ᅠ", { "؀̈", "ᅠ" } },
  { "؀ᆨ", { "؀ᆨ" } },
  { "؀̈ᆨ", { "؀̈", "ᆨ" } },
  { "؀가", { "؀가" } },
  { "؀̈가", { "؀̈", "가" } },
  { "؀각", { "؀각" } },
  { "؀̈각", { "؀̈", "각" } },
  { "؀⌚", { "؀⌚" } },
  { "؀̈⌚", { "؀̈", "⌚" } },
  { "؀̀", { "؀̀" } },
  { "؀̈̀", { "؀̈̀" } },
  { "؀‍", { "؀‍" } },
  { "؀̈‍", { "؀̈‍" } },
  { "؀͸", { "؀͸" } },
  { "؀̈͸", { "؀̈", "͸" } },
  { "ः ", { "ः", " " } },
  { "ः̈ ", { "ः̈", " " } },
  { "ः\r", { "ः", "\r" } },
  { "ः̈\r", { "ः̈", "\r" } },
  { "ः\n", { "ः", "\n" } },
  { "ः̈\n", { "ः̈", "\n" } },
  { "ः", { "ः", "" } },
  { "ः̈", { "ः̈", "" } },
  { "ः͏", { "ः͏" } },
  { "ः̈͏", { "ः̈͏" } },
  { "ः🇦", { "ः", "🇦" } },
  { "ः̈🇦", { "ः̈", "🇦" } },
  { "ः؀", { "ः", "؀" } },
  { "ः̈؀", { "ः̈", "؀" } },
  { "ःः", { "ःः" } },
  { "ः̈ः", { "ः̈ः" } },
  { "ःᄀ", { "ः", "ᄀ" } },
  { "ः̈ᄀ", { "ः̈", "ᄀ" } },
  { "ःᅠ", { "ः", "ᅠ" } },
  { "ः̈ᅠ", { "ः̈", "ᅠ" } },
  { "ःᆨ", { "ः", "ᆨ" } },
  { "ः̈ᆨ", { "ः̈", "ᆨ" } },
  { "ः가", { "ः", "가" } },
  { "ः̈가", { "ः̈", "가" } },
  { "ः각", { "ः", "각" } },
  { "ः̈각", { "ः̈", "각" } },
  { "ः⌚", { "ः", "⌚" } },
  { "ः̈⌚", { "ः̈", "⌚" } },
  { "ः̀", { "ः̀" } },
  { "ः̈̀", { "ः̈̀" } },
  { "ः‍", { "ः‍" } },
  { "ः̈‍", { "ः̈‍" } },
  { "ः͸", { "ः", "͸" } },
  { "ः̈͸", { "ः̈", "͸" } },
  { "ᄀ ", { "ᄀ", " " } },
  { "ᄀ̈ ", { "ᄀ̈", " " } },
  { "ᄀ\r", { "ᄀ", "\r" } },
  { "ᄀ̈\r", { "ᄀ̈", "\r" } },
  { "ᄀ\n", { "ᄀ", "\n" } },
  { "ᄀ̈\n", { "ᄀ̈", "\n" } },
  { "ᄀ", { "ᄀ", "" } },
  { "ᄀ̈", { "ᄀ̈", "" } },
  { "ᄀ͏", { "ᄀ͏" } },
  { "ᄀ̈͏", { "ᄀ̈͏" } },
  { "ᄀ🇦", { "ᄀ", "🇦" } },
  { "ᄀ̈🇦", { "ᄀ̈", "🇦" } },
  { "ᄀ؀", { "ᄀ", "؀" } },
  { "ᄀ̈؀", { "ᄀ̈", "؀" } },
  { "ᄀः", { "ᄀः" } },
  { "ᄀ̈ः", { "ᄀ̈ः" } },
  { "ᄀᄀ", { "ᄀᄀ" } },
  { "ᄀ̈ᄀ", { "ᄀ̈", "ᄀ" } },
  { "ᄀᅠ", { "ᄀᅠ" } },
  { "ᄀ̈ᅠ", { "ᄀ̈", "ᅠ" } },
  { "ᄀᆨ", { "ᄀ", "ᆨ" } },
  { "ᄀ̈ᆨ", { "ᄀ̈", "ᆨ" } },
  { "ᄀ가", { "ᄀ가" } },
  { "ᄀ̈가", { "ᄀ̈", "가" } },
  { "ᄀ각", { "ᄀ각" } },
  { "ᄀ̈각", { "ᄀ̈", "각" } },
  { "ᄀ⌚", { "ᄀ", "⌚" } },
  { "ᄀ̈⌚", { "ᄀ̈", "⌚" } },
  { "ᄀ̀", { "ᄀ̀" } },
  { "ᄀ̈̀", { "ᄀ̈̀" } },
  { "ᄀ‍", { "ᄀ‍" } },
  { "ᄀ̈‍", { "ᄀ̈‍" } },
  { "ᄀ͸", { "ᄀ", "͸" } },
  { "ᄀ̈͸", { "ᄀ̈", "͸" } },
  { "ᅠ ", { "ᅠ", " " } },
  { "ᅠ̈ ", { "ᅠ̈", " " } },
  { "ᅠ\r", { "ᅠ", "\r" } },
  { "ᅠ̈\r", { "ᅠ̈", "\r" } },
  { "ᅠ\n", { "ᅠ", "\n" } },
  { "ᅠ̈\n", { "ᅠ̈", "\n" } },
  { "ᅠ", { "ᅠ", "" } },
  { "ᅠ̈", { "ᅠ̈", "" } },
  { "ᅠ͏", { "ᅠ͏" } },
  { "ᅠ̈͏", { "ᅠ̈͏" } },
  { "ᅠ🇦", { "ᅠ", "🇦" } },
  { "ᅠ̈🇦", { "ᅠ̈", "🇦" } },
  { "ᅠ؀", { "ᅠ", "؀" } },
  { "ᅠ̈؀", { "ᅠ̈", "؀" } },
  { "ᅠः", { "ᅠः" } },
  { "ᅠ̈ः", { "ᅠ̈ः" } },
  { "ᅠᄀ", { "ᅠ", "ᄀ" } },
  { "ᅠ̈ᄀ", { "ᅠ̈", "ᄀ" } },
  { "ᅠᅠ", { "ᅠᅠ" } },
  { "ᅠ̈ᅠ", { "ᅠ̈", "ᅠ" } },
  { "ᅠᆨ", { "ᅠᆨ" } },
  { "ᅠ̈ᆨ", { "ᅠ̈", "ᆨ" } },
  { "ᅠ가", { "ᅠ", "가" } },
  { "ᅠ̈가", { "ᅠ̈", "가" } },
  { "ᅠ각", { "ᅠ", "각" } },
  { "ᅠ̈각", { "ᅠ̈", "각" } },
  { "ᅠ⌚", { "ᅠ", "⌚" } },
  { "ᅠ̈⌚", { "ᅠ̈", "⌚" } },
  { "ᅠ̀", { "ᅠ̀" } },
  { "ᅠ̈̀", { "ᅠ̈̀" } },
  { "ᅠ‍", { "ᅠ‍" } },
  { "ᅠ̈‍", { "ᅠ̈‍" } },
  { "ᅠ͸", { "ᅠ", "͸" } },
  { "ᅠ̈͸", { "ᅠ̈", "͸" } },
  { "ᆨ ", { "ᆨ", " " } },
  { "ᆨ̈ ", { "ᆨ̈", " " } },
  { "ᆨ\r", { "ᆨ", "\r" } },
  { "ᆨ̈\r", { "ᆨ̈", "\r" } },
  { "ᆨ\n", { "ᆨ", "\n" } },
  { "ᆨ̈\n", { "ᆨ̈", "\n" } },
  { "ᆨ", { "ᆨ", "" } },
  { "ᆨ̈", { "ᆨ̈", "" } },
  { "ᆨ͏", { "ᆨ͏" } },
  { "ᆨ̈͏", { "ᆨ̈͏" } },
  { "ᆨ🇦", { "ᆨ", "🇦" } },
  { "ᆨ̈🇦", { "ᆨ̈", "🇦" } },
  { "ᆨ؀", { "ᆨ", "؀" } },
  { "ᆨ̈؀", { "ᆨ̈", "؀" } },
  { "ᆨः", { "ᆨः" } },
  { "ᆨ̈ः", { "ᆨ̈ः" } },
  { "ᆨᄀ", { "ᆨ", "ᄀ" } },
  { "ᆨ̈ᄀ", { "ᆨ̈", "ᄀ" } },
  { "ᆨᅠ", { "ᆨ", "ᅠ" } },
  { "ᆨ̈ᅠ", { "ᆨ̈", "ᅠ" } },
  { "ᆨᆨ", { "ᆨᆨ" } },
  { "ᆨ̈ᆨ", { "ᆨ̈", "ᆨ" } },
  { "ᆨ가", { "ᆨ", "가" } },
  { "ᆨ̈가", { "ᆨ̈", "가" } },
  { "ᆨ각", { "ᆨ", "각" } },
  { "ᆨ̈각", { "ᆨ̈", "각" } },
  { "ᆨ⌚", { "ᆨ", "⌚" } },
  { "ᆨ̈⌚", { "ᆨ̈", "⌚" } },
  { "ᆨ̀", { "ᆨ̀" } },
  { "ᆨ̈̀", { "ᆨ̈̀" } },
  { "ᆨ‍", { "ᆨ‍" } },
  { "ᆨ̈‍", { "ᆨ̈‍" } },
  { "ᆨ͸", { "ᆨ", "͸" } },
  { "ᆨ̈͸", { "ᆨ̈", "͸" } },
  { "가 ", { "가", " " } },
  { "가̈ ", { "가̈", " " } },
  { "가\r", { "가", "\r" } },
  { "가̈\r", { "가̈", "\r" } },
  { "가\n", { "가", "\n" } },
  { "가̈\n", { "가̈", "\n" } },
  { "가", { "가", "" } },
  { "가̈", { "가̈", "" } },
  { "가͏", { "가͏" } },
  { "가̈͏", { "가̈͏" } },
  { "가🇦", { "가", "🇦" } },
  { "가̈🇦", { "가̈", "🇦" } },
  { "가؀", { "가", "؀" } },
  { "가̈؀", { "가̈", "؀" } },
  { "가ः", { "가ः" } },
  { "가̈ः", { "가̈ः" } },
  { "가ᄀ", { "가", "ᄀ" } },
  { "가̈ᄀ", { "가̈", "ᄀ" } },
  { "가ᅠ", { "가ᅠ" } },
  { "가̈ᅠ", { "가̈", "ᅠ" } },
  { "각", { "각" } },
  { "가̈ᆨ", { "가̈", "ᆨ" } },
  { "가가", { "가", "가" } },
  { "가̈가", { "가̈", "가" } },
  { "가각", { "가", "각" } },
  { "가̈각", { "가̈", "각" } },
  { "가⌚", { "가", "⌚" } },
  { "가̈⌚", { "가̈", "⌚" } },
  { "가̀", { "가̀" } },
  { "가̈̀", { "가̈̀" } },
  { "가‍", { "가‍" } },
  { "가̈‍", { "가̈‍" } },
  { "가͸", { "가", "͸" } },
  { "가̈͸", { "가̈", "͸" } },
  { "각 ", { "각", " " } },
  { "각̈ ", { "각̈", " " } },
  { "각\r", { "각", "\r" } },
  { "각̈\r", { "각̈", "\r" } },
  { "각\n", { "각", "\n" } },
  { "각̈\n", { "각̈", "\n" } },
  { "각", { "각", "" } },
  { "각̈", { "각̈", "" } },
  { "각͏", { "각͏" } },
  { "각̈͏", { "각̈͏" } },
  { "각🇦", { "각", "🇦" } },
  { "각̈🇦", { "각̈", "🇦" } },
  { "각؀", { "각", "؀" } },
  { "각̈؀", { "각̈", "؀" } },
  { "각ः", { "각ः" } },
  { "각̈ः", { "각̈ः" } },
  { "각ᄀ", { "각", "ᄀ" } },
  { "각̈ᄀ", { "각̈", "ᄀ" } },
  { "각ᅠ", { "각", "ᅠ" } },
  { "각̈ᅠ", { "각̈", "ᅠ" } },
  { "각ᆨ", { "각ᆨ" } },
  { "각̈ᆨ", { "각̈", "ᆨ" } },
  { "각가", { "각", "가" } },
  { "각̈가", { "각̈", "가" } },
  { "각각", { "각", "각" } },
  { "각̈각", { "각̈", "각" } },
  { "각⌚", { "각", "⌚" } },
  { "각̈⌚", { "각̈", "⌚" } },
  { "각̀", { "각̀" } },
  { "각̈̀", { "각̈̀" } },
  { "각‍", { "각‍" } },
  { "각̈‍", { "각̈‍" } },
  { "각͸", { "각", "͸" } },
  { "각̈͸", { "각̈", "͸" } },
  { "⌚ ", { "⌚", " " } },
  { "⌚̈ ", { "⌚̈", " " } },
  { "⌚\r", { "⌚", "\r" } },
  { "⌚̈\r", { "⌚̈", "\r" } },
  { "⌚\n", { "⌚", "\n" } },
  { "⌚̈\n", { "⌚̈", "\n" } },
  { "⌚", { "⌚", "" } },
  { "⌚̈", { "⌚̈", "" } },
  { "⌚͏", { "⌚͏" } },
  { "⌚̈͏", { "⌚̈͏" } },
  { "⌚🇦", { "⌚", "🇦" } },
  { "⌚̈🇦", { "⌚̈", "🇦" } },
  { "⌚؀", { "⌚", "؀" } },
  { "⌚̈؀", { "⌚̈", "؀" } },
  { "⌚ः", { "⌚ः" } },
  { "⌚̈ः", { "⌚̈ः" } },
  { "⌚ᄀ", { "⌚", "ᄀ" } },
  { "⌚̈ᄀ", { "⌚̈", "ᄀ" } },
  { "⌚ᅠ", { "⌚", "ᅠ" } },
  { "⌚̈ᅠ", { "⌚̈", "ᅠ" } },
  { "⌚ᆨ", { "⌚", "ᆨ" } },
  { "⌚̈ᆨ", { "⌚̈", "ᆨ" } },
  { "⌚가", { "⌚", "가" } },
  { "⌚̈가", { "⌚̈", "가" } },
  { "⌚각", { "⌚", "각" } },
  { "⌚̈각", { "⌚̈", "각" } },
  { "⌚⌚", { "⌚", "⌚" } },
  { "⌚̈⌚", { "⌚̈", "⌚" } },
  { "⌚̀", { "⌚̀" } },
  { "⌚̈̀", { "⌚̈̀" } },
  { "⌚‍", { "⌚‍" } },
  { "⌚̈‍", { "⌚̈‍" } },
  { "⌚͸", { "⌚", "͸" } },
  { "⌚̈͸", { "⌚̈", "͸" } },
  { "̀ ", { "̀", " " } },
  { "̀̈ ", { "̀̈", " " } },
  { "̀\r", { "̀", "\r" } },
  { "̀̈\r", { "̀̈", "\r" } },
  { "̀\n", { "̀", "\n" } },
  { "̀̈\n", { "̀̈", "\n" } },
  { "̀", { "̀", "" } },
  { "̀̈", { "̀̈", "" } },
  { "̀͏", { "̀͏" } },
  { "̀̈͏", { "̀̈͏" } },
  { "̀🇦", { "̀", "🇦" } },
  { "̀̈🇦", { "̀̈", "🇦" } },
  { "̀؀", { "̀", "؀" } },
  { "̀̈؀", { "̀̈", "؀" } },
  { "̀ः", { "̀ः" } },
  { "̀̈ः", { "̀̈ः" } },
  { "̀ᄀ", { "̀", "ᄀ" } },
  { "̀̈ᄀ", { "̀̈", "ᄀ" } },
  { "̀ᅠ", { "̀", "ᅠ" } },
  { "̀̈ᅠ", { "̀̈", "ᅠ" } },
  { "̀ᆨ", { "̀", "ᆨ" } },
  { "̀̈ᆨ", { "̀̈", "ᆨ" } },
  { "̀가", { "̀", "가" } },
  { "̀̈가", { "̀̈", "가" } },
  { "̀각", { "̀", "각" } },
  { "̀̈각", { "̀̈", "각" } },
  { "̀⌚", { "̀", "⌚" } },
  { "̀̈⌚", { "̀̈", "⌚" } },
  { "̀̀", { "̀̀" } },
  { "̀̈̀", { "̀̈̀" } },
  { "̀‍", { "̀‍" } },
  { "̀̈‍", { "̀̈‍" } },
  { "̀͸", { "̀", "͸" } },
  { "̀̈͸", { "̀̈", "͸" } },
  { "‍ ", { "‍", " " } },
  { "‍̈ ", { "‍̈", " " } },
  { "‍\r", { "‍", "\r" } },
  { "‍̈\r", { "‍̈", "\r" } },
  { "‍\n", { "‍", "\n" } },
  { "‍̈\n", { "‍̈", "\n" } },
  { "‍", { "‍", "" } },
  { "‍̈", { "‍̈", "" } },
  { "‍͏", { "‍͏" } },
  { "‍̈͏", { "‍̈͏" } },
  { "‍🇦", { "‍", "🇦" } },
  { "‍̈🇦", { "‍̈", "🇦" } },
  { "‍؀", { "‍", "؀" } },
  { "‍̈؀", { "‍̈", "؀" } },
  { "‍ः", { "‍ः" } },
  { "‍̈ः", { "‍̈ः" } },
  { "‍ᄀ", { "‍", "ᄀ" } },
  { "‍̈ᄀ", { "‍̈", "ᄀ" } },
  { "‍ᅠ", { "‍", "ᅠ" } },
  { "‍̈ᅠ", { "‍̈", "ᅠ" } },
  { "‍ᆨ", { "‍", "ᆨ" } },
  { "‍̈ᆨ", { "‍̈", "ᆨ" } },
  { "‍가", { "‍", "가" } },
  { "‍̈가", { "‍̈", "가" } },
  { "‍각", { "‍", "각" } },
  { "‍̈각", { "‍̈", "각" } },
  { "‍⌚", { "‍", "⌚" } },
  { "‍̈⌚", { "‍̈", "⌚" } },
  { "‍̀", { "‍̀" } },
  { "‍̈̀", { "‍̈̀" } },
  { "‍‍", { "‍‍" } },
  { "‍̈‍", { "‍̈‍" } },
  { "‍͸", { "‍", "͸" } },
  { "‍̈͸", { "‍̈", "͸" } },
  { "͸ ", { "͸", " " } },
  { "͸̈ ", { "͸̈", " " } },
  { "͸\r", { "͸", "\r" } },
  { "͸̈\r", { "͸̈", "\r" } },
  { "͸\n", { "͸", "\n" } },
  { "͸̈\n", { "͸̈", "\n" } },
  { "͸", { "͸", "" } },
  { "͸̈", { "͸̈", "" } },
  { "͸͏", { "͸͏" } },
  { "͸̈͏", { "͸̈͏" } },
  { "͸🇦", { "͸", "🇦" } },
  { "͸̈🇦", { "͸̈", "🇦" } },
  { "͸؀", { "͸", "؀" } },
  { "͸̈؀", { "͸̈", "؀" } },
  { "͸ः", { "͸ः" } },
  { "͸̈ः", { "͸̈ः" } },
  { "͸ᄀ", { "͸", "ᄀ" } },
  { "͸̈ᄀ", { "͸̈", "ᄀ" } },
  { "͸ᅠ", { "͸", "ᅠ" } },
  { "͸̈ᅠ", { "͸̈", "ᅠ" } },
  { "͸ᆨ", { "͸", "ᆨ" } },
  { "͸̈ᆨ", { "͸̈", "ᆨ" } },
  { "͸가", { "͸", "가" } },
  { "͸̈가", { "͸̈", "가" } },
  { "͸각", { "͸", "각" } },
  { "͸̈각", { "͸̈", "각" } },
  { "͸⌚", { "͸", "⌚" } },
  { "͸̈⌚", { "͸̈", "⌚" } },
  { "͸̀", { "͸̀" } },
  { "͸̈̀", { "͸̈̀" } },
  { "͸‍", { "͸‍" } },
  { "͸̈‍", { "͸̈‍" } },
  { "͸͸", { "͸", "͸" } },
  { "͸̈͸", { "͸̈", "͸" } },
  { "\r\na\n̈", { "\r\n", "a", "\n", "̈" } },
  { "ä", { "ä" } },
  { " ‍ن", { " ‍", "ن" } },
  { "ن‍ ", { "ن‍", " " } },
  { "ᄀᄀ", { "ᄀᄀ" } },
  { "각ᄀ", { "각", "ᄀ" } },
  { "각ᆨᄀ", { "각ᆨ", "ᄀ" } },
  { "🇦🇧🇨b", { "🇦🇧", "🇨", "b" } },
  { "a🇦🇧🇨b", { "a", "🇦🇧", "🇨", "b" } },
  { "a🇦🇧‍🇨b", { "a", "🇦🇧‍", "🇨", "b" } },
  { "a🇦‍🇧🇨b", { "a", "🇦‍", "🇧🇨", "b" } },
  { "a🇦🇧🇨🇩b", { "a", "🇦🇧", "🇨🇩", "b" } },
  { "a‍", { "a‍" } },
  { "äb", { "ä", "b" } },
  { "aःb", { "aः", "b" } },
  { "a؀b", { "a", "؀b" } },
  { "👶🏿👶", { "👶🏿", "👶" } },
  { "a🏿👶", { "a🏿", "👶" } },
  { "a🏿👶‍🛑", { "a🏿", "👶‍🛑" } },
  { "👶🏿̈‍👶🏿", { "👶🏿̈‍👶🏿" } },
  { "🛑‍🛑", { "🛑‍🛑" } },
  { "a‍🛑", { "a‍", "🛑" } },
  { "✁‍✁", { "✁‍✁" } },
  { "a‍✁", { "a‍", "✁" } },
};


INSTANTIATE_TEST_CASE_P( UnicodeTest, WordTest, ValuesIn( tests ) );


TEST( WordTest, MatchesBytes ) {
  Word word( "f𐍈oβaＡaR" );

  EXPECT_TRUE( word.ContainsBytes( Word( "f𐍈oβaＡar" ) ) );
  EXPECT_TRUE( word.ContainsBytes( Word( "F𐍈oβaａaR" ) ) );
  EXPECT_TRUE( word.ContainsBytes( Word( "foΒar"    ) ) );
  EXPECT_TRUE( word.ContainsBytes( Word( "RＡβof"    ) ) );
  EXPECT_TRUE( word.ContainsBytes( Word( "βfr𐍈ａ"    ) ) );
  EXPECT_TRUE( word.ContainsBytes( Word( "fβr"      ) ) );
  EXPECT_TRUE( word.ContainsBytes( Word( "r"        ) ) );
  EXPECT_TRUE( word.ContainsBytes( Word( "βββ"      ) ) );
  EXPECT_TRUE( word.ContainsBytes( Word( ""         ) ) );
}


TEST( WordTest, DoesntMatchBytes ) {
  Word word( "Fo𐍈βＡr" );

  EXPECT_FALSE( word.ContainsBytes( Word( "Fo𐍈βＡrε" ) ) );
  EXPECT_FALSE( word.ContainsBytes( Word( "gggg"    ) ) );
  EXPECT_FALSE( word.ContainsBytes( Word( "χ"       ) ) );
  EXPECT_FALSE( word.ContainsBytes( Word( "nfooΒａr" ) ) );
  EXPECT_FALSE( word.ContainsBytes( Word( "Fβrmmm"  ) ) );
}

} // namespace YouCompleteMe
