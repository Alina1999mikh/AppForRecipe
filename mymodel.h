#ifndef MYMODEL_H
#define MYMODEL_H
#include <QVariant>

class myModel
{
public:
    myModel();
    QVariant data(const QModelIndex &idx, int role);
};

#endif // MYMODEL_H
