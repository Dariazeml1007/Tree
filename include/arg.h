#ifndef ARG
#define ARG

struct Argv_type
{
    bool is_define = false;
    bool is_guess = false;
};

int process_args (const int argc, const char* argv[], Argv_type *flags);

#endif
