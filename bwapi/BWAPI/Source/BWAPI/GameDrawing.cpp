#include "GameImpl.h"

#include <cassert>
#include <Util/Clamp.h>
#include <Util/Convenience.h>

#include "../../../Debug.h"

namespace BWAPI
{
  //-------------------------------------------------- IN SCREEN ---------------------------------------------
  bool GameImpl::inScreen(CoordinateType::Enum ctype, int x, int y) const
  {
    if ( !data->hasGUI )
      return false;

    return false;
  }

  bool GameImpl::inScreen(CoordinateType::Enum ctype, int x1, int y1, int x2, int y2) const
  {
    if ( !data->hasGUI )
      return false;

    return false;
  }

  bool GameImpl::inScreen(CoordinateType::Enum ctype, int x1, int y1, int x2, int y2, int x3, int y3) const
  {
    if ( !data->hasGUI )
      return false;

    return false;
  }
  int GameImpl::addShape(const BWAPIC::Shape &s)
  {
    assert(data->shapeCount < GameData::MAX_SHAPES);
    data->shapes[data->shapeCount] = s;
    return data->shapeCount++;
  }
  int GameImpl::addString(const char* text)
  {
    assert(data->stringCount < GameData::MAX_STRINGS);
    StrCopy(data->strings[data->stringCount], text);
    return data->stringCount++;
  }
  int GameImpl::addText(BWAPIC::Shape &s, const char* text)
  {
    s.extra1 = addString(text);
    return addShape(s);
  }
  //-------------------------------------------------- DRAW TEXT ---------------------------------------------
  void GameImpl::setTextSize(Text::Size::Enum size)
  {
    // Clamp to valid sizes
    size = Util::clamp(size, Text::Size::Small, Text::Size::Huge);

    if ( !this->tournamentCheck(Tournament::SetTextSize, &size) )
      return;
    this->textSize = size;
  }
  void GameImpl::vDrawText(CoordinateType::Enum ctype, int x, int y, const char *format, va_list arg)
  {
    if ( !data->hasGUI ) return;
    char buffer[2048];
    VSNPrintf(buffer, format, arg);
    BWAPIC::Shape s(BWAPIC::ShapeType::Text,ctype,x,y,0,0,0,textSize,0,false);
    addText(s,buffer);
  }
  //--------------------------------------------------- DRAW BOX ---------------------------------------------
  void GameImpl::drawBox(CoordinateType::Enum ctype, int left, int top, int right, int bottom, Color color, bool isSolid)
  {
    if (!inScreen(ctype,left,top,right,bottom)) return;
    addShape(BWAPIC::Shape(BWAPIC::ShapeType::Box,ctype,left,top,right,bottom,0,0,color,isSolid));
  }
  //------------------------------------------------ DRAW TRIANGLE -------------------------------------------
  void GameImpl::drawTriangle(CoordinateType::Enum ctype, int ax, int ay, int bx, int by, int cx, int cy, Color color, bool isSolid)
  {
    if (!inScreen(ctype,ax,ay,bx,by,cx,cy)) return;
    addShape(BWAPIC::Shape(BWAPIC::ShapeType::Triangle,ctype,ax,ay,bx,by,cx,cy,color,isSolid));
  }
  //------------------------------------------------- DRAW CIRCLE --------------------------------------------
  void GameImpl::drawCircle(CoordinateType::Enum ctype, int x, int y, int radius, Color color, bool isSolid)
  {
    if (!inScreen(ctype,x-radius,y-radius,x+radius,y+radius)) return;
    addShape(BWAPIC::Shape(BWAPIC::ShapeType::Circle,ctype,x,y,0,0,radius,0,color,isSolid));
  }
  //------------------------------------------------- DRAW ELIPSE --------------------------------------------
  void GameImpl::drawEllipse(CoordinateType::Enum ctype, int x, int y, int xrad, int yrad, Color color, bool isSolid)
  {
    if (!inScreen(ctype,x-xrad,y-yrad,x+xrad,y+yrad)) return;
    addShape(BWAPIC::Shape(BWAPIC::ShapeType::Ellipse,ctype,x,y,0,0,xrad,yrad,color,isSolid));
  }
  //--------------------------------------------------- DRAW DOT ---------------------------------------------
  void GameImpl::drawDot(CoordinateType::Enum ctype, int x, int y, Color color)
  {
    if (!inScreen(ctype,x,y)) return;
    addShape(BWAPIC::Shape(BWAPIC::ShapeType::Dot,ctype,x,y,0,0,0,0,color,false));
  }
  //-------------------------------------------------- DRAW LINE ---------------------------------------------
  void GameImpl::drawLine(CoordinateType::Enum ctype, int x1, int y1, int x2, int y2, Color color)
  {
    if (!inScreen(ctype,x1,y1,x2,y2)) return;
    addShape(BWAPIC::Shape(BWAPIC::ShapeType::Line,ctype,x1,y1,x2,y2,0,0,color,false));
  }
  //--------------------------------------------------- HAS GUI ----------------------------------------------
  bool GameImpl::isGUIEnabled() const
  {
    return data->hasGUI;
  }
  //--------------------------------------------------- SET GUI ----------------------------------------------
  void GameImpl::setGUI(bool enabled)
  {
    if ( !this->tournamentCheck(Tournament::SetGUI, &enabled) )
      return;
    bwgame.setGUI(enabled);
    data->hasGUI = enabled;
    setFrameSkip(enabled ? -1 : 9999999);
  }
  // Fixed precision conversions
  // Uses * and / for compatibility with negative numbers
  #define fixed2Int( x ) ( ((x) + (1 << 15)) / (1 << 16) )
  #define int2Fixed( x ) ( (x) * (1 << 16) )
  #define positive( x ) ( (x) > 1 ? (x) : 1 )
  //--------------------------------------------- DRAW SHAPES ------------------------------------------------
  int GameImpl::drawShapes()
  {
    return data->shapeCount;
  }
#undef fixed2Int
#undef int2Fixed
#undef positive
};
