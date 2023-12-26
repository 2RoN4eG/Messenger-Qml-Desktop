#include "t_application.h"

int main(int argc, char *argv[])
{
    t_application application { argc, argv };

    return application.exec();
}
