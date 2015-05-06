#include <iostream>
#include <QCoreApplication>
#include <QString>
#include <QXmlStreamWriter>
#include <QFile>
#include <QFileInfo>
#include "util.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Starting problems" << std::endl;
    Util::init();
    QCoreApplication a(argc, argv);
    int problemsCount = 10000;
    int inputCount = 100;
    int wantedOutputCount = 1;
    std::cout << "Creating problems : 0%" << std::flush;
    QFile file("./test.problems");
    file.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("problems");
    {
        for(int i = 0 ; i < problemsCount ; i++)
        {
            xmlWriter.writeStartElement("problem");
            {
                QString inputs;
                for(int i = 0 ; i < inputCount ; i++)
                {
                    if(i)
                        inputs += ';';
                    inputs += QString::number(Util::getRandomFloat(0.0,1.0));
                }
                xmlWriter.writeTextElement("inputs", inputs);
                QString wantedOutputs;
                for(int i = 0 ; i < wantedOutputCount ; i++)
                {
                    if(i)
                        wantedOutputs += ';';
                    wantedOutputs += QString::number(Util::getRandomInt(1,10));
                }
                xmlWriter.writeTextElement("wantedOutputs", wantedOutputs);
            }
            xmlWriter.writeEndElement();
            if(!(i%(problemsCount/100)) && i)
                std::cout << '\xd' << "Creating problems : "
                          << i/(problemsCount/100) << "%" << std::flush;
        }
    }
    std::cout << '\xd' << "Creating problems : 100%" << std::endl;
    std::cout << "Perfecting problems" << std::endl;
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    QFileInfo fileInfo(file);
    std::cout << "Problems available at "
              << fileInfo.absoluteFilePath().toStdString() << std::endl;
    return a.exec();
}
