#include "include/App.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  auto machine = App();

  return QApplication::exec();
}
