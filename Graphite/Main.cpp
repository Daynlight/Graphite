#include "Renderer.h"


#include "ScriptController/ScriptController.h"



int main(){
  CW::Renderer::Renderer renderer;
  renderer.setWindowTitle("Graphite");

  Graphite::ScriptLoader script("Script");




  while(!renderer.getWindowData()->should_close){
    renderer.beginFrame();

    script.checkLastWrite();

    script.update();

    renderer.swapBuffer();
    renderer.windowEvents();
  };

  return 0;
};