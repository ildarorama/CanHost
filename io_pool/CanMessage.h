//
// Created by  Ильдар Сулейманов on 13.03.2018.
//

#ifndef CANHOST_CANMESSAGE_H
#define CANHOST_CANMESSAGE_H


class CanMessage {
public:
    CanMessage(void * data,int size);
    void * data();
    int size();
private:
    void * _data;
    int _size;
};


#endif //CANHOST_CANMESSAGE_H
