#include "include/TuringM.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  auto machine = TuringM();

  return QApplication::exec();
}
