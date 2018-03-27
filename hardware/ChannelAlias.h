//
// Created by Ильдар Сулейманов on 24.03.2018.
//

#ifndef CANHOST_CHANNELALIAS_H
#define CANHOST_CHANNELALIAS_H


class ChannelAlias {
public:
    ChannelAlias(int card,int device, int channel);
    int _card;
    int _device;
    int _channel;
};


#endif //CANHOST_CHANNELALIAS_H
