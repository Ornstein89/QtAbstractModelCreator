#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStringListModel>
#include <QStringList>
#include <QFile>
#include <QMessageBox>
// 1) список полей
// 2) название dataobjet:
// 3) set- и get- методы
// 4) конструктор
// model:
// 5) enum roles


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QComboBox * cb =
            new QComboBox( ui->tblProperties );
    cb->setEditable(true);
    QStringList list;
    list << "QString" << "int" << "double" << "char" << "undigned int";
    cb->addItems(list);
    ui->tblProperties
            ->setCellWidget (
                ui->tblProperties->rowCount()-1,
                1,
                cb );
    if (!LoadSampleFiles())
    {
        QMessageBox::critical(this, "Ошибка", "Файлы-шаблоны tmpClass.cpp\nи tmpClass.h не найдены");
        //qApp->exit();
        this->ready = false;
        qDebug() << "*** ready == false";
        return;
    }
    this->ready = true;

}

bool MainWindow::LoadSampleFiles()
{
    QFile file("tmpClass.cpp");
          if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
              return false;
    cppCode = file.readAll();
    file.close();
    qDebug() << cppCode.mid(0, 100);

    file.setFileName("tmpClass.h");
          if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
              return false;
    hCode = file.readAll();
    file.close();

    qDebug() << hCode.mid(0, 100);
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tblProperties_cellChanged(int row, int column)
{
    // TODO если строка была последняяя и все строки заполнены -
    //  +добавить новую пустую
    //  +добавить номер
    //  + добавить ComboboxItem
    qDebug() << "*** columnCount() = "
             << ui->tblProperties->columnCount();

    bool notEmptyString = false;
    for (int i = 0;
         (i < ui->tblProperties->columnCount())
         || !notEmptyString;
         i++)
    {
        qDebug() << "*** i = " << i;
        qDebug() << "*** item(row, " << i << ") = "
                 << ui->tblProperties->item(row, i);
        //qDebug() << "*** text() = " << ui->tblProperties->item(row, i)->text();
        if(ui->tblProperties->item(row, i) == nullptr)
            continue;
        if(i == 1)
            if(QComboBox(ui->tblProperties->cellWidget(row, i)).currentText().isEmpty())
                continue;
        else
            if(ui->tblProperties->item(row, i)->text().isEmpty())
                continue;
        notEmptyString = true;
        break;
    }
    qDebug() << "*** notEmptyString = " << notEmptyString;


    if(notEmptyString)
    {
        if(row == ui->tblProperties->rowCount()-1)
        {
            ui->tblProperties
                    ->insertRow(ui->tblProperties->rowCount() );
            qDebug() << "*** insertRow() OK";
            qDebug() << "*** rowCount() = " << ui->tblProperties->rowCount();

            /*ui->tblProperties
                    ->setItem   ( ui->tblProperties->rowCount()-1,
                                     yourColumn,
                                     new QTableWidgetItem(string));*/

            /*ui->tblProperties
                    ->verticalHeaderItem(ui->tblProperties->rowCount()-2)
                    ->setText(QString::number(ui->tblProperties->rowCount()));
            qDebug() << "*** setText() OK";*/

            //https://stackoverflow.com/questions/3172415/qcombobox-and-qspinbox-in-qtablewidget-with-appropriate-alignment?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
            QComboBox * cb =
                    new QComboBox( ui->tblProperties );
            cb->setEditable(true);

            QStringList list;
            list << "QString" << "int" << "double";
            cb->addItems(list);

            ui->tblProperties
                    ->setCellWidget (
                        ui->tblProperties->rowCount()-1,
                        1,
                        cb );
            qDebug() << "*** setCellWidget() OK";
            /*ui->tblProperties
                    ->horizontalHeader()
                    ->setResizeMode( 0, QHeaderView::Stretch );
            ui->tblProperties
                    ->horizontalHeader()
                    ->setResizeMode( 1, QHeaderView::ResizeToContents );*/
        }
    }
}

void MainWindow::names()
{
    QString strObjClassName1;
    if(ui->edtItemName1->text().isEmpty())
    {
        strObjClassName1 = "Data";
    }
    else
    {
        strObjClassName1 = ui->edtItemName1->text();
    }

    QString strObjClassName2;
    if(ui->edtItemName2->text().isEmpty())
    {
        strObjClassName2 = "Object";
    }
    else
    {
        strObjClassName2 = ui->edtItemName2->text();
    }

    strObjClassName =
            strObjClassName1
            + strObjClassName2;

    QString strObjModelName1;
    if(ui->edtModelName1->text().isEmpty())
    {
        strObjModelName1 = "Data";
    }
    else
    {
        strObjModelName1 = ui->edtModelName1->text();
    }

    QString strObjModelName2;
    if(ui->edtModelName2->text().isEmpty())
    {
        strObjModelName2 = "Model";
    }
    else
    {
        strObjModelName2 = ui->edtModelName2->text();
    }

    strObjModelName =
            strObjModelName1
            + strObjModelName2;


    if(ui->edtFileName1->text().isEmpty())
    {
        strFileName = "Class";
    }
    else
    {
        ui->edtFileName1->text();
    }
}

void MainWindow::on_btnCreteModel_clicked()
{
    // TODO фильтрация ввод по синтаксису C++

    names();
    ui->tabsCodePages->setTabText(0, strFileName + ".h");
    ui->tabsCodePages->setTabText(1, strFileName + ".cpp");
    parameterList();
    CombineCpp();

    ui->edtCpp->setText(cppCode);
    ui->edtHeader->setText(hCode);
}

void MainWindow::parameterList()
{
    qDebug() << ui->tblProperties->item(0, 0)->text();
    qDebug() << qobject_cast<QComboBox*>(ui->tblProperties->cellWidget(0, 1))->
                currentText();
    qDebug() << ui->tblProperties->item(0, 2)->text();
    qDebug() << ui->tblProperties->item(0, 3)->text();

    for(int i = 0;
        i < ui->tblProperties->rowCount()-1;
        i++)
    {
        lstProperties.append(
                    PropRecord(
                        ui->tblProperties->item(i, 0)->text(),
                        qobject_cast<QComboBox*>(ui->tblProperties->cellWidget(i, 1))->
                        currentText(),
                        ui->tblProperties->item(i, 2)->text(),
                        ui->tblProperties->item(i, 3)->text()));
    }

    qDebug() << lstProperties[0].property
            << lstProperties[0].type
            << lstProperties[0].role
            << lstProperties[0].qml_name;
}

QString MainWindow::CombineCpp()
{
    QString result;

    cppCode.replace("<<objClassName>>", strObjClassName);
    cppCode.replace("<<modelClassName>>", strObjModelName);

    /* замены для cpp
    "<<listPrivateAssign1>>"
    "<<listPrivateAssign2>>"
    "<<listReturnByRole>>"
    "<<listRolesAndNames>>"
    "<<controllerClassName>>"*/

    hCode.replace("<<objClassName>>", strObjClassName);
    hCode.replace("<<modelClassName>>", strObjModelName);

    // замены для h
    //"<<listGetMethodsDeclarations>>"
    //"<<listPrivatePropertiesDeclarations>>"

    //  имя   тип  роль   названиеQML
    QString listPrivatePropertiesDeclarations;
    foreach(PropRecord it, lstProperties)
    {
        listPrivatePropertiesDeclarations +=
                '\t' + it.type + " m_" + it.property + '\n';
    }

    hCode.replace("<<listPrivatePropertiesDeclarations>>", listPrivatePropertiesDeclarations);

    //"<<listRoles>>"
    QString listRoles;
    bool firstrole = true;
    foreach(PropRecord it, lstProperties)
    {
        listRoles +=
                '\t' + it.role;
        if(firstrole)
        {
            listRoles += " = Qt::UserRole + 1";
            firstrole = false;
        }
        listRoles += ",\n";
    }

    hCode.replace("<<listRoles>>", listRoles);

    //"<<controllerClassName>>"


    // TODO переделать в pairs "строка" - "замена"

    return result;

}
/*
QString CombineHeader(QString objClassName,
                      QString modelClassName)
{
    QString result;

    class NoteObject
    {
    public:
        NoteObject(const QString &datetime,
                   const QString &caption,
                   const QString &reference,
                   const QString &path,
                   const int &atch);
        //get-методы
        for()
        {
            result.append(тип + " " + название_параметра + "() const;\n");

//        QString dateTime() const;
//        QString caption() const;
//        QString reference() const;
//        QString path() const;
//        bool isText() const;
//        bool isScreenshot() const;
//        bool isAudio() const;
//        bool isVideo() const;
//        bool isPhoto() const;
    }

    result.append("private:\n");

    // свойства
    for()
    {
        result.append(тип + "\tm_" + название_параметра + ";\n");
//        QString m_datetime;
//        QString m_caption;
//        QString m_reference;
//        QString m_path;
//        bool m_text;
//        bool m_screenshot;
//        bool m_audio;
//        bool m_photo;
//        bool m_video;
    }

    append("};\n\n");

    return result;
}
*/
