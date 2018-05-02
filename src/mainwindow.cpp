#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStringListModel>
#include <QStringList>
#include <QFile>
#include <QMessageBox>
#include "Delegate.h"
// 1) список полей
// 2) название dataobjet:
// 3) set- и get- методы
// 4) конструктор
// model:
// 5) enum roles

// +TODO #include
// TODO #define
// TODO при заполнении названий свойств заполняются roles и names
// placeholder у roles и names
// TODO перемещения и удаление свойств
// TODO плагин QT

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* widget'ы самой первой строки */
    QComboBox * cb =
            new QComboBox( ui->tblProperties );
    cb->setEditable(true);

    cb->addItems(listTypes);
    ui->tblProperties
            ->setCellWidget (
                ui->tblProperties->rowCount()-1,
                1, cb );

    /*ui->tblProperties
            ->setCellWidget (
                ui->tblProperties->rowCount()-1,
                1, cb );*/

    /* загрузка шаблонов */
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

            cb->addItems(listTypes);

            ui->tblProperties
                    ->setCellWidget (
                        ui->tblProperties->rowCount()-1,
                        1, cb );
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

    if(ui->chkController->checkState() == Qt::Checked)
    {
        QString strControllerName1;
        if(ui->edtControllerName1->text().isEmpty())
        {
            strControllerName1 = "Data";
        }
        else
        {
            strControllerName1 = ui->edtControllerName1->text();
        }

        QString strControllerName2;
        if(ui->edtControllerName2->text().isEmpty())
        {
            strControllerName2 = "Model";
        }
        else
        {
            strControllerName2 = ui->edtControllerName2->text();
        }

        strControllerName =
                strControllerName1
                + strControllerName2;
    }
    else
    {
        strControllerName.clear();
    }
}

