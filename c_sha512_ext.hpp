#ifndef C_SHA512_EXT_HPP
#define C_SHA512_EXT_HPP

#include "sha_src/sha512.hpp"
using std::string;

struct c_sha512_ext {

        c_sha512_ext() = delete;

        static string generate_hash (const string &msg) { return sha512<string>(msg); }
        static bool verify_hash (const string &msg, const string &hash) { return (generate_hash(msg) == hash); }
};

#endif // C_SHA512_EXT_HPP

