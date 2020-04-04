#include "token_stream.h"


void TokenStream::operator<<(Node new_token) {
    TOKEN_STREAM.push_back(new_token);
}


Node TokenStream::next_token() {
    if (POSITION + 1 <= TOKEN_STREAM.size()) {
        Node next_node = TOKEN_STREAM.at(POSITION);
        POSITION++;

        return next_node;
    } else {
        return Node(true, "NO_TOKEN");
    }
    
}