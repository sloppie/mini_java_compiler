#include "token_stream.h"


void TokenStream::operator<<(Node new_token) {
    TOKEN_STREAM.push_back(new_token);
}