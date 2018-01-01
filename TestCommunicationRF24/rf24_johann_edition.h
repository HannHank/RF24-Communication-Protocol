

enum Type
{
    INT,
    FLOAT,
    CHAR,
    ERROR,
    NO_RESULT
};

struct readPack
{
    Type type;
    int i;
    float f;
    char c;
};

byte *buildMsg(Type type, void *val)
{
    static byte buf[5];

    buf[1] = ((byte*)val)[0];
    buf[2] = ((byte*)val)[1];
    buf[3] = ((byte*)val)[2];
    buf[4] = ((byte*)val)[3];

    switch (type)
    {
    case INT:
        buf[0] = 'i';
        break;
    case FLOAT:
        buf[0] = 'f';
        break;
    case CHAR:
        buf[0] = 'c';
        break;
    }

    return buf;
}

readPack interpretMsg(const byte *receivedMsg)
{
    readPack result;

    switch (*receivedMsg)
    {
    case 'i':
        result.type = INT;
        result.i = *((int *)(receivedMsg + 1));
        break;
    case 'f':
        result.type = FLOAT;
        result.f = *((float *)(receivedMsg + 1));
        break;
    case 'c':
        result.type = CHAR;
        result.c = *((char *)(receivedMsg + 1));
        break;
    default:
        result.type = ERROR;
    }

    return result;
}

int sizeOfMsg()
{
    return 5;
}

void examplesSend()
{
    // myRadio.write(buildMsg(INT, 200), sizeOfMsg());
    // myRadio.write(buildMsg(FLOAT, 5.0), sizeOfMsg());
    // myRadio.write(buildMsg(CHAR, 'cs'), sizeOfMsg());
}

void examplesReceive()
{
    byte *dataReceived = 0;

    // myRadio.read(dataReceived, sizeOfMsg());

    readPack adrian = interpretMsg(dataReceived);

    switch (adrian.type)
    {
    case INT:
        // do different stuff with adrian.i
        break;
    case FLOAT:
        // do different stuff with adrian.f
        break;
    case CHAR:
        // do different stuff with adrian.c
        break;
    default:
        break;
    }
}