void MainWindow::on_btnCreteModel_clicked()
{
    // TODO фильтрация ввод по синтаксису C++

    names();
    ui->tabsCodePages->setTabText(0, strFileName + ".h");
    ui->tabsCodePages->setTabText(1, strFileName + ".cpp");
    parameterList();
    foreach(PropRecord it, lstProperties)
    {
        listGetMethods << it.type
                       + " "
                       + "get"
                       + it.property[0].toUpper()
                       + it.property.remove(0, 1)
                       + "() const";
    }

    foreach(PropRecord it, lstProperties)
    {
        listCopyConstructorParameters +=
                "const "
                + it.type
                + " &p_" + it.property + ",\n";
    }
    listCopyConstructorParameters =
            listCopyConstructorParameters.
            left(listCopyConstructorParameters.length() - 2);


    CombineCpp();
    CombineHeader();

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

void MainWindow::CombineCpp()
{
    QString result;

    cppCode.replace("<<objClassName>>", strObjClassName);
    cppCode.replace("<<modelClassName>>", strObjModelName);

    // <<listCopyConstructorParameters>>
    cppCode.replace("<<listCopyConstructorParameters>>",
                    listCopyConstructorParameters);

    // "<<listPrivateAssign1>>"
    QString listPrivateAssign1;
    foreach(PropRecord it, lstProperties)
    {
        listPrivateAssign1 += "m_" + it.property + "(p_"+it.property+"),\n";
    }
    listPrivateAssign1 = listPrivateAssign1.left(listPrivateAssign1.length()-1);
    cppCode.replace("<<listPrivateAssign1>>",
                    listPrivateAssign1);

    // "<<listPrivateAssign2>>"
    /*QString listPrivateAssign2;

    cppCode.replace("<<listPrivateAssign2>>",
                    listPrivateAssign1);*/


    // "<<listReturnByRole>>"
    QString listReturnByRole;
    listReturnByRole = "const " + strObjClassName +
            "&itemToReturn = m_items[index.row()];\n";

    foreach(PropRecord it, lstProperties)
    {
        listReturnByRole += "if (role == " + it.role + ")\n"
        + "return itemToReturn.get"
        + it.property[0].toUpper() + it.property.right(1)
        + "();\n" + "else ";
    }
    listReturnByRole = listReturnByRole.left(listReturnByRole.length() - 5);
    cppCode.replace("<<listReturnByRole>>",
                    listReturnByRole);

    // "<<listRolesAndNames>>"
    QString listRolesAndNames;
    foreach(PropRecord it, lstProperties)
    {
        listRolesAndNames += "\troles["
                + it.role + "] = \""
                + it.qml_name + "\";\n";
    }
    cppCode.replace("<<listRolesAndNames>>",
                    listRolesAndNames);

    // "<<controllerClassName>>"
    if(ui->chkController->checkState() == Qt::Checked)
    {
        cppCode.replace("<<controllerClassName>>",
                      strControllerName);
    }
    else
    {
        int pos = cppCode.indexOf("<<controllerClassName>>");
        pos = cppCode.lastIndexOf('}',pos);
        pos++;
        cppCode = cppCode.left(pos); // TODO возможно эта отрезает до rowCount
    }

    // TODO переделать в pairs "строка" - "замена"
    // TODO в один цикл foreach

    // <<listGetMethodsDefinitions>>
    QString listGetMethodsDefinitions;
    foreach (QString getMethod, listGetMethods) {
        listGetMethodsDefinitions +=
                getMethod
                + "\n{\nreturn;\n}\n";
    }
    listGetMethodsDefinitions.chop(1);

    cppCode.replace("<<listGetMethodsDefinitions>>",
                    listGetMethodsDefinitions);
    // <<fileName>> в #include
    cppCode.replace("<<fileName>>",
                    strFileName);

    return;

}

void MainWindow::CombineHeader()
{
    hCode.replace("<<objClassName>>", strObjClassName);
    hCode.replace("<<modelClassName>>", strObjModelName);

    // замены для h
    //"<<listGetMethodsDeclarations>>"
    QString listGetMethodsDeclarations;
    foreach(QString it, listGetMethods)
    {
        listGetMethodsDeclarations +=
                '\t' + it + ";\n";
    }
    hCode.replace("<<listGetMethodsDeclarations>>",
                  listGetMethodsDeclarations);

    //"<<listPrivatePropertiesDeclarations>>"
    //  имя   тип  роль   названиеQML
    QString listPrivatePropertiesDeclarations;
    foreach(PropRecord it, lstProperties)
    {
        listPrivatePropertiesDeclarations +=
                '\t' + it.type + " m_" + it.property + ";\n";
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
    listRoles = listRoles.left(listRoles.length()-2);

    hCode.replace("<<listRoles>>", listRoles);

    // "<<controllerClassName>>"
    if(ui->chkController->checkState() == Qt::Checked)
    {
        hCode.replace("<<controllerClassName>>",
                      strControllerName);
    }
    else
    {
        int pos = hCode.indexOf("<<controllerClassName>>");
        pos = hCode.lastIndexOf('}',pos);
        pos++;
        hCode = hCode.left(pos);
    }

    // <<listCopyConstructorParameters>>
    // TODO
    hCode.replace("<<listCopyConstructorParameters>>",
                  listCopyConstructorParameters);
}


void MainWindow::on_chkController_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        ui->edtControllerName1->setEnabled(true);
        ui->edtControllerName2->setEnabled(true);
    }
    else
    {
        ui->edtControllerName1->setEnabled(false);
        ui->edtControllerName2->setEnabled(false);
    }
}

void MainWindow::on_btnSave_clicked()
{
    QFile file(strFileName + ".cpp");
          if (!file.open(QIODevice::ReadWrite
                         | QIODevice::Text
                         | QIODevice::Truncate))
              return;
    QTextStream out1(&file);
    out1 << cppCode;
    file.close();
    qDebug() << "*** cppCode written";

    file.setFileName(strFileName + ".h");
          if (!file.open(QIODevice::ReadWrite
                         | QIODevice::Text
                         | QIODevice::Truncate))
              return;
    QTextStream out2(&file);
    out2 << hCode;
    file.close();
    qDebug() << "*** hCode written";
    return;
}
