//
// Created by KR on 11/29/2017.
//

#ifndef GCPP_KEYS_H
#define GCPP_KEYS_H


struct Keys {
    Keys(bool caps, bool shift, bool alt, bool ctrl, bool tab, bool win);

    bool caps;
    bool shift;
    bool alt;
    bool ctrl;
    bool tab;
    bool win;
};

#endif //GCPP_KEYS_H