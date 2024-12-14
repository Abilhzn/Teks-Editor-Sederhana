void shiftLeft(List L, Address &Cursor) {
    if (Cursor->prev != nullptr) {
        Cursor = Cursor->prev;
    }
}

void shiftRight(List L, Address &Cursor) {
    if (Cursor->next != nullptr) {
        Cursor = Cursor->next;
    }
}