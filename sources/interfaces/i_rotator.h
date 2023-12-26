#ifndef I_ROTATOR_H
#define I_ROTATOR_H

class t_fs;

class i_rotator {
public:
    virtual ~i_rotator() = 0;

    virtual void do_rotate(const t_fs& fs) = 0;
};

#endif // I_ROTATOR_H
