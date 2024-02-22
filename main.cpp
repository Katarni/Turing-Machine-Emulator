#include "include/TuringM.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  auto machine = TuringM();
  machine.start();
  return QApplication::exec();
}
