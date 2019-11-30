#include "examplevalidator.h"
#include <QChar>
#include <QRegExp>

ExampleValidator::ExampleValidator(){}

ExampleValidator::ExampleValidator(QObject* parent)
    : QValidator (parent)
{

}

ExampleValidator::~ExampleValidator()
{

}


QValidator::State ExampleValidator::validate(QString &string, int &pos) const{

    QRegExp strong_validate("[a-zA-Z]://(\\w\\d//)+//[a-zA-Z]+.[a-zA-Z]+");
    QRegExp light_validate("[a-zA-Z]*:?/?/?(\\w\\d//)*[a-zA-Z]*.?[a-zA-Z]*");

    if(strong_validate.exactMatch(string))
        return QValidator::Acceptable;
    else if(light_validate.exactMatch(string))
        return QValidator::Intermediate;
    else {
        return QValidator::Invalid;
    }
}
