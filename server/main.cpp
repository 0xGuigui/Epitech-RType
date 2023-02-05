#include "server/server.h"

int main() {
    Server server(50000);

    try {
        server.run();
    } catch (std::exception &e) {
        // catch any unhandled exceptions
        std::cerr << e.what() << std::endl;
        server.stop();
    }
    return 0;
}