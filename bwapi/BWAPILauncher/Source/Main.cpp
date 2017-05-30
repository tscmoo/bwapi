
#include "BWAPI/GameImpl.h"
#include "BW/BWData.h"

#include <cstdio>

int main() {
  
  try {
    
    BW::GameOwner gameOwner;
    
    gameOwner.setPrintTextCallback([](const char* str) {
      std::string s;
      while (*str) {
        char c = *str++;
        if ((unsigned)c >= 0x20 || c == 9 || c == 10 || c == 13) s += c;
      }
      printf("%s\n", s.c_str());
    });
    
    BWAPI::BroodwarImpl_handle h(gameOwner.getGame());
    
    h->autoMenuManager.startGame();
    
    while (!h->bwgame.gameOver()) {
      h->update();
      h->bwgame.nextFrame();
      
      if (!h->externalModuleConnected) {
        printf("No module loaded, exiting\n");
        return 1;
      }
    }
    h->onGameEnd();
  } catch (const std::exception& e) {
    printf("Error: %s\n", e.what());
  }
  
  return 0;
}
