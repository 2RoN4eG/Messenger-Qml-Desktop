#include "t_application.h"

int main(int argc, char *argv[])
{
    test_compound_fs_path_maker();

    t_application application { argc, argv };

    return application.exec();
}
