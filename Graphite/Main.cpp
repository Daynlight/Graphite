#include "Renderer.h"




int main(){
  CW::Renderer::Renderer renderer;
  renderer.setWindowTitle("Graphite");





  while(!renderer.getWindowData()->should_close){
    renderer.beginFrame();


    renderer.swapBuffer();
    renderer.windowEvents();
  };

  return 0;
};