#ifndef TERMPROJECT_H
#define TERMPROJECT_H
#include <string>
#include <QString>

class termproject {
private:
    int cols = 0;
    int rows = 0;
    unsigned char* pixelValues = nullptr;
    unsigned char* pixelProcessed = nullptr;
public:
    termproject(std::string fname);
    termproject(QString qFname);
    ~termproject();
    int imageProc(int Mode);
    int imageReset();
    int imageWrite(std::string fname);
    int imageWrite(QString qFname);
    int getWidth() const { return cols; }
    int getHeight() const { return rows; }
    unsigned char* getProcessedData() const { return pixelProcessed; }
    unsigned char* getOriginalData() const { return pixelValues; }
};
#endif // TERMPROJECT_H
