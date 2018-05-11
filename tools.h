#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <QByteArray>

class Tools
{
public:
    Tools();

    static QByteArray hexStringToArray(QString hex);

    static QString arrayToHexString(QByteArray &array);

    static QString arrayToASCIIString(QByteArray &array);

    static int g711u_decode(short amp[], const unsigned char g711u_data[], int g711u_bytes);
    static int g711u_encode(unsigned char g711_data[], const short amp[], int len);
};

#endif // TOOLS_H
