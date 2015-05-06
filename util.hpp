#pragma once

#include <random>
#include <QDebug>
#include <QVector>
#include <QString>

class Util
{
    public:
        static void init();
        static float getRandomFloat(const float & min, const float & max);
        static int getRandomInt(const int & min, const int & max);
};
