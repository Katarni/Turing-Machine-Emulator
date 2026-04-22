#include "include/App.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "should be assets directory (only) as second argunemt" << std::endl;
    return 0;
  }

  QApplication a(argc, argv);

  auto machine = App(argv[1]);

  return QApplication::exec();
}
